#pragma once
#include "User.h"
#include "Message.h"
#include "Command.h"
#include "CommandResponse.h"
#include "Course.h"
#include "Assignment.h"
#include "Grade.h"

class System {
public:
	System(const MyString& filename);
	~System();

	void start();

	const List<User>& getUsers() const;
	const List<Message>& getMessages() const;
	const List<Command>& getCommands() const;
	const List<Course>& getCourses() const;
	const List<Assignment>& getAssignments() const;
	const List<AssignmentSolution>& getAssignmentSolutions() const;
	const List<Grade>& getGrades() const;

	const List<Role> getCurrentUserRoles() const;

	bool getIsCurrentlyLoggedIn() const;
	size_t getCurrentlyLoggedInId() const;
	void setIsCurrentlyLoggedIn(bool isCurrentlyLoggedIn);
	void setCurrentlyLoggedInId(size_t currentlyLoggedInId);
	User& getUser();

	List<User>& getUsers();
	List<Message>& getMessages();
	List<Course>& getCourses();
	List<Assignment>& getAssignments();
	List<AssignmentSolution>& getAssignmentSolutions();
	List<Grade>& getGrades();

	List<Command>& getCommands();

	void saveToFile() const;
	void readFromFile();
private:
	MyString fileName;
	bool isCurrentlyLoggedIn;
	size_t currentlyLoggedInId;
	List<User> users;
	List<Message> messages;
	List<Command> commands;
	List<Course> courses;
	List<Assignment> assignments;
	List<AssignmentSolution> assignmentSolutions;
	List<Grade> grades;
};