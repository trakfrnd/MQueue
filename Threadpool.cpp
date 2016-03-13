#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "QueueWorker.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threads)
    :stop(false)
{
    for(size_t i = 0;i<threads;++i)
        workers.push_back(std::thread(QueueWorker(*this)));
}

ThreadPool* ThreadPool::getThreadPool() {
    std::mutex qmutex;
    std::unique_lock<std::mutex> lock(qmutex);
    return new ThreadPool(2);
}
   
ThreadPool::~ThreadPool()
{
    stop = true;
    qcondition.notify_all();     
    for(size_t i = 0;i<workers.size();++i)
        workers[i].join();
}

void ThreadPool::enqueue(Message *msg)
{
	// Push task to queue
    {
        std::cout << "enquee";
        std::unique_lock<std::mutex> lock(qmutex);
        tasks.push_back(*msg);
    }     
    // wake up one thread
    qcondition.notify_one();
}
