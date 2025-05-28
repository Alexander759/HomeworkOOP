#pragma once
#include "List.hpp"
#include "Message.h"

class SystemEmail {
public:
	void addToSendMessagesNewMessage(size_t newMessageId);
	void getNewMessage(size_t newMessageId);
	const List<size_t>& getMessagesSendIds() const;
	const List<size_t>& getMessagesReceivedIds() const;
private:
	List<size_t> messagesSendIds;
	List<size_t> messagesReceivedIds;
};
