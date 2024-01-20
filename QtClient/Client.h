#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "UI/QtClient.h"
#include "ChatMessage.h"


class Client : public QObject
{
	Q_OBJECT
private:
	QTcpSocket clientSocket;
	const QHostAddress hostAddress = QHostAddress("127.0.0.1");
	const quint16 port = 1000;
	QtClient *uiWindow = new QtClient();

private slots:
	void onSokConnected();
	void onSokDisconnected();
	void displaySokError(QAbstractSocket::SocketError socketError);
	void onSokReadyRead();

public slots:
	void sendMessage(const ChatMessage &msg);

signals:
	void messageReceived(const ChatMessage &msg);

public:
	Client();
	~Client();
	void connectToServer();
	void receiveMessage(std::shared_ptr<const ChatMessage> msg);
};

