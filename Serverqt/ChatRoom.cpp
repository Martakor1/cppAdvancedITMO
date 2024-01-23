#include "ChatRoom.h"

ChatRoom::ChatRoom(): msgs(), clients() {}

void ChatRoom::connectClient(std::shared_ptr<ClientConnection> client) {
	clients.insert(client);
}

void ChatRoom::disconnectClient(std::shared_ptr<ClientConnection> client) {
	clients.erase(client);
}

void ChatRoom::addMessage(std::shared_ptr<ChatMessage> msg) {
	msgs.push_back(msg);
	for (const std::shared_ptr<ClientConnection>& client: clients)
	{
		client->sendMessage(msg);
	}
}
