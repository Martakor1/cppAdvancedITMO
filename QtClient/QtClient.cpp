#include "QtClient.h"
#include "QMyMessageLabel.cpp"

QtClient::QtClient(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    /*auto genLabel = new QMyMessageLabel((ui.scrollAreaWidgetContents));*/

    /*ui.verticalLayout_2->addWidget(genLabel);*/
    for (int i = 0; i < 10; ++i) {
       ui.verticalLayout_2->insertWidget(ui.verticalLayout_2->count() - 1, new QMyMessageLabel(ui.scrollAreaWidgetContents));
    }

    /*ui.verticalLayout_2->removeItem(ui.verticalSp)*/
    /*auto verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    ui.verticalLayout_2->addItem(verticalSpacer);*/
}

QtClient::~QtClient()
{}
