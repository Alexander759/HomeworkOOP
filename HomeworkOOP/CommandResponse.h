/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#pragma once
#include "MyString.h"

class CommandResponse {
public:
	CommandResponse() = default;
	CommandResponse(bool success, MyString message);
	bool isSuccessful() const;
	const MyString& getMessage() const;

private:
	bool success;
	MyString message;
};