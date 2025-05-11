#include "Receptionist_news.h"
Receptionist_news::Receptionist_news(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.chooseImage, &QPushButton::clicked, this, &Receptionist_news::on_chooseButton_clicked);
}
Receptionist_news::~Receptionist_news()
{}


void Receptionist_news::on_chooseButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Choose Image", "", "Images (*.png *.jpg *.jpeg)");
    if (!fileName.isEmpty()) {
        QPixmap newPic(fileName);
        ui.image->setPixmap(newPic.scaled(ui.image->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }

    relativePath = fileName.mid(fileName.indexOf("assets"));
    qDebug() << relativePath;
}