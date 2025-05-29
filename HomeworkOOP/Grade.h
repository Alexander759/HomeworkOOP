#pragma once

class Grade {
public:
	Grade();
	Grade(double grade, size_t studentId, size_t assignmentId, size_t teacherId);

	double getGrade() const;
	size_t getStudentId() const;
	size_t getAssignmentSolutionId() const;
	size_t getTeacherId() const;

	void setGrade(double grade);
	void setStudentId(size_t studentId);
	void setAssignmenSolutiontId(size_t assignmenSolutiontId);
	void setTeacherId(size_t teacherId);

private:
	static size_t currentId;

	size_t id;
	double grade;
	size_t studentId;
	size_t assignmentSolutionId;
	size_t teacherId;
};