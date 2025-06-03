/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#include "SystemFunctions.h"
#include "AssignmentSolution.h"
#include <cmath>

void SystemFunctions::addCommands(System& system) {
    Command login("login", "[id] [password]",
        SystemFunctions::validateLogin, SystemFunctions::login, List<Role>());
    login.addRole(Role::Guest);
    system.getCommands().add(login);

    Command logout(Command("logout", "[no arguments]",
        SystemFunctions::validateLogout, SystemFunctions::logout, List<Role>()));
    logout.addRole(Role::Guest);
    system.getCommands().add(logout);

    Command messageToAll("message_all", "[text]",
        SystemFunctions::validateMessageToAllArgs, SystemFunctions::messageToAll, List<Role>());
    messageToAll.addRole(Role::Admin);
    system.getCommands().add(messageToAll);

    Command message("message", "[userId] [text]",
        SystemFunctions::validateMessageArgs, SystemFunctions::message, List<Role>());
    message.addRole(Role::Admin);
    message.addRole(Role::Teacher);
    message.addRole(Role::Student);
    system.getCommands().add(message);

    Command mailBox("mailbox", "[no arguments]",
        SystemFunctions::validateMailBox, SystemFunctions::mailBox, List<Role>());
    mailBox.addRole(Role::Admin);
    mailBox.addRole(Role::Student);
    mailBox.addRole(Role::Teacher);
    system.getCommands().add(mailBox);

    Command clearMailBox("clear_mailbox", "[no arguments]",
        SystemFunctions::validateClearMailBox, SystemFunctions::clearMailBox, List<Role>());
    clearMailBox.addRole(Role::Admin);
    clearMailBox.addRole(Role::Teacher);
    clearMailBox.addRole(Role::Student);
    system.getCommands().add(clearMailBox);

    Command viewMailBox("view_mailbox", "[userId]",
        SystemFunctions::validateViewMailBox, SystemFunctions::viewMailBox, List<Role>());
    viewMailBox.addRole(Role::Admin);
    system.getCommands().add(viewMailBox);

    Command addTeacher("add_teacher", "[firstName] [lastName] [password]",
        SystemFunctions::validateAddTeacher, SystemFunctions::addTeacher, List<Role>());
    addTeacher.addRole(Role::Admin);
    system.getCommands().add(addTeacher);

    Command addStudent("add_student", "[firstName] [lastName] [password]",
        SystemFunctions::validateAddStudent, SystemFunctions::addStudent, List<Role>());
    addStudent.addRole(Role::Admin);
    system.getCommands().add(addStudent);

    Command deleteUser("delete_user", "[userId]",
        SystemFunctions::validateDeleteUser, SystemFunctions::deleteUser, List<Role>());
    deleteUser.addRole(Role::Admin);
    system.getCommands().add(deleteUser);

    Command changePassword("change_password", "[oldPassword] [newPassword]",
        SystemFunctions::validateChangePassword, SystemFunctions::changePassword, List<Role>());
    changePassword.addRole(Role::Admin);
    changePassword.addRole(Role::Teacher);
    changePassword.addRole(Role::Student);
    system.getCommands().add(changePassword);

    Command createCourse("create_course", "[courseName]",
        SystemFunctions::validateCreateCourse, SystemFunctions::createCourse, List<Role>());
    createCourse.addRole(Role::Teacher);
    system.getCommands().add(createCourse);

    Command addToCourse("add_to_course", "[courseName] [studentID]",
        SystemFunctions::validateAddToCourse, SystemFunctions::addToCourse, List<Role>());
    addToCourse.addRole(Role::Teacher);
    system.getCommands().add(addToCourse);

    Command messageToStudents("message_students", "[courseName] [text]",
        SystemFunctions::validateMessageToStudents, SystemFunctions::messageToStudents, List<Role>());
    messageToStudents.addRole(Role::Teacher);
    system.getCommands().add(messageToStudents);

    Command enroll("enroll", "[courseName] [coursePassword]",
        SystemFunctions::validateEnroll, SystemFunctions::enroll, List<Role>());
    enroll.addRole(Role::Student);
    system.getCommands().add(enroll);

    Command assignHomework("assign_homework", "[courseName] [assignmentName]",
        SystemFunctions::validateAssignHomework, SystemFunctions::assignHomework, List<Role>());
    assignHomework.addRole(Role::Teacher);
    system.getCommands().add(assignHomework);

    Command viewHomework("view_homework", "[no arguments]",
        SystemFunctions::validateViewHomework, SystemFunctions::viewHomework, List<Role>());
    viewHomework.addRole(Role::Student);
    system.getCommands().add(viewHomework);

    Command submitAssignment("submit_assignment", "[courseName] [assignmentName] [text]",
        SystemFunctions::validateSubmitAssignment, SystemFunctions::submitAssignment, List<Role>());
    submitAssignment.addRole(Role::Student);
    system.getCommands().add(submitAssignment);

    Command viewAssignmentSubmissions("view_assignment_submissions", "[courseName] [assignmentName]",
        SystemFunctions::validateViewAssignmentSubmissions, SystemFunctions::viewAssignmentSubmissions, List<Role>());
    viewAssignmentSubmissions.addRole(Role::Teacher);
    system.getCommands().add(viewAssignmentSubmissions);

    Command gradeAssignment("grade_assignment", "[courseName] [assignmentName] [studentID] [Grade] [Message]",
        SystemFunctions::validateGradeAssignment, SystemFunctions::gradeAssignment, List<Role>());
    gradeAssignment.addRole(Role::Teacher);
    system.getCommands().add(gradeAssignment);

    Command viewGrades("grades", "[no arguments]",
        SystemFunctions::validateViewGrades, SystemFunctions::viewGrades, List<Role>());
    viewGrades.addRole(Role::Student);
    system.getCommands().add(viewGrades);

    Command help("help", "[no arguments]",
        SystemFunctions::validateHelp, SystemFunctions::help, List<Role>());
    help.addRole(Role::Guest);
    system.getCommands().add(help);
}

bool SystemFunctions::validateMessageToAllArgs(const List<MyString>& args) {
    return args.getLength() >= 1;
}

CommandResponse SystemFunctions::messageToAll(System& system, const List<MyString>& args) {
    User& user = system.getUsers().FirstOrDefault([system](const User& user) -> bool {return user.getId() == system.getCurrentlyLoggedInId(); });
    MyString messageContent;
    for (size_t i = 0; i < args.getLength(); i++) {
        messageContent += args[i] + " ";
    }

    messageContent = messageContent.subStr(0, messageContent.getLength() - 1);

    Message message(user.getId(), messageContent);
    system.getMessages().add(message);

    for (size_t i = 0; i < system.getUsers().getLength(); i++) {
        if (system.getUsers()[i] != user) {
            system.getUsers()[i].getNewMessage(message.getId());
        }
    }
    
    return CommandResponse(true, "");
}

bool SystemFunctions::validateMessageArgs(const List<MyString>& args) {
    return args.getLength() >= 2 && args[0].isSizeT();
}

CommandResponse SystemFunctions::message(System& system, const List<MyString>& args) {
    size_t id = args[0].toSizeT();

    User& sender = system.getUser();
    if (sender.getId() == id) {
        return CommandResponse(false, "Message to others");
    }
    
    User& receiver = system.getUsers().FirstOrDefault([id](const User& user) -> bool {return user.getId() == id; });

    if (receiver.getId() != id) {
        return CommandResponse(false, "User not found");
    }

    MyString messageContent;

    for (size_t i = 1; i < args.getLength(); i++) {
        messageContent += args[i] + " ";
    }

    messageContent = messageContent.subStr(0, messageContent.getLength() - 1);

    Message message(sender.getId(), messageContent);
    system.getMessages().add(message);
    receiver.getNewMessage(message.getId());

    return CommandResponse(true, "");
}

bool SystemFunctions::validateLogin(const List<MyString>& args) {
    if (args.getLength() != 2) {
        return false;
    }

    return args[0].isSizeT();
}

CommandResponse SystemFunctions::login(System& system, const List<MyString>& args) {
    if (system.getIsCurrentlyLoggedIn()) {
        return CommandResponse(false, "Logout first");
    }

    size_t id =  args[0].toSizeT();

    User& user = system.getUsers().FirstOrDefault([id](const User& user) -> bool {return user.getId() == id; });

    if (user.getId() != id) {
        return CommandResponse(false, "Id not found");
    }

    if (user.getIsDeleted()) {
        return CommandResponse(false, "User is deleted");
    }

    if (user.getPassword() != args[1]) {
        return CommandResponse(false, "Wrong password");
    }

    system.setIsCurrentlyLoggedIn(true);
    system.setCurrentlyLoggedInId(user.getId());
    
    MyString message = "Login successful\n";
    message += user.getFullName() + " | " + user.getMainRole() + " | " + user.getId();

    return CommandResponse(true, message);
}

bool SystemFunctions::validateLogout(const List<MyString>& args) {
    return args.getLength() == 0;
}

CommandResponse SystemFunctions::logout(System& system, const List<MyString>& args) {
    if (!system.getIsCurrentlyLoggedIn()) {
        return CommandResponse(false, "Not logged in");
    }

    system.setIsCurrentlyLoggedIn(false);
    return CommandResponse(true, "");
}

bool SystemFunctions::validateMailBox(const List<MyString>& args) {
    return args.getLength() == 0;
}

CommandResponse SystemFunctions::mailBox(System& system, const List<MyString>& args) {
    List<size_t> messageIds =  system.getUser().getMailBox().getMessagesReceivedIds();
    MyString responseContent;
    for (size_t i = 0; i < messageIds.getLength(); i++) {
        size_t currentId = messageIds[i];
        Message& messsage = system.getMessages().FirstOrDefault([currentId](const Message& message) -> bool {return message.getId() == currentId; });
        User& sender = system.getUsers().FirstOrDefault([messsage](const User& user) -> bool {return messsage.getSenderId() == user.getId(); });
        
        responseContent += messsage.getTimeSended().toStringFormat() + ", sent by "
            + sender.getFullName() + ": " + messsage.getContent();

        if (i != messageIds.getLength() - 1) {
            responseContent += "\n";
        }
    }

    if (responseContent.getLength() == 0) {
        responseContent = "No messages to show";
    }

    return CommandResponse(true, responseContent);
}

bool SystemFunctions::validateClearMailBox(const List<MyString>& args) {
    return args.getLength() == 0;
}

CommandResponse SystemFunctions::clearMailBox(System& system, const List<MyString>& args) {
    system.getUser().getMailBox().getMessagesReceivedIds().clear();
    return CommandResponse(true, "Mailbox cleared");
}

bool SystemFunctions::validateViewMailBox(const List<MyString>& args) {
    return args.getLength() == 1 && args[0].isSizeT();
}

CommandResponse SystemFunctions::viewMailBox(System& system, const List<MyString>& args) {
    size_t userId = args[0].toSizeT();
    User& user = system.getUsers().FirstOrDefault([userId](const User& user) -> bool {return user.getId() == userId; });

    if (user.getId() != userId) {
        return CommandResponse(false, "User not found");
    }

    List<size_t> messageIds = user.getMailBox().getMessagesReceivedIds();
    MyString responseContent;
    for (size_t i = 0; i < messageIds.getLength(); i++) {
        size_t currentId = messageIds[i];
        Message& messsage = system.getMessages().FirstOrDefault([currentId](const Message& message) -> bool {return message.getId() == currentId; });
        User& sender = system.getUsers().FirstOrDefault([messsage](const User& user) -> bool {return messsage.getSenderId() == user.getId(); });

        responseContent += messsage.getTimeSended().toStringFormat() + ", sent by "
            + sender.getFullName() + ": " + messsage.getContent();

        if (i != messageIds.getLength() - 1) {
            responseContent += "\n";
        }
    }

    if (responseContent.getLength() == 0) {
        responseContent = "No messages to show";
    }

    return CommandResponse(true, responseContent);
}

bool SystemFunctions::validateAddTeacher(const List<MyString>& args) {
    return args.getLength() == 3;
}

CommandResponse SystemFunctions::addTeacher(System& system, const List<MyString>& args) {
    User teacher(args[0], args[1], args[2], List<Role>());
    teacher.addRole(Role::Teacher);
    teacher.addRole(Role::Guest);
    system.getUsers().add(teacher);

    return CommandResponse(true, MyString("Added Teacher ") + teacher.getFullName() + " with ID " + teacher.getId() + "!");
}

bool SystemFunctions::validateAddStudent(const List<MyString>& args) {
    return args.getLength() == 3;
}

CommandResponse SystemFunctions::addStudent(System& system, const List<MyString>& args) {
    User student(args[0], args[1], args[2], List<Role>());
    student.addRole(Role::Student);
    student.addRole(Role::Guest);
    system.getUsers().add(student);

    return CommandResponse(true, MyString("Added student ") + student.getFullName() + " with ID " + student.getId() + "!");
}

bool SystemFunctions::validateDeleteUser(const List<MyString>& args) {
    return args.getLength() == 1 && args[0].isSizeT();
}

CommandResponse SystemFunctions::deleteUser(System& system, const List<MyString>& args) {
    
    size_t userId = args[0].toSizeT();
    User& user = system.getUsers().FirstOrDefault([userId](const User& user) -> bool {return user.getId() == userId; });

    if (user.getId() != userId) {
        return CommandResponse(false, "User not found");
    }

    if (user.getIsDeleted()) {
        return CommandResponse(false, "User is deleted already");
    }

    if (user == system.getUser()) {
        return CommandResponse(false, "Can not delete current user");
    }

    user.setIsDeleted(true);
    return CommandResponse(true, "");
}

bool SystemFunctions::validateChangePassword(const List<MyString>& args) {
    return args.getLength() == 2;
}

CommandResponse SystemFunctions::changePassword(System& system, const List<MyString>& args) {
    if (system.getUser().getPassword() != args[0]) {
        return CommandResponse(false, "Wrong current password");
    }

    system.getUser().setPassword(args[1]);
    return CommandResponse(true, "Password changed successfully!");
}

bool SystemFunctions::validateCreateCourse(const List<MyString>& args) {
    return args.getLength() == 2;
}

CommandResponse SystemFunctions::createCourse(System& system, const List<MyString>& args) {
    if (system.getCourses()
        .indexOf([args](const Course& course) -> bool {return args[0] == course.getName(); }) != -1) {
        return CommandResponse(false, "Course with this name already exists");
    }

    Course course(args[0], args[1], system.getUser().getId());

    system.getCourses().add(course);
    return CommandResponse(true, "");
}

bool SystemFunctions::validateAddToCourse(const List<MyString>& args) {
    return args.getLength() == 2 && args[1].isSizeT();
}

CommandResponse SystemFunctions::addToCourse(System& system, const List<MyString>& args) {
    if (system.getCourses().getLength() == 0) {
        return CommandResponse(false, "Course not found");
    }
    
    Course& course = system.getCourses().FirstOrDefault([args](const Course& course) -> bool {return course.getName() == args[0]; });

    if (course.getName() != args[0]) {
        return CommandResponse(false, "Course not found");
    }

    size_t studentId = args[1].toSizeT();
    User& student = system.getUsers().FirstOrDefault([studentId](const User& user) -> bool {return user.getId() == studentId; });
    
    if (student.getId() != studentId) {
        return CommandResponse(false, "Student not found");
    }

    if (!student.isInRole(Role::Student)) {
        return CommandResponse(false, "Adding non students is not allowed"); 
    }

    course.getStudentIds().add(studentId);

    MyString messageContent = system.getUser().getFullName() + " added you to " + course.getName();
    List<MyString> emailArgs;
    emailArgs.add(MyString(studentId));
    emailArgs.add(messageContent);
    SystemFunctions::message(system, emailArgs);

    return CommandResponse(true, "");
}

bool SystemFunctions::validateMessageToStudents(const List<MyString>& args) {
    return args.getLength() >= 2;
}

CommandResponse SystemFunctions::messageToStudents(System& system, const List<MyString>& args) {
    if (system.getCourses().getLength() == 0) {
        return CommandResponse(false, "Course not found");
    }

    Course& course = system.getCourses().FirstOrDefault([args](const Course& course) -> bool {return course.getName() == args[0]; });

    if (!course.getTeacherIds().contains(system.getUser().getId())) {
        return CommandResponse(false, "You are not in the course");
    }

    MyString messageContent;

    for (size_t i = 1; i < args.getLength(); i++) {
        messageContent += args[i] + " ";
    }

    messageContent = messageContent.subStr(0, messageContent.getLength() - 1);
    Message message(system.getUser().getId(), messageContent);
    system.getMessages().add(message);

    for (size_t i = 0; i < system.getUsers().getLength(); i++) {
        User& user = system.getUsers()[i];

        if (user.isInRole(Role::Student) && course.getStudentIds().contains(user.getId())) {
            user.getMailBox().getNewMessage(message.getId());
        }
    }

    return CommandResponse(true, "");
}

bool SystemFunctions::validateEnroll(const List<MyString>& args) {
    return args.getLength() == 2;
}

CommandResponse SystemFunctions::enroll(System& system, const List<MyString>& args) {
    if (system.getCourses().getLength() == 0) {
        return CommandResponse(false, "Course not found");
    }

    Course& course = system.getCourses().FirstOrDefault([args](const Course& course) -> bool {return course.getName() == args[0]; });
    if (course.getName() != args[0]) {
        return CommandResponse(false, "Course not found");
    }

    if (course.getPassword() != args[1]) {
        return CommandResponse(false, "Wrong password");
    }

    course.getStudentIds().add(system.getUser().getId());
    return CommandResponse(true, MyString("Successfully enrolled in ") + course.getName() + "!");
}

bool SystemFunctions::validateAssignHomework(const List<MyString>& args) {
    return args.getLength() == 2;
}

CommandResponse SystemFunctions::assignHomework(System& system, const List<MyString>& args) {
    if (system.getCourses().getLength() == 0) {
        return CommandResponse(false, "Course not found");
    }

    Course& course = system.getCourses().FirstOrDefault([args](const Course& course) -> bool {return course.getName() == args[0]; });

    if (!course.getTeacherIds().contains(system.getUser().getId())) {
        return CommandResponse(false, "You are not in the course");
    }

    Assignment assignment(args[1], course.getId());

    system.getAssignments().add(assignment);
    return CommandResponse(true, "Successfully created a new assignment!");
}

bool SystemFunctions::validateViewHomework(const List<MyString>& args) {
    return args.getLength() == 0;
}

CommandResponse SystemFunctions::viewHomework(System& system, const List<MyString>& args) {
    User& student = system.getUser();

    List<Course*> courcesOfStudent;

    for (size_t i = 0; i < system.getCourses().getLength(); i++) {
        if (system.getCourses()[i].getStudentIds().contains(student.getId())) {
            courcesOfStudent.add(&system.getCourses()[i]);
        }
    }

    List<Assignment*> assignmentsOfStudent;
    for (size_t i = 0; i < courcesOfStudent.getLength(); i++) {
        for (size_t j = 0; j < system.getAssignments().getLength(); j++) {
            if (courcesOfStudent[i]->getId() == system.getAssignments()[j].getCourseId()) {
                assignmentsOfStudent.add(&system.getAssignments()[j]);
            }
        }
    }

    for (size_t i = 0; i < system.getAssignmentSolutions().getLength(); i++) {
        AssignmentSolution& assignmentSolution = system.getAssignmentSolutions()[i];

        if (assignmentSolution.getStudentId() == student.getId()) {
            for (size_t j = 0; j < assignmentsOfStudent.getLength(); j++) {
                if (assignmentsOfStudent[j]->getId() == assignmentSolution.getAssignmentId()) {
                    assignmentsOfStudent.removeAt(j);
                    j--;
                }
            }
        }
    }

    if (assignmentsOfStudent.getLength() == 0) {
        return CommandResponse(true, "No new assignments");
    }

    MyString message;

    for (size_t i = 0; i < assignmentsOfStudent.getLength(); i++) {
        message += assignmentsOfStudent[i]->getName() + " " 
            + system.getCourses().FirstOrDefault([assignmentsOfStudent, i](const Course& course) -> bool {return course.getId() == assignmentsOfStudent[i]->getCourseId(); }).getName()
            + "\n";
    }

    message = message.subStr(0, message.getLength() - 1);

    return CommandResponse(true, message);
}

bool SystemFunctions::validateSubmitAssignment(const List<MyString>& args) {
    return args.getLength() >= 3;
}

CommandResponse SystemFunctions::submitAssignment(System& system, const List<MyString>& args) {
    User& user = system.getUser();
    Course& course = system.getCourses().FirstOrDefault([args](const Course& c) -> bool {return c.getName() == args[0]; });

    if (course.getName() != args[0]) {
        return CommandResponse(false, "Course not found");
    }

    if (system.getAssignments().getLength() == 0) {
        return CommandResponse(false, "Assignment not found");
    }

    Assignment& assignment = system.getAssignments().FirstOrDefault([args, course](const Assignment& assignment)
        -> bool {return assignment.getCourseId() == course.getId() && assignment.getName() == args[1]; });

    if (assignment.getCourseId() != course.getId() || assignment.getName() != args[1]) {
        return CommandResponse(false, "Assignment not found");
    }

    MyString solutionContent;
    for (size_t i = 0; i < args.getLength(); i++) {
        solutionContent += args[i] + " ";
    }

    solutionContent = solutionContent.subStr(0, solutionContent.getLength() - 1);

    AssignmentSolution solution(user.getId(), assignment.getId(), solutionContent);
    system.getAssignmentSolutions().add(solution);
    return CommandResponse(true, "");
}

bool SystemFunctions::validateViewAssignmentSubmissions(const List<MyString>& args) {
    return args.getLength() == 2;
}

CommandResponse SystemFunctions::viewAssignmentSubmissions(System& system, const List<MyString>& args) {
    Course& course = system.getCourses().FirstOrDefault([args](const Course& c) -> bool {return c.getName() == args[0]; });

    if (course.getName() != args[0]) {
        return CommandResponse(false, "Course not found");
    }

    Assignment& assignment = system.getAssignments().FirstOrDefault([args, course](const Assignment& assignment)
        -> bool {return assignment.getCourseId() == course.getId() && assignment.getName() == args[1]; });

    if (assignment.getCourseId() != course.getId() || assignment.getName() != args[1]) {
        return CommandResponse(false, "Assignment not found");
    }

    List<AssignmentSolution*> assignmentSolutions;

    for (size_t i = 0; i < system.getAssignmentSolutions().getLength(); i++) {
        AssignmentSolution& solution = system.getAssignmentSolutions()[i];
        if (solution.getAssignmentId() == assignment.getId()) {
            bool isNotGraded = true;
            for (size_t i = 0; i < system.getGrades().getLength(); i++) {
                if (system.getGrades()[i].getAssignmentSolutionId() == solution.getId()) {
                    isNotGraded = false;
                    break;
                }
            }

            if (isNotGraded) {
                assignmentSolutions.add(&solution);
            }
        }
    }

    MyString submissions;
    for (size_t i = 0; i < assignmentSolutions.getLength(); i++) {
        User& student = system.getUsers().FirstOrDefault([assignmentSolutions, i](const User& user) -> bool {return user.getId() == assignmentSolutions[i]->getStudentId(); });

        if (student.getId() != assignmentSolutions[i]->getStudentId()) {
            continue;
        }

        submissions += student.getFullName() + ", " + student.getId() + ": " + assignmentSolutions[i]->getSolution() + "\n";
    }

    if (submissions.getLength() == 0) {
        submissions = "No new submissions";
    }
    else {
        submissions = submissions.subStr(0, submissions.getLength() - 1);
    }

    return CommandResponse(true, submissions);
}

bool SystemFunctions::validateGradeAssignment(const List<MyString>& args) {
    return args.getLength() >= 5 && args[2].isSizeT() && args[3].isDouble();
}

CommandResponse SystemFunctions::gradeAssignment(System& system, const List<MyString>& args) {
    Course& course = system.getCourses().FirstOrDefault([args](const Course& c) -> bool {return c.getName() == args[0]; });

    if (course.getName() != args[0]) {
        return CommandResponse(false, "Course not found");
    }

    Assignment& assignment = system.getAssignments().FirstOrDefault([args, course](const Assignment& assignment)
        -> bool {return assignment.getCourseId() == course.getId() && assignment.getName() == args[1]; });

    if (assignment.getCourseId() != course.getId() || assignment.getName() != args[1]) {
        return CommandResponse(false, "Assignment not found");
    }

    size_t studentId = args[2].toSizeT();
    User& student = system.getUsers().FirstOrDefault([studentId](const User& user) -> bool {return user.getId() == studentId; });

    if (student.getId() != studentId) {
        return CommandResponse(false, "Student not found");
    }

    if (!course.getStudentIds().contains(studentId)) {
        return CommandResponse(false, "Student not in course");
    }

    AssignmentSolution solution = system.getAssignmentSolutions().FirstOrDefault([assignment, student](const AssignmentSolution& assignmentSolution) 
        -> bool {return assignmentSolution.getStudentId() == student.getId() && assignmentSolution.getAssignmentId() == assignment.getId(); });

    if (solution.getStudentId() != student.getId() || solution.getAssignmentId() != assignment.getId()) {
        return CommandResponse(false, "Assignment solution not in course");
    }


    MyString message;
    for (size_t i = 4; i < args.getLength(); i++) {
        message += args[i] + " ";
    }

    message = message.subStr(0, message.getLength() - 1);


    Grade grade(args[3].toDouble(), student.getId(), assignment.getId(),
        system.getUser().getId(), message);
    system.getGrades().add(grade);

    MyString emailMessage = system.getUser().getFullName() + " graded your work on "
        + assignment.getName() + " in " + course.getName();

    List<MyString> emailArgs;
    emailArgs.add(student.getId());
    emailArgs.add(emailMessage);

    SystemFunctions::message(system, emailArgs);

    return CommandResponse(true, "");
}

bool SystemFunctions::validateViewGrades(const List<MyString>& args) {
    return args.getLength() == 0;
}

CommandResponse SystemFunctions::viewGrades(System& system, const List<MyString>& args) {
    User& user = system.getUser();

    MyString message;

    for (size_t i = 0; i < system.getGrades().getLength(); i++) {
        if (system.getGrades()[i].getStudentId() == user.getId()) {
            Grade& grade = system.getGrades()[i];

            AssignmentSolution& assignmentSolution = system.getAssignmentSolutions().FirstOrDefault([grade](const AssignmentSolution& assignmentSolution)
                -> bool {return assignmentSolution.getId() == grade.getAssignmentSolutionId(); });
            
            if (assignmentSolution.getId() != grade.getAssignmentSolutionId()) {
                continue;
            }
            
            Assignment& assignment = system.getAssignments().FirstOrDefault([assignmentSolution](const Assignment& assignment)
                -> bool {return assignment.getId() == assignmentSolution.getAssignmentId(); });

            if (assignment.getId() != assignmentSolution.getAssignmentId()) {
                continue;
            }

            Course& course = system.getCourses().FirstOrDefault([assignment](const Course& course)
                -> bool {return course.getId() == assignment.getCourseId(); });

            if (course.getId() != assignment.getCourseId()) {
                continue;
            }

            message += course.getName() + " | " + assignment.getName() + " | " + (std::round(grade.getGrade() * 100) / 100) + " | " + grade.getMessage() + "\n";
        }
    }

    if (message == "") {
        message = "There are no graded assignments";
    }
    else {
        message = message.subStr(0, message.getLength() - 1);
    }

    return CommandResponse(true, message);
}

bool SystemFunctions::validateHelp(const List<MyString>& args) {
    return true;
}

CommandResponse SystemFunctions::help(System& system, const List<MyString>& args) {
    MyString message;

    for (size_t i = 0; i < system.getCommands().getLength(); i++) {
        Command& command = system.getCommands()[i];

        if (command.userHasAllowedRole(system.getCurrentUserRoles())) {
            message += command.getFullCommandHelp() + "\n";
        }
    }

    message += "exit - exit the app";

    return CommandResponse(true, message);
}
