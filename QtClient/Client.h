#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "UI/QtClient.h"


class Client : public QObject
{
	Q_OBJECT
private:
	QTcpSocket clientSocket;
	const QHostAddress hostAddress = QHostAddress("127.0.0.1");
	const quint16 port = 1000;
	QtClient *uiWindow;

private slots:
	void onSokConnected();
	void onSokDisconnected();
	void displaySokError(QAbstractSocket::SocketError socketError);
	void onSokReadyRead();

public:
	Client(QtClient *uiWindow);
	void connectToServer();

};

