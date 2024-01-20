#include "ChatMessage.h"

ChatMessage::ChatMessage(const QString &text, const QString &username, const QUuid &id):
	text(text), username(username), id(id)
{
}

ChatMessage::ChatMessage(const QJsonObject& jsonObj): 
	ChatMessage(jsonObj["text"].toString(), jsonObj["username"].toString(), QUuid::fromString(jsonObj["id"].toString()))
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
	obj["id"] = id.toString(QUuid::WithoutBraces);
	return obj;
}
