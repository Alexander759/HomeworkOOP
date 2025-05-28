#include "SystemFunctions.h"

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
    
    return CommandResponse(true, "Success");
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

