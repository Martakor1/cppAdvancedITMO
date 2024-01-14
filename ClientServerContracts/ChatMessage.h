#pragma once
#include <QString>
#include "JsonSerializable.h"

class ChatMessage : public JsonSerializable
{
private:
	QString text;
	QString username;
public:
	ChatMessage(const QString &text, const QString &username);
	const QString& getText() const;
	const QString& getUsername() const;
	virtual QJsonObject toJson() const override;
};

