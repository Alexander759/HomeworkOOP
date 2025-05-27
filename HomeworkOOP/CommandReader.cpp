#include "CommandReader.h"

List<MyString> CommandReader::readCommand() {
	MyString command;
	std::cin >> command;
	return command.separate();
}
