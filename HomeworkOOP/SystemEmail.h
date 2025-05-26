#pragma once
#include "List.hpp"
#include "Message.h"

class SystemEmail {
public:
	void addToSendMessagesNewMessage(const Message* newMessage);
	void getNewMessage(const Message* newMessage);
	const List<const Message*>& getMessagesSend() const;
	const List<const Message*>& getMessagesReceived() const;
private:
	List<const Message*> messagesSend;
	List<const Message*> messagesReceived;
};
