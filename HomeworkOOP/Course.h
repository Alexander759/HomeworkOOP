#pragma once
#include "User.h"

class Course {
public:
	Course();
	Course(const MyString& name, const MyString& password, size_t creatorId);

	size_t getId() const;
	const MyString& getName() const;
	const MyString& getPassword() const;
	size_t getCreatorId() const;
	const List<size_t>& getTeacherIds() const;
	const List<size_t>& getStudentIds() const;
	const List<size_t>& getAssignmentIds() const;

	List<size_t>& getTeacherIds();
	List<size_t>& getStudentIds();
	List<size_t>& getAssignmentIds();

	void setName(const MyString& name);
	void setPassword(const MyString& password);
private:
	static size_t currentId;

	size_t id;
	MyString name;
	MyString password;
	size_t creatorId;
	List<size_t> teacherIds;
	List<size_t> studentIds;
	List<size_t> assignmentIds;
};