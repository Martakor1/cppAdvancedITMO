#include "UI/QtClient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QtClient uiClient;
    return app.exec();
}
