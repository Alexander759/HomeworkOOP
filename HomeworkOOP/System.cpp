#include "System.h"
#include <stdexcept>
#include "CommandReader.h"
#include "AssignmentSolution.h"

System::System() {
    this->isCurrentlyLoggedIn = false;
    this->currentlyLoggedInId = 0;
}

System::~System() {
    int a = 0;
}

void System::start() {
    while (true) {
        List<MyString> commandList = CommandReader::readCommand();
    
        if (commandList.getLength() == 0) {
            continue;
        }

        Command& command = this->commands.FirstOrDefault([commandList](const Command& command)
            -> bool {return command.getCommandName() == commandList[0]; });


        if (command.getCommandName() != commandList[0]) {
            std::cout << "Command is not in list" << std::endl;
            continue;
        }

        commandList.removeAt(0);

        CommandResponse response = command.run(*this, commandList);

        if (response.getMessage() != "") {
            std::cout << response.getMessage() << std::endl;
        }
    }
}

const List<User>& System::getUsers() const {
    return this->users;
}

const List<Message>& System::getMessages() const {
    return this->messages;
}

const List<Command>& System::getCommands() const {
    return this->commands;
}

const List<Course>& System::getCourses() const {
    return this->courses;
}

const List<Assignment>& System::getAssignments() const {
    return this->assignments;
}

const List<AssignmentSolution>& System::getAssignmentSolutions() const {
    return this->assignmentSolutions;
}

const List<Grade>& System::getGrades() const {
    return this->grades;
}

const List<Role> System::getCurrentUserRoles() const {
    if (!this->isCurrentlyLoggedIn) {
        List<Role> result;
        result.add(Role::Guest);
        return result;
    }

    size_t currentId = this->currentlyLoggedInId;
    return this->users.FirstOrDefault([currentId](const User& user) -> bool {return user.getId() == currentId; }).getRoles();
}

bool System::getIsCurrentlyLoggedIn() const {
    return this->isCurrentlyLoggedIn;
}

size_t System::getCurrentlyLoggedInId() const {
    if (!this->isCurrentlyLoggedIn) {
        throw std::exception("User not logged in");
    }
    
    return this->currentlyLoggedInId;
}

void System::setIsCurrentlyLoggedIn(bool isCurrentlyLoggedIn) {
    this->isCurrentlyLoggedIn = isCurrentlyLoggedIn;
}

void System::setCurrentlyLoggedInId(size_t currentlyLoggedInId) {
    this->currentlyLoggedInId = currentlyLoggedInId;
}

User& System::getUser() {
    if (!this->isCurrentlyLoggedIn) {
        throw std::exception("No logged in user");
    }

    size_t currentId = this->currentlyLoggedInId;
    return users.FirstOrDefault([currentId](const User& user) -> bool {return user.getId() == currentId; });
}

List<User>& System::getUsers() {
    return this->users;
}

List<Message>& System::getMessages() {
    return this->messages;
}

List<Command>& System::getCommands() {
    return this->commands;
}

List<Course>& System::getCourses() {
    return this->courses;
}

List<Assignment>& System::getAssignments() {
    return this->assignments;
}

List<AssignmentSolution>& System::getAssignmentSolutions() {
    return this->assignmentSolutions;
}

List<Grade>& System::getGrades() {
    return this->grades;
}

