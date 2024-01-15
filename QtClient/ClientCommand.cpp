#include "ClientCommand.h"

ClientCommand::ClientCommand(Client *client, const QByteArray& rawJson):
	AbstractCommand(rawJson), client(client)
{
}

ClientCommand::ClientCommand(Client* client, Domain domain, CrudType crud, const AbstractDto *dto):
	AbstractCommand(domain, crud, dto), client(client)
{
}

void ClientCommand::exec()
{
	if (domain == Domain::msg) {
		if (crud == CrudType::create) {
			// вынести создание объектов в abstractcommand
			client->receiveMessage(std::dynamic_pointer_cast<const ChatMessage>(dto));
		}
		// TODO аналогично
	}
	return;
}


