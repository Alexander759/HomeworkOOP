#pragma once
#include <iostream>
#include "MyString.h"
#include "List.hpp"
#include "System.h"
#include "SystemFunctions.h"

int main() {
	System app("file.bin");

	List<Role> adminList;
	adminList.add(Role::Admin);
	List<Role> teacherList;
	teacherList.add(Role::Teacher);
	List<Role> studentList;
	studentList.add(Role::Student);
	List<Role> guest;
	guest.add(Role::Guest);

	/*User admin("admin", "", "0000", adminList);
	admin.addRole(Role::Guest);
	app.getUsers().add(admin);*/

	//User::setCurrentId(100);

	Command login("login", "[id] [password]",
		SystemFunctions::validateLogin, SystemFunctions::login, List<Role>());
	login.addRole(Role::Guest);
	app.getCommands().add(login);
	
	Command logout(Command("logout", "[no arguments]",
		SystemFunctions::validateLogout, SystemFunctions::logout, List<Role>()));
	logout.addRole(Role::Guest);
	app.getCommands().add(logout);

	Command messageToAll("message_all", "[text]",
		SystemFunctions::validateMessageToAllArgs, SystemFunctions::messageToAll, List<Role>());
	messageToAll.addRole(Role::Admin);
	app.getCommands().add(messageToAll);

	Command message("message", "[userId] [text]",
		SystemFunctions::validateMessageArgs, SystemFunctions::message, List<Role>());
	message.addRole(Role::Admin);
	message.addRole(Role::Teacher);
	message.addRole(Role::Student);
	app.getCommands().add(message);

	Command mailBox("mailbox", "[no arguments]", 
		SystemFunctions::validateMailBox, SystemFunctions::mailBox, adminList);
	mailBox.addRole(Role::Admin);
	mailBox.addRole(Role::Student);
	mailBox.addRole(Role::Teacher);
	app.getCommands().add(mailBox);

	Command clearMailBox("clear_mailbox", "[no arguments]",
		SystemFunctions::validateClearMailBox, SystemFunctions::clearMailBox, List<Role>());
	clearMailBox.addRole(Role::Admin);
	clearMailBox.addRole(Role::Teacher);
	clearMailBox.addRole(Role::Student);
	app.getCommands().add(clearMailBox);

	Command viewMailBox("view_mailbox", "[userId]",
		SystemFunctions::validateViewMailBox, SystemFunctions::viewMailBox, List<Role>());
	viewMailBox.addRole(Role::Admin);
	app.getCommands().add(viewMailBox);

	Command addTeacher("add_teacher", "[firstName] [lastName] [password]",
		SystemFunctions::validateAddTeacher, SystemFunctions::addTeacher, List<Role>());
	addTeacher.addRole(Role::Admin);
	app.getCommands().add(addTeacher);

	Command addStudent("add_student", "[firstName] [lastName] [password]",
		SystemFunctions::validateAddStudent, SystemFunctions::addStudent, List<Role>());
	addStudent.addRole(Role::Admin);
	app.getCommands().add(addStudent);

	Command changePassword("change_password", "[oldPassword] [newPassword]",
		SystemFunctions::validateChangePassword, SystemFunctions::changePassword, List<Role>());
	changePassword.addRole(Role::Admin);
	changePassword.addRole(Role::Teacher);
	changePassword.addRole(Role::Student);
	app.getCommands().add(changePassword);

	Command createCourse("create_course", "[courseName]",
		SystemFunctions::validateCreateCourse, SystemFunctions::createCourse, List<Role>());
	createCourse.addRole(Role::Teacher);
	app.getCommands().add(createCourse);
	
	Command addToCourse("add_to_course", "[courseName] [studentID]",
		SystemFunctions::validateAddToCourse, SystemFunctions::addToCourse, List<Role>());
	addToCourse.addRole(Role::Teacher);
	app.getCommands().add(addToCourse);

	Command messageToStudents("message_students", "[courseName] [text]",
		SystemFunctions::validateMessageToStudents, SystemFunctions::messageToStudents, List<Role>());
	messageToStudents.addRole(Role::Teacher);
	app.getCommands().add(messageToStudents);

	Command enroll("enroll", "[courseName] [coursePassword]",
		SystemFunctions::validateEnroll, SystemFunctions::enroll, List<Role>());
	enroll.addRole(Role::Student);
	app.getCommands().add(enroll);

	Command assignHomework("assign_homework", "[courseName] [assignmentName]",
		SystemFunctions::validateAssignHomework, SystemFunctions::assignHomework, List<Role>());
	assignHomework.addRole(Role::Teacher);
	app.getCommands().add(assignHomework);

	Command viewHomework("view_homework", "[no arguments]",
		SystemFunctions::validateViewHomework, SystemFunctions::viewHomework, List<Role>());
	viewHomework.addRole(Role::Student);
	app.getCommands().add(viewHomework);

	Command submitAssignment("submit_assignment", "[courseName] [assignmentName] [text]",
		SystemFunctions::validateSubmitAssignment, SystemFunctions::submitAssignment, List<Role>());
	submitAssignment.addRole(Role::Student);
	app.getCommands().add(submitAssignment);

	Command viewAssignmentSubmissions("view_assignment_submissions", "[courseName] [assignmentName]",
		SystemFunctions::validateViewAssignmentSubmissions, SystemFunctions::viewAssignmentSubmissions, List<Role>());
	viewAssignmentSubmissions.addRole(Role::Teacher);
	app.getCommands().add(viewAssignmentSubmissions);

	Command gradeAssignment("grade_assignment", "[courseName] [assignmentName] [studentID] [Grade] [Message]",
		SystemFunctions::validateGradeAssignment, SystemFunctions::gradeAssignment, List<Role>());
	gradeAssignment.addRole(Role::Teacher);
	app.getCommands().add(gradeAssignment);

	Command viewGrades("grades", "[no arguments]",
		SystemFunctions::validateViewGrades, SystemFunctions::viewGrades, List<Role>());
	viewGrades.addRole(Role::Student);
	app.getCommands().add(viewGrades);

	Command help("help", "[no arguments]",
		SystemFunctions::validateHelp, SystemFunctions::help, List<Role>());
	help.addRole(Role::Guest);
	app.getCommands().add(help);

	app.start();
}