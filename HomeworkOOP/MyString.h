/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#pragma once
#include <iostream>
#include <fstream>
#include "List.hpp"

class MyString {
public:
	MyString();
	MyString(size_t num);
	MyString(int num);
	MyString(double num);
	MyString(const char* other);
	MyString(const MyString& str);
	MyString(MyString&& str) noexcept;
	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept;
	~MyString();

	void setString(const char* str);
	void setString(const MyString& other);
	const char* getCString() const;
	MyString subStr(size_t start, size_t end) const;
	List<MyString> separate(char separator = ' ') const;
	size_t getLength() const;
	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;
	bool operator>(const MyString& other) const;
	bool operator<(const MyString& other) const;
	bool operator>=(const MyString& other) const;
	bool operator<=(const MyString& other) const;
	
	bool isDouble() const;
	double toDouble() const;

	bool isSizeT() const;
	size_t toSizeT() const;

	MyString& concat(const MyString& str);
	MyString& reverse();
	
	MyString operator+(const MyString& str) const;
	MyString& operator+=(const MyString& str);

	friend std::ofstream& operator<<(std::ofstream& stream, const MyString& string);
	friend std::ifstream& operator>>(std::ifstream& stream, MyString& string);


	friend std::ostream& operator<<(std::ostream& stream, const MyString& string);
	friend std::istream& operator>>(std::istream& stream, MyString& string);
private:
	char* content;
	size_t length;

	void copyFrom(const MyString& other);
	void free();
};