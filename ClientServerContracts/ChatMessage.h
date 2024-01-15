#pragma once
#include <QString>
#include "AbstractDto.h"

class ChatMessage : public AbstractDto
{
private:
	QString text;
	QString username;
public:
	ChatMessage(const QString &text, const QString &username);
	ChatMessage(const QJsonObject& jsonObj);
	const QString& getText() const;
	const QString& getUsername() const;
	virtual QJsonObject toJson() const override;
};

