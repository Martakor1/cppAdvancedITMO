#include "UI/QtClient.h"
#include <QtWidgets/QApplication>
#include "Client.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Client client = Client();
    return app.exec();
}
