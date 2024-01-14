#pragma once
#include <QJsonObject>
class AbstractDto
{
public:
	virtual QJsonObject toJson() const = 0;
};

