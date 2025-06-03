/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#pragma once
#include <fstream>
#include "MyString.h"
#include "Time.h"

class Message {
public:
	Message() = default;
	Message(size_t senderId, MyString content);

	const size_t getId() const;
	const size_t getSenderId() const;
	const MyString& getContent() const;
	const Time& getTimeSended() const;
	bool operator==(const Message& other) const;
	bool operator!=(const Message& other) const;
	friend std::ofstream& operator<<(std::ofstream& stream, const Message& message);
	friend std::ifstream& operator>>(std::ifstream& stream, Message& message);

	static size_t getCurrentId();
	static void setCurrentId(size_t currentId);

private:
	size_t id;
	size_t senderId;
	MyString content;
	Time timeSended;

	static size_t currentId;
};