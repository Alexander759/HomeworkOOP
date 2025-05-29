#pragma once
#include <iostream>
#include "MyString.h"
#include "List.hpp"
#include "System.h"
#include "SystemFunctions.h"

int main() {
	System app;

	List<Role> adminList;
	adminList.add(Role::Admin);
	List<Role> teacherList;
	teacherList.add(Role::Teacher);
	List<Role> studentList;
	studentList.add(Role::Student);
	List<Role> guest;
	guest.add(Role::Guest);

	User admin("firstName", "lastName", "password", adminList);
	admin.addRole(Role::Guest);
	app.getUsers().add(admin);
	
	User teacher("Pesho", "Petrov", "pass", teacherList);
	teacher.addRole(Role::Guest);
	app.getUsers().add(teacher);

	User student("Alan", "Alan", "pass", studentList);
	student.addRole(Role::Guest);
	app.getUsers().add(student);

	Command login("login", "",
		SystemFunctions::validateLogin, SystemFunctions::login, guest);
	app.getCommands().add(login);
	
	Command logout(Command("logout", "",
		SystemFunctions::validateLogout, SystemFunctions::logout, guest));
	app.getCommands().add(logout);

	Command messageToAll("message_all", "Sends emails",
		SystemFunctions::validateMessageToAllArgs, SystemFunctions::messageToAll, adminList);
	app.getCommands().add(messageToAll);

	Command message("message", "",
		SystemFunctions::validateMessageArgs, SystemFunctions::message, List<Role>());
	message.addRole(Role::Admin);
	message.addRole(Role::Teacher);
	message.addRole(Role::Student);
	app.getCommands().add(message);

	Command mailBox("mailbox", "", 
		SystemFunctions::validateMailBox, SystemFunctions::mailBox, adminList);
	mailBox.addRole(Role::Admin);
	mailBox.addRole(Role::Student);
	mailBox.addRole(Role::Teacher);
	app.getCommands().add(mailBox);

	Command clearMailBox("clear_mailbox", "",
		SystemFunctions::validateClearMailBox, SystemFunctions::clearMailBox, List<Role>());
	clearMailBox.addRole(Role::Admin);
	clearMailBox.addRole(Role::Teacher);
	clearMailBox.addRole(Role::Student);
	app.getCommands().add(clearMailBox);

	Command addTeacher("add_teacher", "",
		SystemFunctions::validateAddTeacher, SystemFunctions::addTeacher, List<Role>());
	addTeacher.addRole(Role::Admin);
	app.getCommands().add(addTeacher);

	Command addStudent("add_student", "",
		SystemFunctions::validateAddStudent, SystemFunctions::addStudent, List<Role>());
	addStudent.addRole(Role::Admin);
	app.getCommands().add(addStudent);

	Command changePassword("change_password", "",
		SystemFunctions::validateChangePassword, SystemFunctions::changePassword, List<Role>());
	changePassword.addRole(Role::Admin);
	changePassword.addRole(Role::Teacher);
	changePassword.addRole(Role::Student);
	app.getCommands().add(changePassword);

	Command createCourse("create_course", "",
		SystemFunctions::validateCreateCourse, SystemFunctions::createCourse, List<Role>());
	createCourse.addRole(Role::Teacher);
	app.getCommands().add(createCourse);
	
	Command messageToStudents("message_students", "",
		SystemFunctions::validateMessageToStudents, SystemFunctions::messageToStudents, List<Role>());
	messageToStudents.addRole(Role::Teacher);
	app.getCommands().add(messageToStudents);

	Command enroll("enroll", "",
		SystemFunctions::validateEnroll, SystemFunctions::enroll, List<Role>());
	enroll.addRole(Role::Student);
	app.getCommands().add(enroll);

	Command assignHomework("assign_homework", "",
		SystemFunctions::validateAssignHomework, SystemFunctions::assignHomework, List<Role>());
	assignHomework.addRole(Role::Teacher);
	app.getCommands().add(assignHomework);

	Command viewHomework("view_homework", "",
		SystemFunctions::validateViewHomework, SystemFunctions::viewHomework, List<Role>());
	viewHomework.addRole(Role::Student);
	app.getCommands().add(viewHomework);

	Command submitAssignment("submit_assignment", "",
		SystemFunctions::validateSubmitAssignment, SystemFunctions::submitAssignment, List<Role>());
	submitAssignment.addRole(Role::Student);
	app.getCommands().add(submitAssignment);

	Command viewAssignmentSubmissions("view_assignment_submisssions", "",
		SystemFunctions::validateViewAssignmentSubmissions, SystemFunctions::viewAssignmentSubmissions, List<Role>());
	viewAssignmentSubmissions.addRole(Role::Teacher);
	app.getCommands().add(viewAssignmentSubmissions);

	app.start();
}