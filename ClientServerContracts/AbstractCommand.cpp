#include "AbstractCommand.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "CommandParseException.cpp"
#include "ChatMessage.h"


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
			else throw CommandParseException("Unsuppoted crud");

			if (!jsonObj["dto"].isObject()) throw CommandParseException("Payload is not object");
			QJsonObject dtoJson = jsonObj["dto"].toObject();

			if (domain == Domain::msg) {
				dto = std::shared_ptr<AbstractDto>(new ChatMessage(dtoJson));
			}
			else if (domain == Domain::login) {
				//todo
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

	wrapper["dto"] = dto->toJson();
	return QJsonDocument(wrapper).toJson(QJsonDocument::Compact);
}
