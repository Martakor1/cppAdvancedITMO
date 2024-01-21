#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtClient.h"
#include "ChatMessage.h"
#include "../Client.h"
#include <unordered_set>
#include "MessageWidget.h"

struct Hash {
   size_t operator()(const MessageWidget &w) const {
      return static_cast<size_t>(w.getId().toBytes().data32[0]);
   }
};

class QtClient : public QMainWindow
{
    Q_OBJECT

public:
    QtClient(QWidget *parent = nullptr);
    void showInformation(const QString &message);

public slots:
   void showChatMessage(const ChatMessage &msg);
   void onSocketError(QAbstractSocket::SocketError socketError);

signals:
   void messageCreated(const ChatMessage &msg);

private slots:
   void onSendClicked();
   void onScrollRangeChanged(int min, int max);

private:
    Client client;
    Ui::QtClientClass ui;
    QString appTitle;
    std::unordered_set<MessageWidget, Hash> widgets;
};
