#pragma once
#include "MyString.h"
#include "SystemEmail.h"

class User {
public:
	User(const MyString& firstName, const MyString& lastName);
	virtual ~User() = default;

	const size_t getId() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;

	void setFirstName(const MyString& newFirstName);
	void setLastName(const MyString& newLastName);
private:
	static size_t currentId;
	size_t id;
	MyString firstName;
	MyString lastName;
	SystemEmail systemEmail;
};