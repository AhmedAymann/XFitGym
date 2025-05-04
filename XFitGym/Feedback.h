#include <QtWidgets/QMainWindow>
#include "ui_feedback.h"
#include <stack>
using namespace std;

class Feedback : public QWidget
{
    Q_OBJECT

public:
    Feedback(QWidget* parent = nullptr);
    ~Feedback();

    Ui::FeedbackClass ui;
    static stack<QString>FeedBack;
    void saveFeedBack();
    void loadFeedBack();
};