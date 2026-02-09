#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>
using namespace std;

class HtmlParser {
public:
    vector<string> getUrls(string url){
        if(url=="http://news.example.com/page1")
            return {"http://news.example.com/page2", "http://news.example.com/page3"};
        else if(url=="http://news.example.com/page2")
            return {"http://news.example.com/page4"};
        return {};
    }
};

class Solution {
public:
    string getHost(string url){ //threadsafe as no access to any shared variables here
        int index=url.find('/',7); //find teh first / after http://
        string hostname=url.substr(0,index);
        return hostname;
    }
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        const string hostname=getHost(startUrl);
        unordered_set<string> visited;
        queue<string> q;
        mutex mtx;
        condition_variable cv;
        int working=0;
        //bool stop=false;

        {
            lock_guard<mutex> lock(mtx);
            visited.insert(startUrl);
            q.push(startUrl);
        }

        auto worker=[&](){
            while(true){
                string currUrl;
                //pop fron the queue
                {
                    unique_lock<mutex> lock(mtx);
                    cv.wait(lock, [&](){
                        return !q.empty() || working== 0;
                    });
                    cout<<"Worker: "<<this_thread::get_id()<<" "<<endl;
                    if (q.empty()) {return;} 
                    //entered bcoz of active==0 condn, //no URLs to visit, exit the thread
                    currUrl=q.front(); q.pop();
                    working++;
                }

                vector<string> urls;
                try {
                    urls = htmlParser.getUrls(currUrl);
                } catch (const exception& e){
                    cerr << "Worker " << this_thread::get_id()
                        << " failed on " << currUrl
                        << ": " << e.what() << endl;
         
                    lock_guard<mutex> lock(mtx);
                    working--; //restore the shared state
                    cv.notify_all(); //Other threads may be waiting for working == 0 to become true
                    continue; // go to next loop iteration safely
                }

                //crawl the popped url
                {
                    lock_guard<mutex> lock(mtx);
                    for(auto& url: urls){
                        if(getHost(url)==hostname && visited.find(url)==visited.end()){
                            visited.insert(url);
                            q.push(url);
                        }
                    }
                    working--;
                }  
                cv.notify_all();
            }
        };

        //int numThreads = min(thread::hardware_concurrency(),4u);
        int numThreads = thread::hardware_concurrency();
        if (numThreads == 0) numThreads = 4; // fallback default
        cout<<"main Worker: "<<this_thread::get_id()<<" "<<endl;
        vector<thread> workers;
        for (int i=0; i<numThreads;i++)
        {
            workers.emplace_back(worker);
        }
        // {
        //     unique_lock<mutex> lk(mtx);
        //     cv.wait(lk, [&](){ return q.empty() && working == 0; });
        //     // signal threads to stop and let them exit
        //     //stop = true;
        //     //cv.notify_all(); //is explicit notify needed or not
        // }

        for(auto& w: workers){
            w.join();
        }
        return vector<string>(visited.begin(), visited.end());
    }
};

int main(){
    Solution solution;
    HtmlParser htmlParser;
    string startUrl = "http://news.example.com/page1";
    vector<string> result = solution.crawl(startUrl, htmlParser);
    for(auto& url: result){
        cout << url << endl;
    }
    return 0;
}

/*
Q. What if wanted to add retry logic: modify queue to store pair<string,int>
queue<pair<string,int>> q; // pair<URL, retryCount>
const int MAX_RETRIES = 3;

We need to:
Keep a queue of failed URLs (or reuse the main queue) along with a retry count.
When a worker fails on a URL:
Check if retry count < max retries
If yes, push it back to the queue for another attempt
If no, log it as permanently failed
Ensure thread safety using the same mutex + condition variable logic.
*/
