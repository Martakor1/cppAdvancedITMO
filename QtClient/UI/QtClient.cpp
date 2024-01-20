#include "QtClient.h"
#include "MessageWidget.cpp"
#include <QMessageBox>

QtClient::QtClient(QWidget *parent)
    : QMainWindow(parent), appTitle("Чат приложение")
{
    ui.setupUi(this);
    connect(ui.sendButton, &QPushButton::clicked, this, &QtClient::onSendClicked);
    connect(ui.messageEdit, &QLineEdit::returnPressed, this, &QtClient::onSendClicked);
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

QtClient::~QtClient()
{}

void QtClient::showInformation(const QString &message) {
   QMessageBox::information(this, appTitle, message);
}

void QtClient::showChatMessage(const ChatMessage& msg) //depending on who?
{
   ui.verticalLayout_chat->addWidget(new MessageWidget("Andrew", msg.getText(), Qt::LayoutDirection::RightToLeft, ui.scrollAreaWidgetContents));
}

void QtClient::onSendClicked()
{
   QString text = ui.messageEdit->text();
   if (!text.trimmed().isEmpty()) {
      ChatMessage msg(text, "andrew"); //TODO NAME
      emit messageCreated(msg);
   }
   ui.messageEdit->clear();
}