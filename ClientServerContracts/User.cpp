#include "User.h"

User::User(const QString& username, const QUuid& id):
	username(username), id(id)
{
}

User::User(const QJsonObject& jsonObj):
	User(jsonObj["login"].toString(), QUuid::fromString(jsonObj["id"].toString()))
{
}

const QString& User::getUsername() const
{
	return username;
}

const QUuid& User::getId() const
{
	return id;
}

QJsonObject User::toJson() const
{
	QJsonObject obj;
	obj["username"] = username;
	obj["id"] = id.toString(QUuid::WithoutBraces);
	return obj;
}

bool User::operator==(const User& other) const
{
	return id == other.getId();
}
