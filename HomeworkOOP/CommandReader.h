/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#pragma once
#include <iostream>
#include "MyString.h"
#include "List.hpp"

static class CommandReader {
public:
	static List<MyString> readCommand();
};