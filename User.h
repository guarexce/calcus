#ifndef USER_H
#define USER_H

struct User {
	User(int userFd) : fd(userFd) {
	}

	int getFd() {
		return fd;
	}

private:
	// information about user
	// for now is FD only
	int fd;
};

#endif
