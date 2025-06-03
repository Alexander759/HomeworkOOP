/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
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

size_t Message::getCurrentId() {
	return Message::currentId;
}

void Message::setCurrentId(size_t currentId) {
	Message::currentId = currentId;
}

std::ofstream& operator<<(std::ofstream& stream, const Message& message) {
	if (!stream.is_open()) {
		return stream;
	}

	stream.write(reinterpret_cast<const char*>(&message.id), sizeof(size_t));
	stream.write(reinterpret_cast<const char*>(&message.senderId), sizeof(size_t));
	stream << message.content;
	stream << message.timeSended;

	return stream;
}

std::ifstream& operator>>(std::ifstream& stream, Message& message) {
	if (!stream.is_open()) {
		return stream;
	}

	stream.read(reinterpret_cast<char*>(&message.id), sizeof(size_t));
	stream.read(reinterpret_cast<char*>(&message.senderId), sizeof(size_t));
	stream >> message.content;
	stream >> message.timeSended;

	return stream;
}
