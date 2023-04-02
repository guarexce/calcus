#include "UserAccepter.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

UserAccepter::UserAccepter(const std::string *ipAddress, const int port) {
	fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd < 0) {
		setErrorState();

		return;
	}

	struct sockaddr_in *address = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));

	address->sin_family = AF_INET;
	address->sin_addr.s_addr = inet_addr(ipAddress->c_str());
	address->sin_port = htons(port);

	addressPtr = address;

	if (bind(fd, (struct sockaddr *) address, sizeof(*address)) < 0) {
		setErrorState();

		return;
	}

	if (listen(fd, 1) < 0) {
		setErrorState();

		return;
	}
}

UserAccepter::~UserAccepter() {
	if (addressPtr) {
		free(addressPtr);
	}
}

User *UserAccepter::acceptUser() {
	struct sockaddr_in *address = static_cast<struct sockaddr_in *>(addressPtr);

	int addrlen = sizeof(*address);

	int userFd = accept(fd, (struct sockaddr *) address, (socklen_t *) &addrlen);

	if (userFd < 0) {
		return NULL;
	}

	return new User(userFd);
}
