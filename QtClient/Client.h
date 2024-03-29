#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "ChatMessage.h"
#include "User.h"
#include <unordered_set>
#include "ClientCommand.h"


class Client : public QObject
{
	Q_OBJECT
private:
	struct Hash {
		size_t operator()(const std::shared_ptr<ChatMessage>& msgPtr) const {
			return static_cast<size_t>(msgPtr->getId().toBytes().data32[0]);
		}
	};

	struct Equality {
		bool operator()(const std::shared_ptr<ChatMessage>& msgPtr1, const std::shared_ptr<ChatMessage>& msgPtr2) const {
			return msgPtr1->getId() == msgPtr2->getId();
		}
	};

	QTcpSocket clientSocket;
	const QHostAddress hostAddress = QHostAddress("127.0.0.1");
	const quint16 port = 1000;
	User user;
	std::unordered_set<std::shared_ptr<ChatMessage>, Hash, Equality> msgContainer; //возможно можно и без shared_ptr, если владелец этот контейнер
	bool credAsked = false;
	void sendCommand(const ClientCommand& command);
	

private slots:
	void onSokConnected();
	void onSokDisconnected();
	void onSokReadyRead();
	void onSokError(QAbstractSocket::SocketError socketError);

public slots:
	void onMessageCreated(const ChatMessage& msg);
	void connectToServer();
	void setCredentials(const User& user);
	void setCredFromUi(QString& username, QString &password, int index);

signals:
	void messageReceived(const ChatMessage &msg);
	void messageUpdated(const ChatMessage &msg);
	void socketError(QAbstractSocket::SocketError sokErr);
	void loginError();

public:
	Client();
	void receiveMessage(std::shared_ptr<ChatMessage> msg);
	void sendMessage(std::shared_ptr<ChatMessage> msg);
	void updateMessage(std::shared_ptr<ChatMessage> msg);
	void sendCredentials(ClientCommand::CrudType type, std::shared_ptr<User> user);
	void sendDataAfterLogin();
	const QTcpSocket& getSocket() const;
	const User& getUserById(const QUuid& id) const;
	const User& getUser() const;
};

