#include "MessageWidget.h"
#include <QVboxLayout>

MessageWidget::MessageWidget(const QString &sender, const QString &text, Qt::LayoutDirection horizontalAligment, Status status, QWidget* parent)
      : QWidget(parent), statusLabel(new QLabel())
{
      auto verticalLayout = new QVBoxLayout(this);
      verticalLayout->setSpacing(6);


      auto nameLabel = new QLabel();
      nameLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum));
      nameLabel->setLayoutDirection(horizontalAligment);
      nameLabel->setText(sender);

      verticalLayout->addWidget(nameLabel);

      auto messageLabel = new QLabel();
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
      messageLabel->setText(text);

      verticalLayout->addWidget(messageLabel);



      statusLabel->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum));
      statusLabel->setLayoutDirection(horizontalAligment);
      setStatus(status);
      verticalLayout->addWidget(statusLabel.get());
}
MessageWidget::MessageWidget(const MessageWidget& other): statusLabel(other.getStatusLabel())
{
}
;

void MessageWidget::setStatus(Status newStatus) {
   if (newStatus == Status::sending)
      statusLabel->setText("Отправка");
   else
      statusLabel->setText("Доставлено");
}

std::shared_ptr<QLabel> MessageWidget::getStatusLabel() const
{
   return statusLabel;
}
