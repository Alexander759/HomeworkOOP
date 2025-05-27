#include <iostream>
#include "MyString.h"
#include "List.hpp"
#include "System.h"

int main()
{
	System app;

	List<Role> adminList;
	adminList.add(Role::Admin);
	List<Role> teacherList;
	teacherList.add(Role::Teacher);
	List<Role> studentList;
	studentList.add(Role::Student);

	app.getCommands().add(Command("send_to_all", System::validateMessageToAllArgs, System::messageToAll, adminList));
}