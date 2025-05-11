#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Receptionist_news.h"
#include "QFileDialog.h"

class Receptionist_news : public QWidget
{
    Q_OBJECT

public:
    Receptionist_news(QWidget* parent = nullptr);
    ~Receptionist_news();
    Ui::Receptionist_newsClass ui;

    QString relativePath;
private slots:
    void on_chooseButton_clicked();

};
