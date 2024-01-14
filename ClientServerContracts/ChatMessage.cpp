#include "ChatMessage.h"

ChatMessage::ChatMessage(const QString &text, const QString &username):
	text(text), username(username)
{
}

const QString& ChatMessage::getText() const
{
	return text;
}

const QString& ChatMessage::getUsername() const
{
	return username;
}

QJsonObject ChatMessage::toJson() const
{
	QJsonObject obj;
	obj["username"] = username;
	obj["text"] = text;
	return obj;
}