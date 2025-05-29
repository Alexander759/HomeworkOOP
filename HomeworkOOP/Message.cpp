#include "Message.h"

size_t Message::currentId = 1;

Message::Message(size_t senderId, MyString content) {
	this->id = currentId;
	currentId++;
	this->senderId = senderId;
	this->content = content;
	this->timeSended = Time::getCurrent();
}
const size_t Message::getId() const {
	return this->id;
}
const size_t Message::getSenderId() const {
	return this->senderId;
}

const MyString& Message::getContent() const {
	return this->content;
}

const Time& Message::getTimeSended() const {
	return this->timeSended;
}

bool Message::operator==(const Message& other) const {
	return this == &other;
}

bool Message::operator!=(const Message& other) const {
	return this != &other;
}
