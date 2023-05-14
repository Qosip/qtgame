#ifndef TILE_H
#define TILE_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QPainter>
#include <qdebug>

class Tile : public QGraphicsPixmapItem {
private:
    int tile_code;
    float OriginalX;
    float OriginalY;
public:
    Tile(QString img, int x, int y, int num, int what, int zIndex) : QGraphicsPixmapItem(QPixmap(img)) {
        if (what == 1){
            this->setPos(x*30.7-30.7, y*40);
            this->setScale(2.0639); //2.0625
            this->OriginalX = x*30.7-30.7;
            this->OriginalY = y*40;
        }
        else if (what==2){
            this->setPos(x*40-40, y*40);
            this->setScale(2.5);
            this->OriginalX = x*40-40;
            this->OriginalY = y*40;
        }
        this->tile_code = num;
        this->setZValue(zIndex);
    }
    const int get_tile_code(){
        int code = this->tile_code;
        return code;
    }
    const int get_OriginalX(){
        int code = this->OriginalX;
        return code;
    }
    const int get_OriginalY(){
        int code = this->OriginalY;
        return code;
    }
    void set_Value(int v) {
        this->tile_code = v;
    }
    virtual ~Tile();
};

#endif // TILE_H
