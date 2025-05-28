#pragma once
#include "MyString.h"
#include "CommandResponse.h"
#include "System.h"

class SystemFunctions {
public:
	static bool validateMessageToAllArgs(const List<MyString>& args);
	static CommandResponse messageToAll(System& system, const List<MyString>& args);

	static bool validateLogin(const List<MyString>& args);
	static CommandResponse login(System& system, const List<MyString>& args);

	static bool validateLogout(const List<MyString>& args);
	static CommandResponse logout(System& system, const List<MyString>& args);

	static bool validateMailBox(const List<MyString>& args);
	static CommandResponse mailBox(System& system, const List<MyString>& args);

	static bool validateClearMailBox(const List<MyString>& args);
	static CommandResponse clearMailBox(System& system, const List<MyString>& args);

};