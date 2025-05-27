#include "User.h"

size_t User::currentId = 1;

User::User(const MyString& firstName, const MyString& lastName, const List<Role>& roles) {
    this->id = currentId;
    currentId++;
    this->setFirstName(firstName);
    this->setLastName(lastName);
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

const List<Role>& User::getRoles() const {
    return this->roles;
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

void User::getNewMessage(const Message* message) {
    this->systemEmail.getNewMessage(message);
}
