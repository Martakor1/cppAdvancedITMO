#include "QtClient.h"
#include "MessageWidget.h"
#include <QMessageBox>
#include <QScrollBar>

QtClient::QtClient(QWidget *parent)
    : QMainWindow(parent), appTitle("Чат приложение"), client()
{
    ui.setupUi(this);
    connect(ui.sendButton, &QPushButton::clicked, this, &QtClient::onSendClicked);
    connect(ui.messageEdit, &QLineEdit::returnPressed, this, &QtClient::onSendClicked);


    connect(&client, &Client::socketError, this, &QtClient::onSocketError);
    connect(&client, &Client::messageReceived, this, &QtClient::showChatMessage);
    connect(this, &QtClient::messageCreated, &client, &Client::sendMessage);

    connect(ui.scrollArea->verticalScrollBar(), &QScrollBar::rangeChanged, this, &QtClient::onScrollRangeChanged);
    this->show();

    //connect(&ui.sendButton, &QPushButton::clicked, this, )
    /*auto genLabel = new QMyMessageLabel((ui.scrollAreaWidgetContents));*/

    /*ui.verticalLayout_2->addWidget(genLabel);*/
    /*for (int i = 0; i < 10; ++i) {
       ui.verticalLayout_chat->insertWidget(ui.verticalLayout_chat->count() - 1, new QMessageLabel(ui.scrollAreaWidgetContents));
    }*/

    /*ui.verticalLayout_2->removeItem(ui.verticalSp)*/
    /*auto verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    ui.verticalLayout_2->addItem(verticalSpacer);*/
}

void QtClient::showInformation(const QString &message) {
   QMessageBox::information(this, appTitle, message);
}

void QtClient::showChatMessage(const ChatMessage& msg) {
   auto layout = Qt::LayoutDirection::LeftToRight;
   const User& sender = client.getUserById(msg.getSenderId());
   auto status = MessageWidget::Status::delivered;
   if (sender == client.getUser()) {
      layout = Qt::LayoutDirection::RightToLeft;
      status = MessageWidget::Status::sending;
   }

   auto pair = widgets.insert({msg.getId(), std::make_shared<MessageWidget>(sender.getUsername(), msg.getText(), layout, status, ui.scrollAreaWidgetContents)});
   ui.verticalLayout_chat->addWidget(pair.first->second.get());
}

void QtClient::onSocketError(QAbstractSocket::SocketError socketError)
{
   switch (socketError) {
   case QAbstractSocket::RemoteHostClosedError:
      break;
   case QAbstractSocket::HostNotFoundError:
      showInformation("The host was not found. Please check the "
         "host name and port settings.");
      break;
   case QAbstractSocket::ConnectionRefusedError:
      showInformation("The connection was refused by the peer. "
         "Make sure the fortune server is running, "
         "and check that the host name and port "
         "settings are correct.");
      break;
   default:
      showInformation("The following error occurred: %1." + client.getSocket().errorString());
   }
}

void QtClient::onSendClicked()
{
   QString text = ui.messageEdit->text();
   if (!text.trimmed().isEmpty()) {
      ChatMessage msg(text, client.getUser().getId(), QUuid::createUuid()); //TODO Chat
      emit messageCreated(msg);
   }
   ui.messageEdit->clear();
}

void QtClient::onScrollRangeChanged(int min, int max)
{
   ui.scrollArea->verticalScrollBar()->setValue(max);
}
