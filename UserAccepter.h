#ifndef USERACCEPTER_H
#define USERACCEPTER_H

#include "User.h"

#include <string>

class UserAccepter {
public:
	UserAccepter(const std::string *, const int);
	~UserAccepter();

	int getErrorState() {
		return error;
	}

	User *acceptUser();
private:
	int fd;
	void *addressPtr;

	int error;

	void setErrorState() {
		error = -1;
	}
};

#endif
