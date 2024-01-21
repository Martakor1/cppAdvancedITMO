#pragma once
#include <QLabel>
#include <QtWidgets/QWidget>
#include <QUuid>
class MessageWidget : public QWidget {
private:
   QUuid id;
   std::shared_ptr<QLabel> statusLabel;
public:
   enum class Status { delivered, sending };
   MessageWidget(const QUuid& id, const QString& sender, const QString& text, Qt::LayoutDirection horizontalAligment, Status status, QWidget* parent = nullptr);
   MessageWidget(const MessageWidget& other);
   void setStatus(Status newStatus);
   std::shared_ptr<QLabel> getStatusLabel() const;
   const QUuid& getId() const;
   bool operator==(const MessageWidget& other) const;
};