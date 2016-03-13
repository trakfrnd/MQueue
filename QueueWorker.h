#ifndef QUEUEWORKER_H
#define QUEUEWORKER_H

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "IPersistentStorage.h"
#include "LocalFileSystem.h"
#include "Database.h"

class ThreadPool;

class QueueWorker {
public:
	QueueWorker(ThreadPool &s) : pool(s),localFileSystem(new LocalFileSystem()), db(new Database()) {}
    void operator()();
private:	
    ThreadPool &pool;
    std::unique_ptr<LocalFileSystem> localFileSystem;
    std::unique_ptr<Database> db;
    void persistMessage(uint64_t key, Message msg);
};

#endif