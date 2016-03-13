#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Message.h"

class ThreadPool {
private:
	ThreadPool(size_t size);
public:
	static ThreadPool* getThreadPool();
	void enqueue(Message *msg);
	~ThreadPool();

private:
    friend class QueueWorker;

	std::vector<std::thread> workers;
    std::deque<Message> tasks;
 
    std::mutex qmutex;
    std::condition_variable qcondition;
    bool stop;
};

#endif