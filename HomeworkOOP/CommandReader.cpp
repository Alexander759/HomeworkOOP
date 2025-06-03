/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#include "CommandReader.h"

List<MyString> CommandReader::readCommand() {
	MyString command;
	std::cout << "> ";
	std::cin >> command;
	return command.separate();
}
