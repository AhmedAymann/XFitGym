#include <QtWidgets/QMainWindow>
#include "ui_notifications.h"

class Notifications : public QWidget
{
    Q_OBJECT

public:
    Notifications(QWidget* parent = nullptr);
    ~Notifications();

    Ui::NotificationsClass ui;
};