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
