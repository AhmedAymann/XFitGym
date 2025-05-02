
#include <QtWidgets/QMainWindow>
#include "ui_userProfile.h"

class userProfile : public QWidget
{
    Q_OBJECT

public:
    userProfile(QWidget* parent = nullptr);
    ~userProfile();

    Ui::userProfileClass ui;
};
