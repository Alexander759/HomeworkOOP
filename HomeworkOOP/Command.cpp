#include "Command.h"
#include <stdexcept>

Command::Command(const MyString& commandName, bool(*validateArgsPtr)(const List<MyString>& args), CommandResponse(*commandPtr)(User& user, System& system, const List<MyString>& args), const List<Role>& allowedRoles) {
	if (this->validateArgsPtr == nullptr || commandPtr == nullptr) {
		throw std::invalid_argument("Can not reference nullptrs");
	}

	this->commandName = commandName;
	this->validateArgsPtr = validateArgsPtr;
	this->commandPtr = commandPtr;
	this->allowedRoles = allowedRoles;
}

CommandResponse Command::run(User& user, System& system, const List<MyString>& args) {
	if (!this->userHasAllowedRole(user)) {
		throw std::invalid_argument("Access denied to user");
	}

	if (!validateArgsPtr(args)) {
		throw std::invalid_argument("Arguments invalid");
	}

	return this->commandPtr(user, system, args);
}

bool Command::userHasAllowedRole(const User& user) {
	for (size_t i = 0; i < this->allowedRoles.getLength(); i++) {
		if (user.isInRole(this->allowedRoles[i])) {
			return true;
		}
	}

	return false;
}

bool Command::validateArgs(const List<MyString>& args) {
	return this->validateArgsPtr(args);
}
