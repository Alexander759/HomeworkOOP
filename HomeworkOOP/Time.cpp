#include "Time.h"
#include <ctime>

Time::Time() : seconds(0), minutes(0), hours(0), days(1), month(1), year(1) {
}

Time Time::getCurrent() {
	Time result;
	time_t now = std::time(nullptr);
	tm* currentLocalTime = std::localtime(&now);
	result.seconds = currentLocalTime->tm_sec;
	result.minutes = currentLocalTime->tm_min;
	result.hours = currentLocalTime->tm_hour;
	result.days = currentLocalTime->tm_mday;
	result.month = currentLocalTime->tm_mon + 1;
	result.year = currentLocalTime->tm_year + 1900;

	return result;
}

int Time::compare(const Time& first, const Time& second) {
}

int Time::getSeconds() const {
	return this->seconds;
}

int Time::getMinutes() const {
	return this->minutes;
}

int Time::getHours() const {
	return this->hours;
}

int Time::getDays() const {
	return this->days;
}

int Time::getMonth() const {
	return this->month;
}

int Time::getYear() const {
	return this->year;
}
