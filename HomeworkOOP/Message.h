#pragma once
#include "MyString.h"
#include "Time.h"

class User;

class Message {
public:
	Message();
	Message(size_t senderId, MyString content);

	const size_t getId() const;
	const size_t getSenderId() const;
	const MyString& getContent() const;
	const Time& getTimeSended() const;
	bool operator==(const Message& other) const;
	bool operator!=(const Message& other) const;
private:
	static size_t currentId;
	size_t id;
	size_t senderId;
	//User* sender;
	MyString content;
	Time timeSended;
};