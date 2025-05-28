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
	
	User student("Alan", "Alan", "pass", studentList);
	student.addRole(Role::Guest);
	app.getUsers().add(student);

	Command login("login", "",
		SystemFunctions::validateLogin, SystemFunctions::login, guest);
	app.getCommands().add(login);
	
	Command logout(Command("logout", "",
		SystemFunctions::validateLogout, SystemFunctions::logout, guest));
	app.getCommands().add(logout);

	Command sendToAll("send_to_all", "Sends emails",
		SystemFunctions::validateMessageToAllArgs, SystemFunctions::messageToAll, adminList);
	app.getCommands().add(sendToAll);

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

	app.start();
}