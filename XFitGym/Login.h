
#include <QtWidgets/QMainWindow>
#include "ui_login.h"

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget* parent = nullptr);
    ~Login();

    Ui::LoginClass ui;

private slots:
    void StartLogin();

private:
    bool CheckLogin(QString& username, QString& password);

};
