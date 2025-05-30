#include "Grade.h"
#include <stdexcept>

size_t Grade::currentId = 1;

Grade::Grade(double grade, size_t studentId, size_t assignmentId, size_t teacherId, const MyString& message)
    : studentId(studentId), assignmentSolutionId(assignmentId), teacherId(teacherId), message(message) {
    this->id = currentId;
    currentId++;
    this->setGrade(grade);
}

size_t Grade::getId() const {
    return this->id;
}

double Grade::getGrade() const {
    return this->grade;
}

size_t Grade::getStudentId() const {
    return this->studentId;
}

size_t Grade::getAssignmentSolutionId() const {
    return this->assignmentSolutionId;
}

size_t Grade::getTeacherId() const {
    return this->teacherId;
}

const MyString& Grade::getMessage() const {
    return this->message;
}

bool Grade::operator==(const Grade& other) const {
    return this->id == other.getId();
}

bool Grade::operator!=(const Grade& other) const {
    return this->id != other.getId();;
}

void Grade::setGrade(double grade) {
    if (grade < 2 || grade > 6) {
        throw std::invalid_argument("Grade must be between 2 and 6");
    }

    this->grade = grade;
}

void Grade::setStudentId(size_t studentId) {
    this->studentId = studentId;
}

void Grade::setAssignmenSolutiontId(size_t assignmentSolutionId) {
    this->assignmentSolutionId = assignmentSolutionId;
}

void Grade::setTeacherId(size_t teacherId) {
    this->teacherId = teacherId;
}

void Grade::setMessage(const MyString& message) {
    this->message = message;
}

size_t Grade::getCurrentId() {
    return Grade::currentId;
}

void Grade::setCurrentId(size_t currentId) {
    Grade::currentId = currentId;
}

std::ofstream& operator<<(std::ofstream& stream, const Grade& grade) {
    if (!stream.is_open()) {
        return stream;
    }
    
    stream.write(reinterpret_cast<const char*>(&grade.id), sizeof(size_t));
    stream.write(reinterpret_cast<const char*>(&grade.grade), sizeof(double));
    stream.write(reinterpret_cast<const char*>(&grade.studentId), sizeof(size_t));
    stream.write(reinterpret_cast<const char*>(&grade.assignmentSolutionId), sizeof(size_t));
    stream.write(reinterpret_cast<const char*>(&grade.teacherId), sizeof(size_t));
    stream << grade.message;

    return stream;
}

std::ifstream& operator>>(std::ifstream& stream, Grade& grade) {
    if (!stream.is_open()) {
        return stream;
    }

    stream.read(reinterpret_cast<char*>(&grade.id), sizeof(size_t));
    stream.read(reinterpret_cast<char*>(&grade.grade), sizeof(double));
    stream.read(reinterpret_cast<char*>(&grade.studentId), sizeof(size_t));
    stream.read(reinterpret_cast<char*>(&grade.assignmentSolutionId), sizeof(size_t));
    stream.read(reinterpret_cast<char*>(&grade.teacherId), sizeof(size_t));
    stream >> grade.message;

    return stream;
}
