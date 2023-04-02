#ifndef USER_H
#define USER_H

struct User {
	User(int userFd) : fd(userFd) {
	}

private:
	int fd;
};

#endif
