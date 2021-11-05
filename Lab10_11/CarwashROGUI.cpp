#include "CarwashROGUI.h"


void CarwashROGUI::paintEvent(QPaintEvent* ev) {
    QPainter p{ this };
    for (int i = 0; i < wash.getElems().size(); i++)
    {
        string imageName("Images/car");
        int imageNr = rand() % PhotosNr;
        imageName += to_string(imageNr) + ".png";
        QImage img = QImage(QString::fromStdString(imageName)).scaled(50, 50, Qt::KeepAspectRatio);
        p.drawImage(rand() % (width() - img.width()), rand() % (height() - img.height()), img);
    }
}
void CarwashROGUI::update(){
    this->repaint();
}