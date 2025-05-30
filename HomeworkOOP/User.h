#pragma once
#include "MyString.h"
#include "SystemEmail.h"
#include "Role.h"

class User {
public:
	User() = default;
	User(const MyString& firstName, const MyString& lastName, const MyString& password, const List<Role>& roles);
	virtual ~User() = default;

	const size_t getId() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const MyString getFullName() const;
	const MyString& getPassword() const;
	const List<Role>& getRoles() const;
	const SystemEmail& getMailBox() const;
	SystemEmail& getMailBox();
	bool isInRole(Role role) const;
	MyString getMainRole() const;
	bool operator==(const User& user) const;
	bool operator!=(const User& user) const;
	friend std::ofstream& operator<<(std::ofstream& stream, const User& user);
	friend std::ifstream& operator>>(std::ifstream& stream, User& user);


	void setFirstName(const MyString& newFirstName);
	void setLastName(const MyString& newLastName);
	void setPassword(const MyString& password);
	void addRole(Role role);
	void removeRole(Role role);
	void getNewMessage(size_t message);
	
	static size_t getCurrentId();
	static void setCurrentId(size_t currentId);
private:
	size_t id;
	MyString firstName;
	MyString lastName;
	MyString password;
	SystemEmail systemEmail;
	List<Role> roles;
	
	static size_t currentId;
};