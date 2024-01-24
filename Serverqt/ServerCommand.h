#pragma once
#include "AbstractCommand.h"

class ClientConnection;

class ServerCommand : public AbstractCommand
{
private:
	ClientConnection* clientConn;
public:
	ServerCommand(ClientConnection* cconn, const QByteArray& rawJson);
	ServerCommand(ClientConnection* cconn, Domain domain, CrudType crud, std::shared_ptr<AbstractDto> dto);
	virtual void exec() override;
};