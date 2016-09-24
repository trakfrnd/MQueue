#ifndef ILOCALFILESYSTEM_H
#define ILOCALFILESYSTEM_H

#include <string.h>
#include <stdlib.h>
#include "Message.h"
#include "IPersistentStorage.h"
/*
Test
Test
*/
class LocalFileSystem: public IPersistentStorage {
public:
	void storeMessage(Message msg, uint64_t msgKey);
	Message getMessage(std::string path);
};
#endif