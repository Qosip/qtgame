#include "Controltuto.h"

controlTuto::controlTuto(QString img, float Ox, float Oy) : QGraphicsPixmapItem(QPixmap(img))
{
    this->OriginalX = Ox;
    this->OriginalY = Oy;
    this->setPos(Ox, Oy);
    this->setScale(3);
    this->setZValue(3);
}
void controlTuto::keyPressed(){
    if (this->pos().ry() == OriginalY){
        this->setPos(this->pos().rx(), this->pos().ry()+5);
    }
}
void controlTuto::keyReleased(){
    if (this->pos().ry() != OriginalY){
        this->setPos(OriginalX, OriginalY);
    }
}
controlTuto::~controlTuto(){

}
