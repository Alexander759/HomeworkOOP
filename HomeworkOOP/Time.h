/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#pragma once
#include "MyString.h"
#include <fstream>

class Time {
public:
	Time();
	static Time getCurrent();
	static int compare(const Time& first, const Time& second);

	int getSeconds() const;
	int getMinutes() const;
	int getHours() const;
	int getDays() const;
	int getMonth() const;
	int getYear() const;
	const MyString toStringFormat() const;

	bool operator==(const Time& other) const;
	bool operator!=(const Time& other) const;
	bool operator>(const Time& other) const;
	bool operator<(const Time& other) const;
	bool operator>=(const Time& other) const;
	bool operator<=(const Time& other) const;

	friend std::ofstream& operator<<(std::ofstream& stream, const Time& time);
	friend std::ifstream& operator>>(std::ifstream& stream, Time& time);
private:
	int seconds;
	int minutes;
	int hours;
	int days;
	int month;
	int year;
};
