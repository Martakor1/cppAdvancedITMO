#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

class QMyMessageLabel : public QLabel {
public:
	QMyMessageLabel(QWidget* parent = nullptr) : QLabel(parent) {
      QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
      this->setSizePolicy(sizePolicy);
      this->setMinimumSize(QSize(0, 0));
      this->setAutoFillBackground(false);
      this->setStyleSheet(QString::fromUtf8("QLabel {\n"
         "	border-radius: 10px;\n"
         "	background-color: rgb(255, 255, 255);\n"
         "}"));
      this->setScaledContents(true);
      this->setWordWrap(true);
      this->setMargin(10);
      this->setIndent(-1);
      this->setText("Lal");
	};
};