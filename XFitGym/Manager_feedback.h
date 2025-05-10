#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_manager_feedback.h"
class Manager_feedback : public QWidget
{
    Q_OBJECT

public:
    Manager_feedback(QWidget* parent = nullptr);
    ~Manager_feedback();
    Ui::Manager_feedbackClass ui;
};