class BoundedBlockingQueue {
    int cap;
    queue<int> q;
    mutex mtx;
    condition_variable cv_not_full;
    condition_variable cv_not_empty;

public:
    BoundedBlockingQueue(int capacity) {
        this->cap=capacity;
    }
    
    void enqueue(int element) {
        unique_lock<mutex> lock(mtx);
        cv_not_full.wait(lock, [&](){
            return q.size()<cap;
        });
        q.push(element);
        cv_not_empty.notify_one();
    }
    
    int dequeue() {
        unique_lock<mutex> lock(mtx);
        cv_not_empty.wait(lock, [&](){
            return q.size()>0;
        });
        int val=q.front();
        q.pop();
        cv_not_full.notify_one();
        return val;
    }
    
    int size() {
        lock_guard<mutex> lock(mtx);
        return q.size();
    }
};