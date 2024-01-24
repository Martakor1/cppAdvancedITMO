#include "ChatMessage.h"
#include <iostream>

ChatMessage::ChatMessage(const QString &text, const QUuid &senderId, const QUuid& chatId, bool sended, const QUuid &id):
	text(text), senderId(senderId), id(id), chatId(chatId), sended(sended)
{
}

ChatMessage::ChatMessage(const QJsonObject& jsonObj): 
	ChatMessage(jsonObj["text"].toString(), QUuid::fromString(jsonObj["senderId"].toString()),
		QUuid::fromString(jsonObj["chatId"].toString()), jsonObj["sended"].toBool(), QUuid::fromString(jsonObj["id"].toString()))
{ 
}

bool ChatMessage::getStatus() const {
	return sended;
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
	obj["sended"] = sended;
	return obj;
}

void ChatMessage::setStatus(bool isSended) {
	sended = isSended;
}

ChatMessage::~ChatMessage() {
	//почему-то heap corruption при удалении unordered_set<shared_ptr> было, пока оставлю
	std::cout << "I'm die (msg)\n" << text.toStdString() << "\n";
}