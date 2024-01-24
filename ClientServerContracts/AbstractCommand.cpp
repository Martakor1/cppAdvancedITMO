#include "AbstractCommand.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "CommandParseException.cpp"
#include "ChatMessage.h"
#include "User.h"


AbstractCommand::AbstractCommand(const QByteArray& rawJson)
{
	QJsonParseError err;
	QJsonDocument doc = QJsonDocument::fromJson(rawJson, &err);
	if (err.error == QJsonParseError::NoError) {
		if (doc.isObject()) {
			QJsonObject jsonObj = doc.object();
			QString str = jsonObj["domain"].toString();
			if (str == "msg")
				domain = Domain::msg;
			else if (str == "login")
				domain = Domain::login;
			else throw CommandParseException("Unsuppoted domain");

			str = jsonObj["operation"].toString();
			if (str == "create")
				crud = CrudType::create;
			else if (str == "update")
				crud = CrudType::update;
			else if (str == "read")
				crud = CrudType::read;
			else if (str == "delete")
				crud = CrudType::del;
			else if (str == "check")
				crud = CrudType::check;
			else if (str == "ok")
				crud = CrudType::ok;
			else throw CommandParseException("Unsuppoted crud");

			if (!jsonObj["dto"].isObject()) throw CommandParseException("Payload is not object");
			QJsonObject dtoJson = jsonObj["dto"].toObject();

			if (domain == Domain::msg) {
				dto = std::shared_ptr<AbstractDto>(new ChatMessage(dtoJson));
			}
			else if (domain == Domain::login) {
				dto = std::shared_ptr<AbstractDto>(new User(dtoJson));
			}
			return;
		}
	}
	throw CommandParseException("Message parse error");
}


AbstractCommand::AbstractCommand(Domain domain, CrudType crud, std::shared_ptr<AbstractDto> dto) :
	domain(domain), crud(crud), dto(dto)
{
}

AbstractCommand::Domain AbstractCommand::getDomain() {
	return domain;
}

const QByteArray AbstractCommand::toBytes() const
{
	QJsonObject wrapper;
	if (domain == Domain::msg)
		wrapper["domain"] = "msg";
	else if (domain == Domain::login)
		wrapper["domain"] = "login";

	if (crud == CrudType::create)
		wrapper["operation"] = "create";
	else if (crud == CrudType::update)
		wrapper["operation"] = "update";
	else if (crud == CrudType::read)
		wrapper["operation"] = "read";
	else if (crud == CrudType::del)
		wrapper["operation"] = "delete";
	else if (crud == CrudType::check)
		wrapper["operation"] = "check";
	else if (crud == CrudType::ok)
		wrapper["operation"] = "ok";

	wrapper["dto"] = dto->toJson();
	return QJsonDocument(wrapper).toJson(QJsonDocument::Compact);
}
