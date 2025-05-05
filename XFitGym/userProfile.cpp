#include "userProfile.h"
userProfile::userProfile(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.chooseImage, &QPushButton::clicked, this, &userProfile::on_chooseButton_clicked);

}
userProfile::~userProfile()
{}

void userProfile::on_chooseButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Choose Image", "", "Images (*.png *.jpg *.jpeg)");
    if (!fileName.isEmpty()) {
        QPixmap newPic(fileName);
        ui.profilePicture->setPixmap(newPic.scaled(ui.profilePicture->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }
    
    QString relativePath = fileName.mid(fileName.indexOf("assets"));
    qDebug() << relativePath;
}
