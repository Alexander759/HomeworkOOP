#include "Time.h"
#include <ctime>

Time::Time() : seconds(0), minutes(0), hours(0), days(1), month(1), year(1) {
}

Time Time::getCurrent() {
	Time result;
	time_t now = std::time(nullptr);
	tm currentLocalTime;
	localtime_s(&currentLocalTime, &now);
	result.seconds = currentLocalTime.tm_sec;
	result.minutes = currentLocalTime.tm_min;
	result.hours = currentLocalTime.tm_hour;
	result.days = currentLocalTime.tm_mday;
	result.month = currentLocalTime.tm_mon + 1;
	result.year = currentLocalTime.tm_year + 1900;

	return result;
}

int Time::compare(const Time& first, const Time& second) {
	if (first.year > second.year) {
		return 1;
	}
	else if(first.year < second.year) {
		return -1;
	}

	if (first.month > second.month) {
		return 1;
	}
	else if (first.month < second.month) {
		return -1;
	}

	if (first.days > second.days) {
		return 1;
	}
	else if (first.days < second.days) {
		return -1;
	}

	if (first.hours > second.hours) {
		return 1;
	}
	else if (first.hours < second.hours) {
		return -1;
	}

	if (first.minutes > second.minutes) {
		return 1;
	}
	else if (first.minutes < second.minutes) {
		return -1;
	}

	if (first.seconds > second.seconds) {
		return 1;
	}
	else if (first.seconds < second.seconds) {
		return -1;
	}

	return 0;
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

const MyString Time::toStringFormat() const {
	MyString result;
	result += hours < 10 ? MyString("0") + this->hours : this->hours;
	result += ":";
	result += this->minutes < 10 ? MyString("0") + this->minutes : this->minutes;
	result += " ";
	result += this->days < 10 ? MyString("0") + this->days : this->days ;
	result += ".";
	result += this->month < 10 ? MyString("0") + this->month : this->month;
	result += ".";
	result += this->year;
	
	return result;
}

bool Time::operator==(const Time& other) const {
	return compare(*this, other) == 0;
}

bool Time::operator!=(const Time& other) const {
	return compare(*this, other) != 0;
}

bool Time::operator>(const Time& other) const {
	return compare(*this, other) > 0;
}

bool Time::operator<(const Time& other) const {
	return compare(*this, other) < 0;
}

bool Time::operator>=(const Time& other) const {
	return compare(*this, other) >= 0;
}

bool Time::operator<=(const Time& other) const {
	return compare(*this, other) <= 0;
}

std::ofstream& operator<<(std::ofstream& stream, const Time& time) {
	if (!stream.is_open()) {
		return stream;
	}

	stream.write(reinterpret_cast<const char*>(&time.seconds), sizeof(int));
	stream.write(reinterpret_cast<const char*>(&time.minutes), sizeof(int));
	stream.write(reinterpret_cast<const char*>(&time.days), sizeof(int));
	stream.write(reinterpret_cast<const char*>(&time.month), sizeof(int));
	stream.write(reinterpret_cast<const char*>(&time.year), sizeof(int));

	return stream;
}
