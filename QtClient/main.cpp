#include "UI/QtClient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtClient mainWindow;
    mainWindow.show();
    return app.exec();
}
