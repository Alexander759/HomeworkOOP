#include "SystemFunctions.h"
#include "AssignmentSolution.h"

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
    return args.getLength() >= 2 && args[0].isNumber();
}

CommandResponse SystemFunctions::message(System& system, const List<MyString>& args) {
    size_t id = atoi(args[0].getCString());

    User& sender = system.getUser();
    /*if (sender.getId() == id) {
        return CommandResponse(false, "User shouldn't send message to himeself");
    }???*/
    
    User& receiver = system.getUsers().FirstOrDefault([id](const User& u) -> bool {return u.getId() == id; });

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
    receiver.getMailBox().getNewMessage(message.getId());

    return CommandResponse(true, "");
}

bool SystemFunctions::validateLogin(const List<MyString>& args) {
    if (args.getLength() != 2) {
        return false;
    }

    return args[0].isNumber();
}

CommandResponse SystemFunctions::login(System& system, const List<MyString>& args) {
    if (system.getIsCurrentlyLoggedIn()) {
        return CommandResponse(false, "Logout first");
    }

    size_t id =  atoi(args[0].getCString());

    User& user = system.getUsers().FirstOrDefault([id](const User& user) -> bool {return user.getId() == id; });

    if (user.getId() != id) {
        return CommandResponse(false, "Id not found");
    }

    if (user.getPassword() != args[1]) {
        return CommandResponse(false, "Wrong password");
    }

    system.setIsCurrentlyLoggedIn(true);
    system.setCurrentlyLoggedInId(user.getId());
    return CommandResponse(true, MyString("Welcome ") + system.getUser().getFirstName());
}

bool SystemFunctions::validateLogout(const List<MyString>& args) {
    return args.getLength() == 0;
}

CommandResponse SystemFunctions::logout(System& system, const List<MyString>& args) {
    if (!system.getIsCurrentlyLoggedIn()) {
        return CommandResponse(false, "Not logged in");
    }

    system.setIsCurrentlyLoggedIn(false);
    return CommandResponse(true, "Logged out");
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
            + sender.getFirstName() + " " + sender.getLastName() + ": " + messsage.getContent();

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

bool SystemFunctions::validateAddTeacher(const List<MyString>& args) {
    return args.getLength() == 3;
}

CommandResponse SystemFunctions::addTeacher(System& system, const List<MyString>& args) {
    User teacher(args[0], args[1], args[2], List<Role>());
    teacher.addRole(Role::Teacher);
    teacher.addRole(Role::Guest);
    system.getUsers().add(teacher);

    return CommandResponse(true, MyString("Added Teacher ") + teacher.getFirstName() 
        + teacher.getLastName() + " with ID " + teacher.getId());
}

bool SystemFunctions::validateAddStudent(const List<MyString>& args) {
    return args.getLength() == 3;
}

CommandResponse SystemFunctions::addStudent(System& system, const List<MyString>& args) {
    User student(args[0], args[1], args[2], List<Role>());
    student.addRole(Role::Student);
    student.addRole(Role::Guest);
    system.getUsers().add(student);

    return CommandResponse(true, MyString("Added student ") + student.getFirstName()
        + student.getLastName() + " with ID " + student.getId());
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
    return args.getLength() == 2 && args[1].isNumber();
}

CommandResponse SystemFunctions::addToCourse(System& system, const List<MyString>& args) {
    Course& course = system.getCourses().FirstOrDefault([args](const Course& course) -> bool {return course.getName() == args[0]; });

    if (course.getName() != args[0]) {
        return CommandResponse(false, "Course not found");
    }

    size_t studentId = atoi(args[1].getCString());
    User student = system.getUsers().FirstOrDefault([studentId](const User& user) -> bool {return user.getId() == studentId; });
    
    if (!student.isInRole(Role::Student)) {
        return CommandResponse(false, "Adding non students is not allowed"); // ?????

    }

    if (student.getId() != studentId) {
        return CommandResponse(false, "Student not found");
    }

    course.getStudentIds().add(studentId);
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
        User user = system.getUsers()[i];

        if (user.isInRole(Role::Student)) {
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

