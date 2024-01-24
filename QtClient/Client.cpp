#include "Client.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include "ClientCommand.h"
#include "CommandParseException.cpp"
#include <iostream>
#include <QTimer>



Client::Client() : QObject(), clientSocket(this), user("martakor")
{
	connect(&clientSocket, &QTcpSocket::connected, this, &Client::onSokConnected);
	connect(&clientSocket, &QTcpSocket::disconnected, this, &Client::onSokDisconnected);
	connect(&clientSocket, &QTcpSocket::errorOccurred, this, &Client::onSokError);
	connect(&clientSocket, &QTcpSocket::readyRead, this, &Client::onSokReadyRead);

   connectToServer();
}


void Client::onSokError(QAbstractSocket::SocketError sokErr) {
   emit socketError(sokErr);
   QTimer::singleShot(5000, this, &Client::connectToServer);
}

const QTcpSocket& Client::getSocket() const
{
   return clientSocket;
}

void Client::connectToServer()
{
   //TODO сделать reconnect и отрисовку сообщений о подключении
	clientSocket.connectToHost(hostAddress, port);
}

void Client::receiveMessage(std::shared_ptr<ChatMessage> msg) // подумать в конце
{
   msgContainer.insert(msg);
   emit messageReceived(*msg); //не очень красивая запись, но в туториалах везде используется ссылка
}

void Client::updateMessage(std::shared_ptr<ChatMessage> msg) {
   msgContainer.erase(msg);
   msgContainer.insert(msg);
   emit messageUpdated(*msg);
}

const User& Client::getUserById(const QUuid& id) const
{
   //TODO: кеширование
   return user;
}

const User& Client::getUser() const
{
   return user;
}

void Client::onSokConnected() {
   for (const auto& t : msgContainer) {
      if (!t->getStatus()) {
         sendMessage(t);
      }
   }
   /*ChatMessage msg("Hello world!", user.getId(), QUuid::createUuid(), false);
   QJsonObject wrapper;
   wrapper["domain"] = "msg";
   wrapper["operation"] = "create";
   wrapper["dto"] = msg.toJson();
   QJsonDocument a(wrapper);
   auto s = QDataStream(&clientSocket);
   s << a.toJson(QJsonDocument::Compact);*/
}

void Client::onSokReadyRead() {
   QByteArray jsonData;
   QDataStream socketStream(&clientSocket);
   for (;;) {
      // we start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
      socketStream.startTransaction();
      // we try to read the JSON data 
      socketStream >> jsonData;
      if (socketStream.commitTransaction()) { //auto chek that read size of data in first 4 bytes
         try {
            auto c = ClientCommand(this, jsonData); // to char
            c.exec();
         }
         catch (CommandParseException& e) {
            //некорректный json от сервера. Игнорируем?
            std::cout << e.what() << std::endl;
         }
      }
      else {
         // the read failed, the socket goes automatically back to the state it was in before the transaction started
         // we just exit the loop and wait for more data to become available
         break;
      }
   }
}

void Client::onMessageCreated(const ChatMessage& msg) {
   auto pair = msgContainer.insert(std::make_shared<ChatMessage>(msg));
   sendMessage(*pair.first);
}

void Client::sendMessage(std::shared_ptr<ChatMessage> msgPtr)
{
   ClientCommand sendCommand(this, ClientCommand::Domain::msg, ClientCommand::CrudType::create, msgPtr);
   if (clientSocket.state() == QAbstractSocket::ConnectedState) {
      QDataStream dataStream(&clientSocket);
      dataStream << sendCommand.toBytes();
   }
}


void Client::onSokDisconnected()
{
}