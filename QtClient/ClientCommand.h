#pragma once
#include "AbstractCommand.h"
#include "Client.h"

class ClientCommand : public AbstractCommand
{
private:
	Client *client;
public:
	ClientCommand(Client *client, char *rawJson, size_t size);
	ClientCommand(Client *client, Domain domain, CrudType crud, const QJsonObject& object);
	virtual void exec() override;
};

