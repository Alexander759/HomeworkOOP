#pragma once
#include <iostream>
#include "MyString.h"
#include "List.hpp"

static class CommandReader {
	static List<MyString> readCommand();
};