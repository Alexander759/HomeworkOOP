#pragma once
#include "Role.h"
#include "List.hpp"
#include "CommandResponse.h"
/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#include "User.h"

class System;

class Command {
public:
	Command() = default;
	Command(const MyString& commandName, const MyString& commandHelp,
		bool (*validateArgsPtr)(const List<MyString>& args),
		CommandResponse(*commandPtr)(System& system, const List<MyString>& args),
		const List<Role>& allowedRoles);
	CommandResponse run(System& system, const List<MyString>& args);
	bool userHasAllowedRole(const List<Role>& roles);
	bool validateArgs(const List<MyString>& args);

	size_t getId() const;
	const MyString& getCommandName() const;
	const MyString& getCommandHelp() const;
	bool operator==(const Command& other) const;
	bool operator!=(const Command& other) const;
	const MyString getFullCommandHelp() const;
	void addRole(Role role);
	void removeRole(Role role);
private:
	static size_t currentId;
	
	size_t id;
	MyString commandName;
	MyString commandHelp;
	bool (*validateArgsPtr)(const List<MyString>& args);
	CommandResponse(*commandPtr)(System& system, const List<MyString>& args);
	List<Role> allowedRoles;
};