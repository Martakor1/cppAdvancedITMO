#pragma once
#include <QLabel>
#include <QtWidgets/QWidget>
#include <QUuid>
#include "ChatMessage.h"

class MessageWidget : public QWidget {
private:
   std::unique_ptr<QLabel> statusLabel;
   std::unique_ptr<QLabel> nameLabel;
   std::unique_ptr<QLabel> messageLabel;
public:
   enum class Status { delivered, sending }; //можно убрать...
   MessageWidget(const ChatMessage& msg, const QString& sender, Qt::LayoutDirection horizontalAligment, QWidget* parent = nullptr);
   MessageWidget(const MessageWidget& other);
   void updateFromMsg(const ChatMessage &msg);
   void setStatus(bool sended);
};