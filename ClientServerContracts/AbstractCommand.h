#pragma once
//#include <boost/uuid/uuid.hpp>
#include <QJsonObject>
#include "AbstractDto.h"
#include <QByteArray>


class AbstractCommand
{
public:
	enum class Domain {msg, login};
	enum class CrudType {create, update, read, del, check, ok};
protected:
	Domain domain;
	CrudType crud;
	std::shared_ptr<AbstractDto> dto;
public:
	AbstractCommand(const QByteArray& rawJson);
	AbstractCommand(Domain domain, CrudType crud, std::shared_ptr<AbstractDto> dto);
	const QByteArray toBytes() const;
	Domain getDomain();
	virtual void exec() = 0;
};