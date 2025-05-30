#include "Command.h"
#include "System.h"
#include <stdexcept>

size_t Command::currentId = 1;

Command::Command(const MyString& commandName, const MyString& commandHelp, bool(*validateArgsPtr)(const List<MyString>& args), CommandResponse(*commandPtr)(System& system, const List<MyString>& args), const List<Role>& allowedRoles) {
	if (validateArgsPtr == nullptr || commandPtr == nullptr) {
		throw std::invalid_argument("Can not reference nullptrs");
	}

	this->id = currentId;
	currentId++;
	this->commandName = commandName;
	this->commandHelp = commandHelp;
	this->validateArgsPtr = validateArgsPtr;
	this->commandPtr = commandPtr;
	this->allowedRoles = allowedRoles;
}

CommandResponse Command::run(System& system, const List<MyString>& args) {
	if (this->validateArgsPtr == nullptr || this->commandPtr == nullptr) {
		throw std::invalid_argument("Can not reference nullptrs");
	}

	if (this->validateArgsPtr == nullptr || this->commandPtr == nullptr) {
		throw std::exception("Command not found");
	}

	if (!this->userHasAllowedRole(system.getCurrentUserRoles())) {
		return CommandResponse(false, "Access denied");
	}

	if (!validateArgsPtr(args)) {
		return CommandResponse(false, "Arguments invalid");
	}

	return this->commandPtr(system, args);
	system.saveToFile();
}

bool Command::userHasAllowedRole(const List<Role>& roles) {
	for (size_t i = 0; i < this->allowedRoles.getLength(); i++) {
		for (size_t j = 0; j < roles.getLength(); j++) {
			if (this->allowedRoles[i] == roles[j]) {
				return true;
			}
		}
	}

	return false;
}

bool Command::validateArgs(const List<MyString>& args) {
	if (this->validateArgsPtr == nullptr) {
		throw std::exception("Command not found");
	}

	return this->validateArgsPtr(args);
}

size_t Command::getId() const {
	return this->id;
}

const MyString& Command::getCommandName() const {
	return this->commandName;
}

const MyString& Command::getCommandHelp() const {
	return this->commandHelp;
}

bool Command::operator==(const Command& other) const {
	return this == &other;
}

bool Command::operator!=(const Command& other) const {
	return this != &other;
}

void Command::addRole(Role role) {
	if (this->allowedRoles.indexOf(role) == -1) {
		this->allowedRoles.add(role);
	}
}

void Command::removeRole(Role role) {
	this->allowedRoles.remove(role);
}
