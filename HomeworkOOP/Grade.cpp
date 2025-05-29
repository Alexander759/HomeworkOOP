#include "Grade.h"
#include <stdexcept>

size_t Grade::currentId = 1;

Grade::Grade() {
    this->id = currentId;
    currentId++;
}

Grade::Grade(double grade, size_t studentId, size_t assignmentId, size_t teacherId, const MyString& message)
    : studentId(studentId), assignmentSolutionId(assignmentId), teacherId(teacherId), message(message) {
    this->id = currentId;
    currentId++;
    this->setGrade(grade);
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

void Grade::setGrade(double grade) {
    if (this->grade < 2 || 6 < this->grade) {
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
