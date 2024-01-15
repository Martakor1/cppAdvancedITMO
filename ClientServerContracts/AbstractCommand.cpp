#include "AbstractCommand.h"
#include <QJsonDocument>
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


AbstractCommand::AbstractCommand(Domain domain, CrudType crud, const AbstractDto *dto) :
	domain(domain), crud(crud), dto(dto)
{
}