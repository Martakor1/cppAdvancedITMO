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
	QString senderName;
	bool sended;
public:
	ChatMessage(const QString &text, const QUuid &senderId, const QUuid &chatId, bool sended, const QString& senderName, const QUuid &id = QUuid::createUuid());
	ChatMessage(const QJsonObject &jsonObj);
	const QString& getText() const;
	const QUuid& getSenderId() const;
	const QUuid& getId() const;
	const QUuid& getChatId() const;
	const QString& getSenderName() const;
	bool getStatus() const;
	void setStatus(bool isSended);
	virtual QJsonObject toJson() const override;
	~ChatMessage();
};

