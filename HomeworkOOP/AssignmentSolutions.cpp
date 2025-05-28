#include "AssignmentSolutions.h"

size_t AssignmentSolutions::currentId = 1;

AssignmentSolutions::AssignmentSolutions() {
	this->id = currentId;
	currentId++;
}

AssignmentSolutions::AssignmentSolutions(size_t studentId, size_t assignmentId, const MyString& solution)
	:studentId(studentId), assignmentId(assignmentId), solution(solution) {
	this->id = currentId;
	currentId++;
}

const size_t AssignmentSolutions::getId() const {
	return this->id;
}

const size_t AssignmentSolutions::getStudentId() const {
	return this->studentId;
}

const size_t AssignmentSolutions::getAssignmentId() const {
	return this->assignmentId;
}

const MyString& AssignmentSolutions::getSolution() const {
	return this->solution;
}
