#pragma once

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

	bool operator==(const Time& other) const;
	bool operator!=(const Time& other) const;
	bool operator>(const Time& other) const;
	bool operator<(const Time& other) const;
	bool operator>=(const Time& other) const;
	bool operator<=(const Time& other) const;
private:
	int seconds;
	int minutes;
	int hours;
	int days;
	int month;
	int year;
};
