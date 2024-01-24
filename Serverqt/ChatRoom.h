#pragma once
#include <vector>
#include <unordered_set>
#include "ClientConnection.h"
#include "ChatMessage.h"
#include <memory>

class ChatRoom {
private:
	struct Hash {
		size_t operator()(const std::shared_ptr<ClientConnection>& clientPtr) const {
			return static_cast<size_t>(clientPtr->getClientId().toBytes().data32[0]);
		}
	};

	struct Equality {
		bool operator()(const std::shared_ptr<ClientConnection>& client1, const std::shared_ptr<ClientConnection>& client2) const {
			return client1->getClientId() == client2->getClientId();
		}
	};

	std::vector<std::shared_ptr<ChatMessage>> msgs;
	std::unordered_set<std::shared_ptr<ClientConnection>, Hash, Equality> clients;
public:
	ChatRoom();
	void connectClient(std::shared_ptr<ClientConnection> client);
	void disconnectClient(std::shared_ptr<ClientConnection> client);
	void addMessage(std::shared_ptr<ChatMessage> msg);
};