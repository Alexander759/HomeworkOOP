#pragma once
#include "MyString.h"
#include <fstream>

class Grade {
public:
	Grade() = default;
	Grade(double grade, size_t studentId, size_t assignmentId, size_t teacherId, const MyString& message);

	size_t getId() const;
	double getGrade() const;
	size_t getStudentId() const;
	size_t getAssignmentSolutionId() const;
	size_t getTeacherId() const;
	const MyString& getMessage() const;
	bool operator==(const Grade& other) const;
	bool operator!=(const Grade& other) const;

	friend std::ofstream& operator<<(std::ofstream& stream, const Grade& grade);
	friend std::ifstream& operator>>(std::ifstream& stream, Grade& grade);

	void setGrade(double grade);
	void setStudentId(size_t studentId);
	void setAssignmenSolutiontId(size_t assignmenSolutiontId);
	void setTeacherId(size_t teacherId);
	void setMessage(const MyString& message);

	static size_t getCurrentId();
	static void setCurrentId(size_t currentId);

private:
	size_t id;
	double grade;
	size_t studentId;
	size_t assignmentSolutionId;
	size_t teacherId;
	MyString message;

	static size_t currentId;
};