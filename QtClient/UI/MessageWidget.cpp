#include "MessageWidget.h"
#include <QVboxLayout>

MessageWidget::MessageWidget(const ChatMessage& msg, const QString &sender, Qt::LayoutDirection horizontalAligment, QWidget* parent)
      : QWidget(parent), statusLabel(new QLabel(this)), nameLabel(new QLabel(this)), messageLabel(new QLabel(this))
{
      auto verticalLayout = new QVBoxLayout(this);
      verticalLayout->setSpacing(6);

      nameLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum));
      nameLabel->setLayoutDirection(horizontalAligment);
      nameLabel->setText(sender);

      verticalLayout->addWidget(nameLabel.get());

      QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Minimum);

      sizePolicy1.setHeightForWidth(messageLabel->sizePolicy().hasHeightForWidth());
      messageLabel->setSizePolicy(sizePolicy1);
      messageLabel->setMaximumSize(QSize(500, 16777215));
      messageLabel->setLayoutDirection(horizontalAligment);
      messageLabel->setAutoFillBackground(false);
      messageLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
         "	border-radius: 10px;\n"
         "	background-color: rgb(255, 255, 255);\n"
         "}"));
      messageLabel->setScaledContents(true);
      messageLabel->setWordWrap(true);
      messageLabel->setMargin(10);
      messageLabel->setIndent(-1);
      messageLabel->setText(msg.getText());

      verticalLayout->addWidget(messageLabel.get());



      statusLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum));
      statusLabel->setLayoutDirection(horizontalAligment);
      setStatus(msg.getStatus());
      verticalLayout->addWidget(statusLabel.get());
}
//MessageWidget::MessageWidget(const MessageWidget& other): statusLabel(other.getStatusLabel())
//{
//}
//;

void MessageWidget::setStatus(bool sended) {
   if (sended == false)
      statusLabel->setText("Отправка");
   else
      statusLabel->setText("Доставлено");
}

void MessageWidget::updateFromMsg(const ChatMessage& msg) {
   setStatus(msg.getStatus());
   messageLabel->setText(msg.getText());
}
