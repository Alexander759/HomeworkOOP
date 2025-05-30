#include "SystemEmail.h"
#include <stdexcept>

void SystemEmail::addToSendMessagesNewMessage(size_t newMessageId) {
    this->messagesSendIds.add(newMessageId);
}

void SystemEmail::getNewMessage(size_t newMessageId) {
    this->messagesReceivedIds.add(newMessageId);
}

const List<size_t>& SystemEmail::getMessagesSendIds() const {
    return this->messagesSendIds;
}

List<size_t>& SystemEmail::getMessagesSendIds() {
    return this->messagesSendIds;
}

const List<size_t>& SystemEmail::getMessagesReceivedIds() const {
    return this->messagesReceivedIds;
}

List<size_t>& SystemEmail::getMessagesReceivedIds() {
    return this->messagesReceivedIds;
}

std::ofstream& operator<<(std::ofstream& stream, const SystemEmail& systemEmail) {
    if (!stream.is_open()) {
        return stream;
    }

    stream << systemEmail.messagesSendIds;
    stream << systemEmail.messagesReceivedIds;

    return stream;
}

std::ifstream& operator>>(std::ifstream& stream, SystemEmail& systemEmail) {
    if (!stream.is_open()) {
        return stream;
    }

    stream >> systemEmail.messagesSendIds;
    stream >> systemEmail.messagesReceivedIds;

    return stream;
}
