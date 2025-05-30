#pragma once
#include "List.hpp"
#include "Message.h"

class SystemEmail {
public:
	void addToSendMessagesNewMessage(size_t newMessageId);
	void getNewMessage(size_t newMessageId);
	const List<size_t>& getMessagesSendIds() const;
	List<size_t>& getMessagesSendIds();
	const List<size_t>& getMessagesReceivedIds() const;
	List<size_t>& getMessagesReceivedIds();

	friend std::ofstream& operator<<(std::ofstream& stream, const SystemEmail& systemEmail);
	friend std::ifstream& operator>>(std::ifstream& stream, SystemEmail& systemEmail);

private:
	List<size_t> messagesSendIds;
	List<size_t> messagesReceivedIds;
};
