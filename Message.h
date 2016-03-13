#ifndef MESSAGE_H
#define MESSAGE_H

#include <string.h>
#include <stdlib.h>
#include <iostream>

class Message {
public:
	Message() {
		this->msg = "";
	}
	Message(std::string msg) {
		this->msg = msg;
	}

	void setMessage(std::string msg) {
		this->msg = msg;
	}

	std::string getMessage() {
		return this->msg;
	}

private:
	std::string msg;
};
#endif