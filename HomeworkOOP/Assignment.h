#pragma once
#include "List.hpp"
#include "AssignmentSolutions.h"

class Assignment {
public:
	Assignment();
	Assignment(size_t courseId);

	const List<size_t>& getAssignmentSolutionsIds() const;
	void addSolution(size_t assignmentSolutionId);

private:
	static size_t currentId;

	size_t id;
	size_t courseId;
	List<size_t> solutionIds;
};