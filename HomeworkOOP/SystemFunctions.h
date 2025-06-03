#pragma once
#include "MyString.h"
#include "CommandResponse.h"
/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#include "System.h"

class SystemFunctions {
public:
	static void addCommands(System& system);

	static bool validateMessageToAllArgs(const List<MyString>& args);
	static CommandResponse messageToAll(System& system, const List<MyString>& args);

	static bool validateMessageArgs(const List<MyString>& args);
	static CommandResponse message(System& system, const List<MyString>& args);

	static bool validateLogin(const List<MyString>& args);
	static CommandResponse login(System& system, const List<MyString>& args);

	static bool validateLogout(const List<MyString>& args);
	static CommandResponse logout(System& system, const List<MyString>& args);

	static bool validateMailBox(const List<MyString>& args);
	static CommandResponse mailBox(System& system, const List<MyString>& args);

	static bool validateClearMailBox(const List<MyString>& args);
	static CommandResponse clearMailBox(System& system, const List<MyString>& args);

	static bool validateViewMailBox(const List<MyString>& args);
	static CommandResponse viewMailBox(System& system, const List<MyString>& args);

	static bool validateAddTeacher(const List<MyString>& args);
	static CommandResponse addTeacher(System& system, const List<MyString>& args);

	static bool validateAddStudent(const List<MyString>& args);
	static CommandResponse addStudent(System& system, const List<MyString>& args);

	static bool validateDeleteUser(const List<MyString>& args);
	static CommandResponse deleteUser(System& system, const List<MyString>& args);

	static bool validateChangePassword(const List<MyString>& args);
	static CommandResponse changePassword(System& system, const List<MyString>& args);

	static bool validateCreateCourse(const List<MyString>& args);
	static CommandResponse createCourse(System& system, const List<MyString>& args);

	static bool validateAddToCourse(const List<MyString>& args);
	static CommandResponse addToCourse(System& system, const List<MyString>& args);

	static bool validateMessageToStudents(const List<MyString>& args);
	static CommandResponse messageToStudents(System& system, const List<MyString>& args);

	static bool validateEnroll(const List<MyString>& args);
	static CommandResponse enroll(System& system, const List<MyString>& args);

	static bool validateAssignHomework(const List<MyString>& args);
	static CommandResponse assignHomework(System& system, const List<MyString>& args);

	static bool validateViewHomework(const List<MyString>& args);
	static CommandResponse viewHomework(System& system, const List<MyString>& args);

	static bool validateSubmitAssignment(const List<MyString>& args);
	static CommandResponse submitAssignment(System& system, const List<MyString>& args);

	static bool validateViewAssignmentSubmissions(const List<MyString>& args);
	static CommandResponse viewAssignmentSubmissions(System& system, const List<MyString>& args);

	static bool validateGradeAssignment(const List<MyString>& args);
	static CommandResponse gradeAssignment(System& system, const List<MyString>& args);

	static bool validateViewGrades(const List<MyString>& args);
	static CommandResponse viewGrades(System& system, const List<MyString>& args);

	static bool validateHelp(const List<MyString>& args);
	static CommandResponse help(System& system, const List<MyString>& args);

};