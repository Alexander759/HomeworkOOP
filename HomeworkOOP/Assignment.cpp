/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#include "Assignment.h"

size_t Assignment::currentId = 1;

Assignment::Assignment(const MyString& name, size_t courseId) {
	this->id = currentId;
	currentId++;

	this->name = name;
	this->courseId = courseId;
}

size_t Assignment::getId() const {
	return this->id;
}

size_t Assignment::getCourseId() const {
	return this->courseId;
}

const MyString& Assignment::getName() const {
	return this->name;
}

bool Assignment::operator==(const Assignment& other) const {
	return this->id == other.getId();
}

bool Assignment::operator!=(const Assignment& other) const {
	return this->id != other.getId();
}

void Assignment::setName(const MyString& name) {
	this->name = name;
}

size_t Assignment::getCurrentId() {
	return Assignment::currentId;
}

void Assignment::setCurrentId(size_t currentId) {
	Assignment::currentId = currentId;
}

std::ofstream& operator<<(std::ofstream& stream, const Assignment& assignment) {
	if (!stream.is_open()) {
		return stream;
	}

	stream.write(reinterpret_cast<const char*>(&assignment.id), sizeof(size_t));
	stream.write(reinterpret_cast<const char*>(&assignment.courseId), sizeof(size_t));
	stream << assignment.name;

	return stream;
}

std::ifstream& operator>>(std::ifstream& stream, Assignment& assignment) {
	if (!stream.is_open()) {
		return stream;
	}

	stream.read(reinterpret_cast<char*>(&assignment.id), sizeof(size_t));
	stream.read(reinterpret_cast<char*>(&assignment.courseId), sizeof(size_t));
	stream >> assignment.name;

	return stream;
}
