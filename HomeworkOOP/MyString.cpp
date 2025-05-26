#include "MyString.h"
#include <iostream>
#include <cstring>

MyString::MyString() {
    this->length = 0;
    this->content = new char[1];
    this->content[0] = '\0';
}

MyString::MyString(const char* str) {
    if (str == nullptr) {
        this->length = 0;
        this->content = new char[1];
        this->content[0] = '\0';
        return;
    }

    this->length = strlen(str);
    this->content = new char[this->length + 1];
    strcpy_s(this->content, this->length + 1, str);
}

MyString::MyString(const MyString& other) {
    this->copyFrom(other);
}

MyString::MyString(MyString&& str) noexcept {
    this->length = str.length;
    this->content = str.content;
    str.content = nullptr;
    str.length = 0;
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        this->free();
        this->copyFrom(other);
    }

    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        this->free();
        this->length = other.length;
        this->content = other.content;
        other.content = nullptr;
        other.length = 0;
    }

    return *this;
}

MyString::~MyString() {
    this->free();
}

void MyString::setString(const char* str) {
    if (str == nullptr) {
        return;
    }

    delete[] this->content;

    this->length = strlen(str);
    this->content = new char[this->length + 1];
    strcpy_s(this->content, this->length + 1, str);
}

void MyString::setString(const MyString& other) {
    this->setString(other.getCString());
}

const char* MyString::getCString() const {
    return this->content;
}

size_t MyString::getLength() const {
    return this->length;
}

bool MyString::operator==(const MyString& other) const {
    return strcmp(this->content, other.getCString()) == 0;
}

bool MyString::operator!=(const MyString& other) const {
    return strcmp(this->content, other.getCString()) != 0;
}

bool MyString::operator>(const MyString& other) const {
    return strcmp(this->content, other.getCString()) > 0;
}

bool MyString::operator<(const MyString& other) const {
    return strcmp(this->content, other.getCString()) < 0;
}

bool MyString::operator>=(const MyString& other) const {
    return strcmp(this->content, other.getCString()) > -1;
}

bool MyString::operator<=(const MyString& other) const {
    return strcmp(this->content, other.getCString()) < 1;
}

MyString& MyString::concat(const MyString& str) {
    size_t newLength =  this->length + str.getLength();
    char* newContent = new char[newLength + 1];

    strcpy_s(newContent, newLength + 1, this->content);
    strcat_s(newContent, newLength + 1, str.getCString());

    delete[] this->content;
    this->length = newLength;
    this->content = newContent;
    return *this;
}

MyString MyString::operator+(const MyString& str) const {
    MyString result(*this);
    result.concat(str);
    return result;
}

MyString& MyString::operator+=(const MyString& str) {
    this->concat(str);
    return *this;
}

void MyString::copyFrom(const MyString& other) {
    this->length = other.getLength();
    this->content = new char[this->length + 1];
    strcpy_s(this->content, this->length + 1, other.getCString());
}

void MyString::free() {
    delete[] this->content;
    this->content = nullptr;
    this->length = 0;
}

std::ostream& operator<<(std::ostream& stream, const MyString& string) {
    stream << string.content;
    return stream;
}