#include <iostream>

#include "UserAccepter.h"
#include "UserInterface.h"
#include "UserValidator.h"
#include "CommandProcessor.h"

using namespace std;

// default configuration...
const string IpAddress = "127.0.0.1";
const int Port = 44818;

UserValidator userValidator;
CommandProcessor commandProcessor;

inline int authenticateUser(UserInterface &userInterface) {
	string *login;
       
	do {
		login = userInterface.getLogin();
	} while (login == nullptr);

	std::cout << "LOGIN: " << *login << endl << flush;

	string *password;
	
	do {
		password = userInterface.getPassword();
	} while (password == nullptr);

	std::cout << "PASSWORD: " << *password << endl << flush;

	if (userValidator(*login, *password) < 0) {
		return -1;
	}

	delete login;
	delete password;

	return 0;
}

inline void calculateOrLogout(UserInterface &userInterface) {
	while (true) {
		string *command;
		
		do {
			command = userInterface.getCommand();
		} while (command == nullptr);

		std::cout << "COMMAND: " << *command << endl << flush;

		if (command->compare("logout") == 0) {
			delete command;

			break;
		}

		string *result = commandProcessor(*command); // calculate the result

		delete command;

		userInterface.postResult(result);

		delete result;
	}
}

int main(int argc, char *argv[]) {
	cout << "Initialize the socket..." << endl << flush;

	UserAccepter userAccepter(&IpAddress, Port);

	if (userAccepter.getErrorState() < 0) {
		cout << "Error occurred!" << endl << flush;

		return -1;
	}

	cout << "Accepting user connections..." << endl << flush;

	User *userPtr;

	while (userPtr = userAccepter.acceptUser()) {
		if (!userPtr) {
			cout << "Error occurred!" << endl << flush;

			break;
		}

		cout << "User Accepted!" << endl << flush;

		UserInterface userInterface(userPtr);

		cout << "Please authorize:" << endl << flush;

		if (authenticateUser(userInterface) < 0) {
			cout << "User is not authorized!" << endl << flush;

			userInterface.resetConnection();

			delete userPtr;

			continue;
		}

		cout << "User is authorized!" << endl << flush;

		calculateOrLogout(userInterface);

		userInterface.resetConnection();

		delete userPtr;
	}

	return 0;
}
