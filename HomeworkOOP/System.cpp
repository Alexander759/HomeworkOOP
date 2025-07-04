/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#include "System.h"
#include <stdexcept>
#include <fstream>
#include "CommandReader.h"
#include "AssignmentSolution.h"

System::System(const MyString& fileName) {
    this->isCurrentlyLoggedIn = false;
    this->currentlyLoggedInId = 0;
    this->fileName = fileName;
}

void System::start() {
    while (true) {
        List<MyString> commandList = CommandReader::readCommand();
    
        if (commandList.getLength() == 0) {
            continue;
        }

        if (commandList[0] == "exit") {
            break;
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

        this->saveToFile();
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

void System::saveToFile() const {
    std::ofstream stream(fileName.getCString(), std::ios::out | std::ios::binary);

    if (!stream.is_open()) {
        return;
    }

    size_t currentId = User::getCurrentId();
    
    currentId = User::getCurrentId();
    stream.write(reinterpret_cast<const char*>(&currentId), sizeof(size_t));

    currentId = Message::getCurrentId();
    stream.write(reinterpret_cast<const char*>(&currentId), sizeof(size_t));

    currentId = Course::getCurrentId();
    stream.write(reinterpret_cast<const char*>(&currentId), sizeof(size_t));

    currentId = Assignment::getCurrentId();
    stream.write(reinterpret_cast<const char*>(&currentId), sizeof(size_t));

    currentId = AssignmentSolution::getCurrentId();
    stream.write(reinterpret_cast<const char*>(&currentId), sizeof(size_t));

    currentId = Grade::getCurrentId();
    stream.write(reinterpret_cast<const char*>(&currentId), sizeof(size_t));

    stream << this->users;
    stream << this->messages;
    stream << this->courses;
    stream << this->assignments;
    stream << this->assignmentSolutions;
    stream << this->grades;

    stream.close();
}

void System::readFromFile() {
    std::ifstream stream(fileName.getCString(), std::ios::in | std::ios::binary);
    
    if (!stream.is_open()) {
        return;
    }

    size_t currentId;
    
    stream.read(reinterpret_cast<char*>(&currentId), sizeof(size_t));
    User::setCurrentId(currentId);

    stream.read(reinterpret_cast<char*>(&currentId), sizeof(size_t));
    Message::setCurrentId(currentId);

    stream.read(reinterpret_cast<char*>(&currentId), sizeof(size_t));
    Course::setCurrentId(currentId);

    stream.read(reinterpret_cast<char*>(&currentId), sizeof(size_t));
    Assignment::setCurrentId(currentId);

    stream.read(reinterpret_cast<char*>(&currentId), sizeof(size_t));
    AssignmentSolution::setCurrentId(currentId);

    stream.read(reinterpret_cast<char*>(&currentId), sizeof(size_t));
    Grade::setCurrentId(currentId);

    stream >> this->users;
    stream >> this->messages;
    stream >> this->courses;
    stream >> this->assignments;
    stream >> this->assignmentSolutions;
    stream >> this->grades;

    stream.close();

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
