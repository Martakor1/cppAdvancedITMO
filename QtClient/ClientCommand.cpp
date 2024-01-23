#include "ClientCommand.h"

ClientCommand::ClientCommand(Client *client, const QByteArray& rawJson):
	AbstractCommand(rawJson), client(client)
{
}

ClientCommand::ClientCommand(Client* client, Domain domain, CrudType crud, std::shared_ptr<AbstractDto> dto):
	AbstractCommand(domain, crud, dto), client(client)
{
}


void ClientCommand::exec()
{
	if (domain == Domain::msg) {
		if (crud == CrudType::create) {
			// вынести создание объектов в abstractcommand
			client->receiveMessage(std::dynamic_pointer_cast<ChatMessage>(dto));
		}
		else if (crud == CrudType::update) { //протестировать update
			client->updateMessage(std::dynamic_pointer_cast<ChatMessage>(dto));
		}
		// TODO аналогично
	}
	return;
}