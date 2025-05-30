#include "Course.h"

size_t Course::currentId = 1;

Course::Course(const MyString& name, const MyString& password, size_t creatorId) : name(name), password(password), creatorId(creatorId) {
	this->id = currentId;
	currentId++;
	teacherIds.add(creatorId);
}

size_t Course::getId() const {
	return this->id;
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

bool Course::operator==(const Course& other) const {
	return this->id == other.getId();
}

bool Course::operator!=(const Course& other) const {
	return this->id == other.getId();
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

std::ofstream& operator<<(std::ofstream& stream, const Course& course) {
	if (!stream.is_open()) {
		return stream;
	}

	stream.write(reinterpret_cast<const char*>(&course.id), sizeof(size_t));
	stream.write(reinterpret_cast<const char*>(&course.creatorId), sizeof(size_t));
	stream << course.name;
	stream << course.password;
	stream << course.teacherIds;
	stream << course.studentIds;
	stream << course.assignmentIds;

	return stream;
}
