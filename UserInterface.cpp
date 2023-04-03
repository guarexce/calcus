#include "UserInterface.h"

#include <string.h>

#include <sys/socket.h>
#include <unistd.h>

UserInterface::UserInterface(User *ptr) : userPtr(ptr) {
	buffer = (char *) malloc(sizeof(char) * length);
}

UserInterface::~UserInterface() {
	if (buffer != NULL) {
		free(buffer);
	}
}

std::string *UserInterface::getLogin() {
	std::string *login = getString();

	if (login != nullptr && login->rfind(loginKey, 0) == 0) {
		login->erase(0, loginKey.length());

		if (login->length() > 0) {
			int index = login->find_first_not_of(WHITESPACE);

			login->erase(0, index);

			index = login->find_last_not_of(WHITESPACE);

			login->erase(index + 1, std::string::npos);

			if (login->length() > 0) {
				return login;
			}
		}
	}

	return nullptr;
}

std::string *UserInterface::getPassword() {
	std::string *password = getString();

	if (password != nullptr && password->rfind(passwordKey, 0) == 0) {
		password->erase(0, passwordKey.length());

		if (password->length() > 0) {
			int index = password->find_first_not_of(WHITESPACE);

			password->erase(0, index);

			index = password->find_last_not_of(WHITESPACE);

			password->erase(index + 1, std::string::npos);

			if (password->length() > 0) {
				return password;
			}
		}
	}

	return nullptr;
}

std::string *UserInterface::getCommand() {
	std::string *command = getString();

	if (command != nullptr) {
		if (command->rfind(calcKey, 0) == 0) {
			command->erase(0, calcKey.length());

			if (command->length() > 0) {
				int index = command->find_first_not_of(WHITESPACE);

				command->erase(0, index);

				index = command->find_last_not_of(WHITESPACE);

				command->erase(index + 1, std::string::npos);

				if (command->length() > 0) {
					return command;
				}
			}
		} else if (command->rfind(logoutKey, 0) == 0) {
			int index = command->find_last_not_of(WHITESPACE);

			command->erase(index + 1, std::string::npos);

			if (command->length() == logoutKey.length()) {
				return command;
			}
		}
	}

	return nullptr;
}

void UserInterface::postResult(std::string *result) {
	postString(result);
}

std::string *UserInterface::getString() {
	if (userPtr == nullptr || userPtr->getFd() < 0) {
		return nullptr;
	}

	memset(buffer, 0, length);

	int count = recv(userPtr->getFd(), buffer, length, 0);

	if (count != -1) {
		return new std::string(buffer);
	}

	return nullptr;
}

void UserInterface::postString(std::string *ptr) {
	if (userPtr == nullptr || userPtr->getFd() < 0) {
		return;
	}

	const char *str = ptr->c_str();
	int len = strlen(str);

	send(userPtr->getFd(), str, len, 0);
}

void UserInterface::resetConnection() {
	if (userPtr == nullptr || userPtr->getFd() < 0) {
		return;
	}

	close(userPtr->getFd());
}
