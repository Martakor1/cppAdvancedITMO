#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtClient.h"
#include "ChatMessage.h"
#include "../Client.h"
#include <unordered_set>
#include "MessageWidget.h"



class QtClient : public QMainWindow
{
    Q_OBJECT

public:
    QtClient(QWidget *parent = nullptr);
    void showInformation(const QString &message);

public slots:
   void showChatMessage(const ChatMessage &msg);
   void onMessageUpdated(const ChatMessage &msg);
   void onSocketError(QAbstractSocket::SocketError socketError);
   void askCredentials();

signals:
   void messageCreated(const ChatMessage &msg);
   void credentialsProduced(QString& username, QString& password, int index);

private slots:
   void onSendClicked();
   void onScrollRangeChanged(int min, int max);

private:
   struct Hash {
      size_t operator()(const QUuid& id) const {
         return static_cast<size_t>(id.toBytes().data32[0]);
      }
   };
   Client client;
   Ui::QtClientClass ui;
   QString appTitle;
   std::unordered_map<QUuid, std::shared_ptr<MessageWidget>, Hash> widgets;
};