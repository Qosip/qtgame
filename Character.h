#ifndef CHARACTER_H
#define CHARACTER_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QPainter>

class Character : public QGraphicsPixmapItem
{
private:
    int* posX;
    int* posY;
    int* width;
    int* height;
    int* v_X;
    int* v_Y;
public:
    Character(QString img, int x, int y, int w, int h) : QGraphicsPixmapItem(QPixmap(img).scaled(w, h)){
        this->setPos(x, y);
    }
    virtual ~Character();
signals:

};

#endif // CHARACTER_H
