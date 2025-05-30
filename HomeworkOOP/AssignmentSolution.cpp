#include "AssignmentSolution.h"

size_t AssignmentSolution::currentId = 1;

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

bool AssignmentSolution::operator==(const AssignmentSolution& other) const {
	return this->id == other.getId();
}

bool AssignmentSolution::operator!=(const AssignmentSolution& other) const {
	return this->id == other.getId();
}

size_t AssignmentSolution::getCurrentId() {
	return AssignmentSolution::currentId;
}

void AssignmentSolution::setCurrentId(size_t currentId) {
	AssignmentSolution::currentId = currentId;
}

std::ofstream& operator<<(std::ofstream& stream, const AssignmentSolution& assignmentSolution) {
	if (!stream.is_open()) {
		return stream;
	}

	stream.write(reinterpret_cast<const char*>(&assignmentSolution.id), sizeof(size_t));
	stream.write(reinterpret_cast<const char*>(&assignmentSolution.studentId), sizeof(size_t));
	stream.write(reinterpret_cast<const char*>(&assignmentSolution.assignmentId), sizeof(size_t));
	stream << assignmentSolution.solution;
	return stream;
}

std::ifstream& operator>>(std::ifstream& stream, AssignmentSolution& assignmentSolution) {
	if (!stream.is_open()) {
		return stream;
	}

	stream.read(reinterpret_cast<char*>(&assignmentSolution.id), sizeof(size_t));
	stream.read(reinterpret_cast<char*>(&assignmentSolution.studentId), sizeof(size_t));
	stream.read(reinterpret_cast<char*>(&assignmentSolution.assignmentId), sizeof(size_t));
	stream >> assignmentSolution.solution;
	return stream;
}
