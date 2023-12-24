#include "Client.h"
#include <QMessageBox>
Client::Client(QtClient *uiWindow) : QObject(), clientSocket(this), uiWindow(uiWindow)
{
	connect(&clientSocket, &QTcpSocket::connected, this, &Client::onSokConnected);
	connect(&clientSocket, &QTcpSocket::disconnected, this, &Client::onSokDisconnected);
	connect(&clientSocket, &QTcpSocket::errorOccurred, this, &Client::displaySokError);
	connect(&clientSocket, &QTcpSocket::readyRead, this, &Client::onSokReadyRead);
}

void Client::connectToServer()
{
	clientSocket.connectToHost(hostAddress, port);
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

void Client::onSokConnected() {
   return; // остановились тут
}
