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
			QJsonObject obj = doc.object();
			QString str = obj["domain"].toString();
			if (str == "msg")
				domain = Domain::msg;
			else if (str == "login")
				domain = Domain::login;
			else throw CommandParseException("Unsuppoted domain");
			str = obj["operation"].toString();
			if (str == "create")
				crud = CrudType::create;
			else if (str == "update")
				crud = CrudType::update;
			else if (str == "read")
				crud = CrudType::read;
			else if (str == "delete")
				crud = CrudType::del;
			else throw CommandParseException("Unsuppoted crud");
			if (!obj["object"].isObject()) throw CommandParseException("Payload is not object");

			if (domain == Domain::msg) {
				object = obj["object"].toObject();//parse
				objectp = std::shared_ptr<AbstractDto>(new ChatMessage());
			}

			else
				return;
		}
	}
	throw CommandParseException("Message parse error");
}


AbstractCommand::AbstractCommand(Domain domain, CrudType crud, const AbstractDto *object) :
	domain(domain), crud(crud), objectp(object)
{
}