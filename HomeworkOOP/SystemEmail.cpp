#include "SystemEmail.h"
#include <stdexcept>

void SystemEmail::addToSendMessagesNewMessage(const Message* newMessage) {
    if (newMessage == nullptr) {
        throw std::invalid_argument("Can not add nullptr");
    }

    this->messagesSend.add(newMessage);
}

void SystemEmail::getNewMessage(const Message* newMessage) {
    if (newMessage == nullptr) {
        throw std::invalid_argument("Can not add nullptr");
    }

    this->messagesReceived.add(newMessage);
}

const List<const Message*>& SystemEmail::getMessagesSend() const {
    return this->messagesSend;
}

const List<const Message*>& SystemEmail::getMessagesReceived() const {
    return this->messagesReceived;
}
