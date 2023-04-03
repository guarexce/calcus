#ifndef USERVALIDATOR_H
#define USERVALIDATOR_H

#include <map>

typedef std::map<std::string, std::string> UsersList;

class UserValidator {
	UsersList usersList; // contains login and password pair

public:
	int operator()(std::string login, std::string password) {
		UsersList::iterator iter = usersList.find(login);

		if (iter != usersList.end()) {
			if (iter->second.compare(password) == 0) {
				return 0; // validated successfully
			} else {
				return -1; // is not validated
			}
		}

		// add new login and password pair if it's not presented
		usersList[login] = password;

		return 0;
	}
};

#endif
