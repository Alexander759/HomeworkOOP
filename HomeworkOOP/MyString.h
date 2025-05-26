#pragma once
#include <iostream>

class MyString {
public:
	MyString();
	MyString(const char* other);
	MyString(const MyString& str);
	MyString(MyString&& str) noexcept;
	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept;
	~MyString();

	void setString(const char* str);
	void setString(const MyString& other);
	const char* getCString() const;
	size_t getLength() const;
	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;
	bool operator>(const MyString& other) const;
	bool operator<(const MyString& other) const;
	bool operator>=(const MyString& other) const;
	bool operator<=(const MyString& other) const;

	MyString& concat(const MyString& str);
	
	MyString operator+(const MyString& str) const;
	MyString& operator+=(const MyString& str);

	friend std::ostream& operator<<(std::ostream& stream, const MyString& string);
private:
	char* content;
	size_t length;

	void copyFrom(const MyString& other);
	void free();
};