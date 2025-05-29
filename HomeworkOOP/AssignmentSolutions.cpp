#include "AssignmentSolution.h"

size_t AssignmentSolution::currentId = 1;

AssignmentSolution::AssignmentSolution() {
	this->id = currentId;
	currentId++;
}

AssignmentSolution::AssignmentSolution(size_t studentId, size_t assignmentId, const MyString& solution)
	:studentId(studentId), assignmentId(assignmentId), solution(solution) {
	this->id = currentId;
	currentId++;
}

const size_t AssignmentSolution::getId() const {
	return this->id;
}

const size_t AssignmentSolution::getStudentId() const {
	return this->studentId;
}

const size_t AssignmentSolution::getAssignmentId() const {
	return this->assignmentId;
}

const MyString& AssignmentSolution::getSolution() const {
	return this->solution;
}
