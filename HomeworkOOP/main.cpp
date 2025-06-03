/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/

#pragma once
#include <iostream>
#include "MyString.h"
#include "List.hpp"
#include "System.h"
#include "SystemFunctions.h"

int main() {
	System app("file.bin");

	//Remove to generate new file
	app.readFromFile();

	//Add to generate file
	/*User admin("admin", "", "0000", List<Role>());
	admin.addRole(Role::Admin);
	admin.addRole(Role::Guest);
	app.getUsers().add(admin);*/

	User::setCurrentId(100);

	SystemFunctions::addCommands(app);

	app.start();
}