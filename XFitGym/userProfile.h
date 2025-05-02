
#include <QtWidgets/QMainWindow>
#include "ui_userProfile.h"
#include "QFileDialog.h"
class userProfile : public QWidget
{
    Q_OBJECT

public:
    userProfile(QWidget* parent = nullptr);
    ~userProfile();

    Ui::userProfileClass ui;

private slots:
    void on_chooseButton_clicked();
};
