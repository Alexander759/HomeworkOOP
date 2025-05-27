#include "System.h"

const List<User>& System::getUsers() const {
    return this->users;
}

const List<Message>& System::getMessages() const {
    return this->messages;
}

const List<Command>& System::getCommands() const {
    return this->commands;
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

bool System::validateMessageToAllArgs(const List<MyString>& args) {
    return args.getLength() >= 1;
}

CommandResponse System::messageToAll(User& user, System& system, const List<MyString>& args) {
    MyString messageContent;
    for (size_t i = 0; i < args.getLength(); i++) {
        messageContent += args[i] + " ";
    }

    messageContent = messageContent.subStr(0, messageContent.getLength() - 1);

    Message message(user.getId(), messageContent);
    system.getMessages().add(message);

    Message* systemMessagePtr = nullptr;
    for (int i = system.messages.getLength() - 1; i >= 0; i--) {
        if (system.messages[i].getId() == message.getId()) {
            systemMessagePtr = &system.messages[i];
        }
    }

    if (systemMessagePtr == nullptr) {
        return CommandResponse(false, "Error");
    }

    for (size_t i = 0; i < system.getUsers().getLength(); i++) {
        if (system.getUsers()[i] != user) {
            system.getUsers()[i].getNewMessage(systemMessagePtr);
        }
    }

    return CommandResponse(true, "Success");
}
