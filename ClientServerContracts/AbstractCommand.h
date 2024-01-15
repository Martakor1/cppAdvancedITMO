#pragma once
//#include <boost/uuid/uuid.hpp>
#include <QJsonObject>
#include "AbstractDto.h"


class AbstractCommand
{
public:
	enum class Domain {msg, login};
	enum class CrudType {create, update, read, del};
protected:
	Domain domain;
	CrudType crud;
	std::shared_ptr<const AbstractDto> dto;
public:
	AbstractCommand(const QByteArray& rawJson);
	AbstractCommand(Domain domain, CrudType crud, const AbstractDto *dto);
	//~AbstractCommand();
	virtual void exec() = 0;
};