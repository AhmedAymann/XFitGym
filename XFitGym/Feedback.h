#include <QtWidgets/QMainWindow>
#include "ui_feedback.h"

class Feedback : public QWidget
{
    Q_OBJECT

public:
    Feedback(QWidget* parent = nullptr);
    ~Feedback();

    Ui::FeedbackClass ui;
};