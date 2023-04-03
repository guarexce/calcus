#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "User.h"

#include <string>

class UserInterface {
public:
	UserInterface(User *);
	~UserInterface();

	std::string *getLogin();
	std::string *getPassword();
	std::string *getCommand();
	void postResult(std::string *);
	void resetConnection();

private:
	User *userPtr;

	char *buffer;
	const int length = 100;

	const std::string loginKey = "login";
	const std::string passwordKey = "password";
	const std::string calcKey = "calc";
	const std::string logoutKey = "logout";

	const std::string WHITESPACE = " \n\r\t\f\v";

	std::string *getString();
	void postString(std::string *);
};

#endif
