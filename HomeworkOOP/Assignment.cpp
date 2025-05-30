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

std::ofstream& operator<<(std::ofstream& stream, const Assignment& assignment) {
	if (!stream.is_open()) {
		return stream;
	}

	stream.write(reinterpret_cast<const char*>(&assignment.id), sizeof(size_t));
	stream.write(reinterpret_cast<const char*>(&assignment.courseId), sizeof(size_t));
	stream << assignment.name;

	return stream;
}
