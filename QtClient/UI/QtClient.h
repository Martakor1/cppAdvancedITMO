#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtClient.h"
#include "ChatMessage.h"

class QtClient : public QMainWindow
{
    Q_OBJECT

public:
    QtClient(QWidget *parent = nullptr);
    ~QtClient();
    void showInformation(const QString &message);

public slots:
   void showChatMessage(const ChatMessage &msg);

private:
    Ui::QtClientClass ui;
    QString appTitle;
};
