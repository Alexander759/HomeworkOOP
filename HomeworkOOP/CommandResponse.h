#pragma once
#include "MyString.h"

class CommandResponse {
public:
	CommandResponse(bool success, MyString message);
	bool isSuccessful() const;
	const MyString& getMessage() const;

private:
	bool success;
	MyString message;
};