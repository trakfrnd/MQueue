#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <future>
#include "QueueWorker.h"
#include "ThreadPool.h"

void QueueWorker::operator()()
{
    Message msg;    
    while(true)
    {
    	{
            std::unique_lock<std::mutex> 
                lock(pool.qmutex);
             
            while(!pool.stop && pool.tasks.empty())
            {
                pool.qcondition.wait(lock);
            }
 
            if(pool.stop)
                return;
 
            msg = pool.tasks.front();
            pool.tasks.pop_front();
        }

        // Generate unique identifier for message, need to replace with boost::UUID
        unsigned long key =
            std::chrono::system_clock::now().time_since_epoch()/std::chrono::milliseconds(1);
        persistMessage(key,msg);

        std::cout << "Message " << msg.getMessage();
    }
};

void QueueWorker::persistMessage(uint64_t key, Message msg) {
    //Save messgae in local filesystem
    auto fileSystem = std::async (std::launch::async, 
        std::bind(&LocalFileSystem::storeMessage, localFileSystem.get(), 
            std::placeholders::_1, std::placeholders::_2), msg, key);
    //Save messgae in database
    auto database = std::async (std::launch::async,
        std::bind(&Database::storeMessage, db.get(), 
            std::placeholders::_1, std::placeholders::_2), msg, key);
    fileSystem.wait();
    database.wait();
};
