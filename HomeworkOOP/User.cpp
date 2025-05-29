#include "User.h"

size_t User::currentId = 1;

User::User(const MyString& firstName, const MyString& lastName, const MyString& password, const List<Role>& roles) {
    this->id = currentId;
    currentId++;
    this->setFirstName(firstName);
    this->setLastName(lastName);
    this->setPassword(password);
    this->roles = roles;
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

const MyString User::getFullName() const {
    return this->firstName + " " + this->lastName;
}

const MyString& User::getPassword() const {
    return this->password;
}

const List<Role>& User::getRoles() const {
    return this->roles;
}

const SystemEmail& User::getMailBox() const {
    return this->systemEmail;
}

SystemEmail& User::getMailBox() {
    return this->systemEmail;
}

bool User::isInRole(Role role) const {
    for (size_t i = 0; i < this->roles.getLength(); i++) {
        if (role == this->roles[i]) {
            return true;
        }
    }

    return false;
}

bool User::operator==(const User& user) const {
    return this->id == user.id;
}

bool User::operator!=(const User& user) const {
    return this->id != user.id;
}

void User::setFirstName(const MyString& newFirstName) {
    this->firstName = newFirstName;
}

void User::setLastName(const MyString& newLastName) {
    this->lastName = newLastName;
}

void User::setPassword(const MyString& password) {
    this->password = password;
}

void User::addRole(Role role) {
    if (!this->roles.contains(role)) {
        this->roles.add(role);
    }
}

void User::removeRole(Role role) {
    if (this->roles.contains(role)) {
        this->roles.remove(role);
    }
}

void User::getNewMessage(size_t message) {
    this->systemEmail.getNewMessage(message);
}
