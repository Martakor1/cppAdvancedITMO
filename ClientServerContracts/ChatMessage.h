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
	bool sended;
public:
	ChatMessage(const QString &text, const QUuid &senderId, const QUuid &chatId, bool sended, const QUuid &id = QUuid::createUuid());
	ChatMessage(const QJsonObject &jsonObj);
	const QString& getText() const;
	const QUuid& getSenderId() const;
	const QUuid& getId() const;
	const QUuid& getChatId() const;
	bool getStatus() const;
	virtual QJsonObject toJson() const override;
	~ChatMessage();
};

