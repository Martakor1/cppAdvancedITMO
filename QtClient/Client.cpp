#include "Client.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include "ClientCommand.h"
#include "CommandParseException.cpp"
#include <iostream>

Client::Client() : QObject(), clientSocket(this)
{
	connect(&clientSocket, &QTcpSocket::connected, this, &Client::onSokConnected);
	connect(&clientSocket, &QTcpSocket::disconnected, this, &Client::onSokDisconnected);
	connect(&clientSocket, &QTcpSocket::errorOccurred, this, &Client::displaySokError);
	connect(&clientSocket, &QTcpSocket::readyRead, this, &Client::onSokReadyRead);

   connect(this, &Client::messageReceived, uiWindow, &QtClient::showChatMessage);
   connect(uiWindow, &QtClient::messageCreated, this, &Client::sendMessage);
   uiWindow->show();
   connectToServer();
}

Client::~Client() {
   delete uiWindow;
}

void Client::connectToServer()
{
   //TODO сделать reconnect и отрисовку сообщений о подключении
	clientSocket.connectToHost(hostAddress, port);
}

void Client::receiveMessage(std::shared_ptr<const ChatMessage> msg) // подумать в конце
{
   //vector.push_back(msg)... localCache.store() etc...
   emit messageReceived(*msg.get()); //не очень красивая запись, но в туториалах везде используется ссылка
}

void Client::onSokConnected() {
   ChatMessage msg("Hello world!", "Andrew Glazkov");
   QJsonObject wrapper;
   wrapper["domain"] = "msg";
   wrapper["operation"] = "create";
   wrapper["dto"] = msg.toJson();
   QJsonDocument a(wrapper);
   auto s = QDataStream(&clientSocket);
   s << a.toJson(QJsonDocument::Compact);
}

void Client::displaySokError(QAbstractSocket::SocketError socketError)
{
   switch (socketError) {
   case QAbstractSocket::RemoteHostClosedError:
      break;
   case QAbstractSocket::HostNotFoundError:
      uiWindow->showInformation("The host was not found. Please check the "
         "host name and port settings.");
      break;
   case QAbstractSocket::ConnectionRefusedError:
      uiWindow->showInformation("The connection was refused by the peer. "
            "Make sure the fortune server is running, "
            "and check that the host name and port "
            "settings are correct.");
      break;
   default:
      uiWindow->showInformation("The following error occurred: %1." + clientSocket.errorString());
   }

   // getFortuneButton->setEnabled(true);
}

void Client::onSokReadyRead() {
   QByteArray jsonData;
   QDataStream socketStream(&clientSocket);
   for (;;) {
      // we start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
      socketStream.startTransaction();
      // we try to read the JSON data 
      socketStream >> jsonData;
      if (socketStream.commitTransaction()) {
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

void Client::sendMessage(const ChatMessage& msg)
{
   QJsonObject wrapper;
   wrapper["domain"] = "msg";
   wrapper["operation"] = "create";
   wrapper["dto"] = msg.toJson();
   QDataStream dataStream(&clientSocket);
   dataStream << QJsonDocument(wrapper).toJson(QJsonDocument::Compact);
}


void Client::onSokDisconnected()
{
}
