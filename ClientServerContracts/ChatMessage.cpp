#include "ChatMessage.h"

ChatMessage::ChatMessage(const QString &text, const QUuid &senderId, const QUuid& chatId, const QUuid &id):
	text(text), senderId(senderId), id(id), chatId(chatId)
{
}

ChatMessage::ChatMessage(const QJsonObject& jsonObj): 
	ChatMessage(jsonObj["text"].toString(), QUuid::fromString(jsonObj["senderId"].toString()),
		QUuid::fromString(jsonObj["chatId"].toString()), QUuid::fromString(jsonObj["id"].toString()))
{ 
}

const QString& ChatMessage::getText() const
{
	return text;
}

const QUuid& ChatMessage::getSenderId() const
{
	return senderId;
}

const QUuid& ChatMessage::getId() const
{
	return id;
}

const QUuid& ChatMessage::getChatId() const
{
	return chatId;
}

QJsonObject ChatMessage::toJson() const
{
	QJsonObject obj;
	obj["senderId"] = senderId.toString(QUuid::WithoutBraces);
	obj["text"] = text;
	obj["id"] = id.toString(QUuid::WithoutBraces);
	obj["chatId"] = chatId.toString(QUuid::WithoutBraces);
	return obj;
}
