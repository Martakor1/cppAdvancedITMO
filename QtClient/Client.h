#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "ChatMessage.h"
#include "User.h"
#include <unordered_set>


class Client : public QObject
{
	Q_OBJECT
private:
	struct Hash {
		size_t operator()(const std::shared_ptr<ChatMessage>& msgPtr) const {
			return static_cast<size_t>(msgPtr->getId().toBytes().data32[0]);
		}
	};

	QTcpSocket clientSocket;
	const QHostAddress hostAddress = QHostAddress("127.0.0.1");
	const quint16 port = 1000;
	User user;
	std::unordered_set<std::shared_ptr<ChatMessage>, Hash> msgContainer; //возможно можно и без shared_ptr, если владелец этот контейнер

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
	void receiveMessage(std::shared_ptr<ChatMessage> msg);
	const User& getUserById(const QUuid& id) const;
	const User& getUser() const;
};

