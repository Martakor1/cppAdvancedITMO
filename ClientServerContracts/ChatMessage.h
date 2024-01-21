#pragma once
#include <QString>
#include <QUuid>
#include "AbstractDto.h"

class ChatMessage : public AbstractDto
{
private:
	QString text;
	QUuid senderId;
	QUuid id;
	QUuid chatId;
public:
	ChatMessage(const QString &text, const QUuid &senderId, const QUuid &chatId, const QUuid &id = QUuid::createUuid());
	ChatMessage(const QJsonObject &jsonObj);
	const QString& getText() const;
	const QUuid& getSenderId() const;
	const QUuid& getId() const;
	const QUuid& getChatId() const;
	virtual QJsonObject toJson() const override;
};

