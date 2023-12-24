#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtClient.h"

class QtClient : public QMainWindow
{
    Q_OBJECT

public:
    QtClient(QWidget *parent = nullptr);
    ~QtClient();

private:
    Ui::QtClientClass ui;
};
