#ifndef CONTROLTUTO_H
#define CONTROLTUTO_H

#include <QObject>
#include <QGraphicsPixmapItem>

class controlTuto : public QGraphicsPixmapItem {
private:
    float OriginalX;
    float OriginalY;
public:
    controlTuto(QString img, float Ox, float Oy);
    void keyPressed();
    void keyReleased();
    virtual ~controlTuto();
};

#endif // CONTROLTUTO_H
