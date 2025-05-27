#pragma once
#include "Role.h"
#include "List.hpp"
#include "CommandResponse.h"
#include "User.h"

class System;

class Command {
public:
	Command();
	Command(const MyString& commandName, bool (*validateArgsPtr)(const List<MyString>& args),
		CommandResponse(*commandPtr)(User& user, System& system, const List<MyString>& args),
		const List<Role>& allowedRoles);
	CommandResponse run(User& user, System& system, const List<MyString>& args);
	bool userHasAllowedRole(const User& user);
	bool validateArgs(const List<MyString>& args);
	bool operator==(const Command& other) const;
	bool operator!=(const Command& other) const;
private:
	MyString commandName;
	bool (*validateArgsPtr)(const List<MyString>& args);
	CommandResponse (*commandPtr)(User& user, System& system, const List<MyString>& args);
	List<Role> allowedRoles;
};