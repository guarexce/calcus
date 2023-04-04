#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <iostream>
#include <cstring>

class CommandProcessor {
	const int length = 200;
	char *buffer;

	// execute command in shell and get result string
	std::string *executeCommand(const char *command) {
		std::string *result = new std::string("");

		FILE *pipe = popen(command, "r");

		if (!pipe) {
			delete result;

			return nullptr;
		}

		try {
			while (fgets(buffer, length, pipe) != nullptr) {
				*result += buffer;
			}
		} catch (...) {
			pclose(pipe);

			delete result;

			return nullptr;
		}

		pclose(pipe);

		return result;
	}

public:
	CommandProcessor() {
		buffer = (char *) malloc(sizeof(char) * length);
	}

	~CommandProcessor() {
		if (buffer != nullptr) {
			free(buffer);
		}
	}

	std::string *operator()(std::string command) {
		command.insert(0, "echo \"");
		command.append("\" | bc -l"); // use basic calculator

		return executeCommand(command.c_str());
	}
};

#endif
