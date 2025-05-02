
#include <QtWidgets/QMainWindow>
#include "ui_login.h"
#include "qtimer.h"


class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget* parent = nullptr);
    ~Login();

    Ui::LoginClass ui;

public slots:
    bool CheckLogin(QString& username, QString& password);

};
