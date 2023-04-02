#include <iostream>

#include "UserAccepter.h"

const std::string IpAddress = "localhost";
const int Port = 44818;

int main(int argc, char *argv[]) {
	UserAccepter userAccpeter(&IpAddress, Port);

	User *userPtr;

	while (userPtr = userAccpeter.acceptUser()) {
		;
	}

	return 0;
}
