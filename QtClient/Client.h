#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "ChatMessage.h"
#include "User.h"

class Client : public QObject
{
	Q_OBJECT
private:
	QTcpSocket clientSocket;
	const QHostAddress hostAddress = QHostAddress("127.0.0.1");
	const quint16 port = 1000;
	User user;

private slots:
	void onSokConnected();
	void onSokDisconnected();
	void onSokReadyRead();

public slots:
	void sendMessage(const ChatMessage &msg);
	void connectToServer();

signals:
	void messageReceived(const ChatMessage &msg);
	void socketError(QAbstractSocket::SocketError socketError);

public:
	Client();
	const QTcpSocket& getSocket() const;
	void receiveMessage(std::shared_ptr<const ChatMessage> msg);
	const User& getUserById(const QUuid& id) const;
	const User& getUser() const;
};

