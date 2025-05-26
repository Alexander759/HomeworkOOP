#include "Message.h"

Message::Message(User* sender, MyString content) {
	this->sender = sender;
	this->content = content;
	this->timeSended = Time::getCurrent();
}

const User* Message::getSender() const {
	return this->sender;
}

const MyString& Message::getContent() const {
	return this->content;
}

const Time& Message::getTimeSended() const {
	return this->timeSended;
}
