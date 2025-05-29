#pragma once
#include "MyString.h"

class AssignmentSolution {
public:
	AssignmentSolution();
	AssignmentSolution(size_t studentId, size_t assignmentId, const MyString& solution);

	const size_t getId() const;
	const size_t getStudentId() const;
	const size_t getAssignmentId() const;
	const MyString& getSolution() const;

private:
	static size_t currentId;

	size_t id;
	size_t studentId;
	size_t assignmentId;
	MyString solution;
};