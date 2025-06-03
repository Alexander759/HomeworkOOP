/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#pragma once
#include "List.hpp"
#include "AssignmentSolution.h"

class Assignment {
public:
	Assignment() = default;
	Assignment(const MyString& title, size_t courseId);

	size_t getId() const;
	size_t getCourseId() const;
	const MyString& getName() const;
	bool operator==(const Assignment& other) const;
	bool operator!=(const Assignment& other) const;
	void setName(const MyString& name);

	friend std::ofstream& operator<<(std::ofstream& stream, const Assignment& assignment);
	friend std::ifstream& operator>>(std::ifstream& stream, Assignment& assignment);

	static size_t getCurrentId();
	static void setCurrentId(size_t currentId);

private:
	size_t id;
	size_t courseId;
	MyString name;

	static size_t currentId;
};