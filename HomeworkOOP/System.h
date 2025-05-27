#pragma once
#include "User.h"
#include "Message.h"
#include "Command.h"

class CommandResponse;

class System {
public:
	const List<User>& getUsers() const;
	const List<Message>& getMessages() const;
	const List<Command>& getCommands() const;

	List<User>& getUsers();
	List<Message>& getMessages();
	List<Command>& getCommands();

	static bool validateMessageToAllArgs(const List<MyString>& args);
	static CommandResponse messageToAll(User& user, System& system, const List<MyString>& args);

private:
	List<User> users;
	List<Message> messages;
	List<Command> commands;
};