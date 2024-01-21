#pragma once
#include "AbstractDto.h"
#include <QString>
#include <QUuid>

class User : public AbstractDto
{
private:
	QString username;
	QUuid id;
public:
	User(const QString& username, const QUuid& id = QUuid::createUuid());
	User(const QJsonObject& jsonObj);
	const QString& getUsername() const;
	const QUuid& getId() const;
	virtual QJsonObject toJson() const override;
	bool operator==(const User& other) const;
};

