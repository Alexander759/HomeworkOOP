#pragma once
#include "MyString.h"

class Grade {
public:
	Grade() = default;
	Grade(double grade, size_t studentId, size_t assignmentId, size_t teacherId, const MyString& message);

	double getGrade() const;
	size_t getStudentId() const;
	size_t getAssignmentSolutionId() const;
	size_t getTeacherId() const;
	const MyString& getMessage() const;

	void setGrade(double grade);
	void setStudentId(size_t studentId);
	void setAssignmenSolutiontId(size_t assignmenSolutiontId);
	void setTeacherId(size_t teacherId);
	void setMessage(const MyString& message);

private:
	static size_t currentId;

	size_t id;
	double grade;
	size_t studentId;
	size_t assignmentSolutionId;
	size_t teacherId;
	MyString message;
};