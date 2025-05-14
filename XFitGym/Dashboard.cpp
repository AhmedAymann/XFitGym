#include "Dashboard.h"
#include <QPainter>
#include <QPen>
#include <QtMath>
Dashboard::Dashboard(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    
    //making cells
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 6; ++col) {
            int index = row * 6 + col;
            QFrame* cell = new QFrame(this);
            cell->setFixedSize(30, 30);
            cell->setFrameShape(QFrame::Box);
            cell->setStyleSheet("background-color: #4A4A4A; border: 1px solid white;");

            cells[index] = cell;
            ui.AttendanceSheet->addWidget(cell, row, col);
        }
    }

    
}

//filling cells attended
void Dashboard::setAttendance(int day, vector<bool> attendance)
{

    for (int i = 0; i < attendance.size(); i++) {
        //qDebug() << "attended on day " << i << " Attendance: " << attendance[i];
    }


    if (day != 0) {
        day %= 30;
    }

    if (day % 30 == 0) {
        clearAttendanceGui();
    }
        int i = 0;
        while (i < day) {
            
        if (attendance[i]) {
            cells[i]->setStyleSheet("background-color: #6a5acd; border: 1px solid #8B50FF;");
        }
        else {
            cells[i]->setStyleSheet("background-color: #cd5c5c; border: 1px solid #8B50FF;");
        }
        i++;
        }
}


Dashboard::~Dashboard()
{}


Gauge::Gauge(QWidget* parent) : QWidget(parent) {}

void Gauge::setValue(int val) {
    value = qBound(0, val, 100);  // Clamp between 0 and 100
    update();
}

void Gauge::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Align the gauge center horizontally along the widget's center
    painter.translate(width() / 2, height() / 2);
    painter.translate(-width() / 2, -height() / 2);

    // Adjust the position and width of the rectangle to modify the boundaries
    int side = qMin(width(), height());
    side += 20;  // Expand a bit

    QRectF rect((width() - side) / 2, (height() - side) / 2 + 25, side, side);


    // Background arc (red)
    QPen backPen(QColor(255, 70, 70));
    backPen.setWidth(12);
    painter.setPen(backPen);
    painter.drawArc(rect, 0 * 16, 180 * 16);  // Top half of the circle


    // Progress arc (green)
    QPen progPen(QColor(0, 255, 0));
    progPen.setWidth(13);
    painter.setPen(progPen);
    painter.drawArc(rect, 0 * 16, (value * 180 * 16)  / 100);  // Proportion based on value

}


void Dashboard::clearAttendanceGui() {
    for (int i = 0; i < 30; i++) {
        cells[i]->setStyleSheet("background-color: transparent; border: 1px solid #8B50FF;");
    }
}