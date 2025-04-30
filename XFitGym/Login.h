
#include <QtWidgets/QMainWindow>
#include "ui_login.h"

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget* parent = nullptr);
    ~Login();
    Ui::LoginClass ui;
};
