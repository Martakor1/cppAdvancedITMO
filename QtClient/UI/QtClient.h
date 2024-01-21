#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtClient.h"
#include "ChatMessage.h"
#include "../Client.h"

class QtClient : public QMainWindow
{
    Q_OBJECT

public:
    QtClient(QWidget *parent = nullptr);
    ~QtClient();
    void showInformation(const QString &message);

public slots:
   void showChatMessage(const ChatMessage &msg);
   void onSocketError(QAbstractSocket::SocketError socketError);

signals:
   void messageCreated(const ChatMessage &msg);

private slots:
   void onSendClicked();

private:
    Client client;
    Ui::QtClientClass ui;
    QString appTitle;
};
