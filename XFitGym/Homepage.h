
#include <QtWidgets/QMainWindow>
#include "ui_Homepage.h"

class Homepage : public QWidget
{
    Q_OBJECT

public:
    Homepage(QWidget* parent = nullptr);
    ~Homepage();
    Ui::HomepageClass ui;

};
