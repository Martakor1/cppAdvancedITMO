#include "ClientCommand.h"

ClientCommand::ClientCommand(Client *client, char* rawJson, size_t size):
	AbstractCommand(rawJson, size), client(client)
{
}

ClientCommand::ClientCommand(Client* client, Domain domain, CrudType crud, const QJsonObject& object):
	AbstractCommand(domain, crud, object), client(client)
{
}

void ClientCommand::exec()
{
	if (domain == Domain::msg) {
		if (crud == CrudType::create) {
			// вынести создание объектов в abstractcommand
			if (object["username"].isString() && object["text"].isString()) {
				ChatMessage msg(object["text"].toString(), object["username"].toString());
				client->receiveMessage(msg);
			}
		}
		// TODO аналогично
	}
	return;
}


