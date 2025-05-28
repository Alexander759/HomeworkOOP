#include "Course.h"

Course::Course(const MyString& name, const MyString& password, size_t creatorId) : name(name), password(password), creatorId(creatorId) {
}

const MyString& Course::getName() const {
	return this->name;
}

const MyString& Course::getPassword() const {
	return this->password;
}

size_t Course::getCreatorId() const {
	return this->creatorId;
}

const List<size_t>& Course::getTeacherIds() const {
	return this->teacherIds;
}

const List<size_t>& Course::getStudentIds() const {
	return this->studentIds;
}

const List<size_t>& Course::getAssignmentIds() const {
	return this->assignmentIds;
}

List<size_t>& Course::getTeacherIds() {
	return this->teacherIds;
}

List<size_t>& Course::getStudentIds() {
	return this->studentIds;
}

List<size_t>& Course::getAssignmentIds() {
	return this->assignmentIds;
}

void Course::setName(const MyString& name) {
	this->name = name;
}

void Course::setPassword(const MyString& password) {
	this->password = password;
}
