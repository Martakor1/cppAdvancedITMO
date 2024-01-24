#pragma once
#include "AbstractCommand.h"

class Client;

class ClientCommand : public AbstractCommand
{
private:
	Client *client;
public:
	ClientCommand(Client *client, const QByteArray& rawJson);
	ClientCommand(Client *client, Domain domain, CrudType crud, std::shared_ptr<AbstractDto> dto);
	virtual void exec() override;
};

