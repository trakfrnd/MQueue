#include <string.h>
#include <stdlib.h>
#include "Database.h"

void Database::storeMessage(Message msg, uint64_t msgKey) {
	std::cout << "Save Message" << msgKey;
}

Message Database::getMessage(std::string path) {
	std::cout << "Get Message";
}
