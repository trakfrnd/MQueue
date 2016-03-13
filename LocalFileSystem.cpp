#include <string.h>
#include <stdlib.h>
#include "LocalFileSystem.h"

void LocalFileSystem::storeMessage(Message msg, uint64_t msgKey) {
	std::cout << "Save Message" << msgKey;
}

Message LocalFileSystem::getMessage(std::string path) {
	std::cout << "Get Message";
}
