#include "Assignment.h"

size_t Assignment::currentId = 1;

Assignment::Assignment() {
	this->id = currentId;
	currentId++;
}

Assignment::Assignment(size_t courseId) {
	this->id = currentId;
	currentId++;

	this->courseId = courseId;
}

const List<size_t>& Assignment::getAssignmentSolutionsIds() const {
	return this->solutionIds;
}

void Assignment::addSolution(size_t assignmentSolutionId) {
	this->solutionIds.add(assignmentSolutionId);
}
