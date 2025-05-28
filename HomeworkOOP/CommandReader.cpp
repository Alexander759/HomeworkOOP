#include "CommandReader.h"

List<MyString> CommandReader::readCommand() {
	MyString command;
	std::cout << "> ";
	std::cin >> command;
	return command.separate();
}
