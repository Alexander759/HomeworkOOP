#pragma once
#include "List.hpp"
#include "AssignmentSolutions.h"

class Assignment {
public:
	Assignment();
	Assignment(const MyString& title, size_t courseId);

	size_t getId() const;
	const MyString& getName() const;
	void setName(const MyString& name);

private:
	static size_t currentId;

	size_t id;
	size_t courseId;
	MyString name;
};