#include "User.h"

User::User(const QString& username, const QString &password, const QUuid& id):
	username(username), id(id), password(password)
{
}

User::User(const QJsonObject& jsonObj):
	User(jsonObj["username"].toString(), jsonObj["password"].toString(), QUuid::fromString(jsonObj["id"].toString()))
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
	obj["password"] = password;
	return obj;
}

bool User::operator==(const User& other) const
{
	return id == other.getId();
}


const QString& User::getPassword() const {
	return password;
}

User& User::operator=(const User& other) {
	username =  other.getUsername();
	password = other.getPassword();
	id = other.getId();
	return *this;
}
