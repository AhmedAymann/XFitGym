
#include <QtWidgets/QMainWindow>
#include "ui_Padel.h"

class Padel : public QWidget
{
    Q_OBJECT

public:
    Padel(QWidget* parent = nullptr);
    ~Padel();
    Ui::PadelClass ui;
    QPushButton* selectedSlot = nullptr;
    QString selectedDay;
    QString selectedTime;

};
