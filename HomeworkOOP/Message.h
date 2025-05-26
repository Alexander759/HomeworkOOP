#pragma once
#include "MyString.h"
#include "Time.h"
#include "User.h"

class Message {
public:
	Message(User* sender, MyString content);

	const User* getSender() const;
	const MyString& getContent() const;
	const Time& getTimeSended() const;
private:
	User* sender;
	MyString content;
	Time timeSended;
};