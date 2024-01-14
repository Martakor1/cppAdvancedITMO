#include "Client.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include "ClientCommand.h"

Client::Client() : QObject(), clientSocket(this)
{
	connect(&clientSocket, &QTcpSocket::connected, this, &Client::onSokConnected);
	connect(&clientSocket, &QTcpSocket::disconnected, this, &Client::onSokDisconnected);
	connect(&clientSocket, &QTcpSocket::errorOccurred, this, &Client::displaySokError);
	connect(&clientSocket, &QTcpSocket::readyRead, this, &Client::onSokReadyRead);
   uiWindow->show();
   connectToServer();
}

Client::~Client() {
   delete uiWindow;
}

void Client::connectToServer()
{
	clientSocket.connectToHost(hostAddress, port);
}

void Client::receiveMessage(const ChatMessage& msg)
{
   //vector.push_back(msg)... localCache.store() etc...
   emit messageReceived(msg);
}

void Client::onSokConnected() {
   ChatMessage msg("Hello world!", "Andrew Glazkov");
   QJsonObject wrapper;
   wrapper["domain"] = "msg";
   wrapper["operation"] = "create";
   wrapper["object"] = msg.toJson();
   QJsonDocument a(wrapper);
   clientSocket.write(a.toJson(QJsonDocument::Compact));
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

void Client::onSokReadyRead()
{
   QByteArray jsonData;
   // create a QDataStream operating on the socket
   QDataStream socketStream(&clientSocket);
   for (;;) {
      // we start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
      socketStream.startTransaction();
      // we try to read the JSON data 
      socketStream >> jsonData;
      if (socketStream.commitTransaction()) {

         ClientCommand(this, jsonData.) // to char

      }
      else {
         // the read failed, the socket goes automatically back to the state it was in before the transaction started
         // we just exit the loop and wait for more data to become available
         break;
      }
}


void Client::onSokDisconnected()
{
}
