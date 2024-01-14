#include "QtClient.h"
#include "QMessageLabel.cpp"
#include <QMessageBox>

QtClient::QtClient(QWidget *parent)
    : QMainWindow(parent), appTitle("Чат приложение")
{
    ui.setupUi(this);
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

void QtClient::showChatMessage(const ChatMessage& msg)
{
   ui.verticalLayout_chat->addWidget(new QMessageLabel(msg.getText(), ui.scrollAreaWidgetContents));
}
