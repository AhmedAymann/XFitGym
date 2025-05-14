#include <QtWidgets/QMainWindow>
#include "ui_dashboard.h"
#include <vector>

using namespace std;

class Dashboard : public QWidget
{
    Q_OBJECT

public:

    QFrame* cells[30];
    void clearAttendanceGui();
    void setAttendance(int day, vector<bool> attendance);



    Dashboard(QWidget* parent = nullptr);
    ~Dashboard();
    Ui::DashboardClass ui;
};

class Gauge : public QWidget {
    Q_OBJECT

public:
    explicit Gauge(QWidget* parent = nullptr);

    void setValue(int val);  // 0 to 100

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    int value = 0;
};

