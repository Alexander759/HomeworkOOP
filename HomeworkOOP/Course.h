#pragma once
#include "User.h"
#include <fstream>

class Course {
public:
	Course() = default;
	Course(const MyString& name, const MyString& password, size_t creatorId);

	size_t getId() const;
	const MyString& getName() const;
	const MyString& getPassword() const;
	size_t getCreatorId() const;
	const List<size_t>& getTeacherIds() const;
	const List<size_t>& getStudentIds() const;
	const List<size_t>& getAssignmentIds() const;
	bool operator==(const Course& other) const;
	bool operator!=(const Course& other) const;

	friend std::ofstream& operator<<(std::ofstream& stream, const Course& course);
	friend std::ifstream& operator>>(std::ifstream& stream, Course& course);

	List<size_t>& getTeacherIds();
	List<size_t>& getStudentIds();
	List<size_t>& getAssignmentIds();

	void setName(const MyString& name);
	void setPassword(const MyString& password);

	static size_t getCurrentId();
	static void setCurrentId(size_t currentId);

private:
	size_t id;
	size_t creatorId;
	MyString name;
	MyString password;
	List<size_t> teacherIds;
	List<size_t> studentIds;
	List<size_t> assignmentIds;

	static size_t currentId; 
};