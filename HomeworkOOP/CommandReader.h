#pragma once
#include <iostream>
#include "MyString.h"
#include "List.hpp"

static class CommandReader {
public:
	static List<MyString> readCommand();
};