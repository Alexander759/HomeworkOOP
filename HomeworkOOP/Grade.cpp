#include "Grade.h"
#include <stdexcept>

size_t Grade::currentId = 1;

Grade::Grade() {
    this->id = currentId;
    currentId++;
}

Grade::Grade(double grade, size_t studentId, size_t assignmentId, size_t teacherId) : studentId(studentId), assignmentId(assignmentId), teacherId(teacherId) {
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

size_t Grade::getAssignmentId() const {
    return this->assignmentId;
}

size_t Grade::getTeacherId() const {
    return this->teacherId;
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

void Grade::setAssignmentId(size_t assignmentId) {
    this->assignmentId = assignmentId;
}

void Grade::setTeacherId(size_t teacherId) {
    this->teacherId = teacherId;
}
