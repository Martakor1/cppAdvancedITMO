#pragma once
#include <QString>
#include <QUuid>
#include "AbstractDto.h"

class ChatMessage : public AbstractDto
{
private:
	QString text;
	QString username;
	QUuid id;
public:
	ChatMessage(const QString &text, const QString &username, const QUuid &id = QUuid::createUuid());
	ChatMessage(const QJsonObject &jsonObj);
	const QString& getText() const;
	const QString& getUsername() const;
	virtual QJsonObject toJson() const override;
};

