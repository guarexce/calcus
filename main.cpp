#include <iostream>

#include "UserAccepter.h"

using namespace std;

const string IpAddress = "127.0.0.1";
const int Port = 44818;

int main(int argc, char *argv[]) {
	cout << "Initialize the socket..." << endl;

	UserAccepter userAccepter(&IpAddress, Port);

	if (userAccepter.getErrorState() < 0) {
		cout << "Error occurred!" << endl;

		return -1;
	}

	cout << "Accepting user connections..." << endl;

	cout << flush;

	User *userPtr;

	while (userPtr = userAccepter.acceptUser()) {
		if (!userPtr) {
			cout << "Error occurred!" << endl;

			cout << flush;

			break;
		}

		cout << "User Accepted!" << endl;

		cout << flush;
	}

	return 0;
}
