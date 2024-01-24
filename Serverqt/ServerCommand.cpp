#include "ServerCommand.h"
#include "ChatMessage.h"
#include "ClientConnection.h"

ServerCommand::ServerCommand(ClientConnection* cconn, const QByteArray& rawJson) :
	AbstractCommand(rawJson), clientConn(cconn)
{
}

ServerCommand::ServerCommand(ClientConnection* cconn, Domain domain, CrudType crud, std::shared_ptr<AbstractDto> dto) :
	AbstractCommand(domain, crud, dto), clientConn(cconn)
{
}


void ServerCommand::exec()
{
	if (domain == Domain::msg) {
		if (crud == CrudType::create) {
			clientConn->receiveMessage(std::dynamic_pointer_cast<ChatMessage>(dto));
		}
		/*else if (crud == CrudType::update) {
			clientConn->updateMessage(std::dynamic_pointer_cast<ChatMessage>(dto));
		}*/
		// TODO аналогично
	}
	else if (domain == Domain::login) {
		if (crud == CrudType::check) {
			clientConn->checkLogin(std::dynamic_pointer_cast<User>(dto));
		}
	}
	return;
}