#include "Assignment.h"

size_t Assignment::currentId = 1;

Assignment::Assignment() {
	this->id = currentId;
	currentId++;
}

Assignment::Assignment(const MyString& name, size_t courseId) {
	this->id = currentId;
	currentId++;

	this->name = name;
	this->courseId = courseId;
}

size_t Assignment::getId() const {
	return this->id;
}

const MyString& Assignment::getName() const {
	return this->name;
}

void Assignment::setName(const MyString& name) {
	this->name = name;
}
