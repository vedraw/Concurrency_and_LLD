Question Link: 
https://www.interviewstop.com/InterviewPrep/QuestionBank/multithreaded-web-crawler-lld?category=LLD&company=Rubrik&role=L4

Your crawler doesn’t need a stop flag because the threads naturally exit when all URLs are processed.
A reusable thread pool needs a stop flag to terminate threads safely when no more tasks are coming.

Multithreaded consideration: 
In a single-thread BFS (like you wrote), both versions will produce the same final vis.
In multithreaded crawling, you must mark visited before pushing, and guard with a mutex. Otherwise, two threads could both push the same URL at the same time.

