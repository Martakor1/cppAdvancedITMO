#pragma once
#include "AbstractCommand.h"
#include "Client.h"

class ClientCommand : public AbstractCommand
{
private:
	Client *client;
public:
	ClientCommand(Client *client, const QByteArray& rawJson);
	ClientCommand(Client *client, Domain domain, CrudType crud, const AbstractDto *dto);
	virtual void exec() override;
};

