#include "User.h"

size_t User::currentId = 1;

User::User(const MyString& firstName, const MyString& lastName) {
    this->id = currentId;
    currentId++;
    this->setFirstName(firstName);
    this->setLastName(lastName);
}

const size_t User::getId() const {
    return this->id;
}

const MyString& User::getFirstName() const {
    return this->firstName;
}

const MyString& User::getLastName() const {
    return this->lastName;
}

void User::setFirstName(const MyString& newFirstName) {
    this->firstName = newFirstName;
}

void User::setLastName(const MyString& newLastName) {
    this->lastName = newLastName;
}
