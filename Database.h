#ifndef IDATABASE_H
#define IDATABASE_H

#include <string.h>
#include <stdlib.h>
#include "Message.h"

class Database {
public:
	void storeMessage(Message msg, uint64_t msgKey);
	Message getMessage(std::string path);
};
#endif