#pragma once
#include "MyString.h"

class AssignmentSolution {
public:
	AssignmentSolution() = default;
	AssignmentSolution(size_t studentId, size_t assignmentId, const MyString& solution);

	const size_t getId() const;
	const size_t getStudentId() const;
	const size_t getAssignmentId() const;
	const MyString& getSolution() const;
	bool operator==(const AssignmentSolution& other) const;
	bool operator!=(const AssignmentSolution& other) const;

	friend std::ofstream& operator<<(std::ofstream& stream, const AssignmentSolution& assignmentSolution);

private:
	static size_t currentId;

	size_t id;
	size_t studentId;
	size_t assignmentId;
	MyString solution;
};