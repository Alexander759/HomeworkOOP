#pragma once
#include "User.h"
#include "Message.h"
#include "Command.h"
#include "CommandResponse.h"

class System {
public:
	System();
	~System();

	void start();

	const List<User>& getUsers() const;
	const List<Message>& getMessages() const;
	const List<Command>& getCommands() const;
	const List<Role> getCurrentUserRoles() const;

	bool getIsCurrentlyLoggedIn() const;
	size_t getCurrentlyLoggedInId() const;
	void setIsCurrentlyLoggedIn(bool isCurrentlyLoggedIn);
	void setCurrentlyLoggedInId(size_t currentlyLoggedInId);
	User& getUser();


	List<User>& getUsers();
	List<Message>& getMessages();
	List<Command>& getCommands();
private:
	bool isCurrentlyLoggedIn;
	size_t currentlyLoggedInId;
	List<User> users;
	List<Message> messages;
	List<Command> commands;
};