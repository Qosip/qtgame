#ifndef E_NIGHTBORNE_H
#define E_NIGHTBORNE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <random>

class E_Nightborne : public QGraphicsPixmapItem {
private:
    float OriginalX;
    float OriginalY;
    int loop;
    bool b_death;
    int life;
    float max_Health;
    int randomidle;
    int sensrun;
    int loopidle;
    int maxRange;
    bool full_dead;
    bool is_hurting;
    int sens_hurt;
    float scale;
public:
    E_Nightborne(QString img, float Ox, float Oy, int maxR);
    QGraphicsPixmapItem* healthdeco;
    QGraphicsPixmapItem* bar;
    void idle(int sens);
    void attack(int sens);
    void death();
    void run(int sens);
    void health();
    void hurt();
    virtual ~E_Nightborne();
    const bool get_Death(){
        bool d = this->b_death;
        return d;
    }
    const bool get_Hurt(){
        bool d = this->is_hurting;
        return d;
    }
    void set_Hurt(bool loopi) {
        this->is_hurting = loopi;
    }
    const int get_Loop_Idle(){
        int d = this->loopidle;
        return d;
    }
    const float get_Scale(){
        float d = this->scale;
        return d;
    }
    const int get_Random_Idle(){
        int d = this->randomidle;
        return d;
    }
    const int get_Sens_Run(){
        int d = this->sensrun;
        return d;
    }
    const int get_Loop(){
        int d = this->loop;
        return d;
    }
    const bool get_Full_Dead(){
        bool d = this->full_dead;
        return d;
    }
    void set_Loop(int loopi) {
        this->loop = loopi;
    }
    const float get_Ox(){
        float d = this->OriginalX;
        return d;
    }
    const float get_Oy(){
        float d = this->OriginalY;
        return d;
    }
    const int get_Range(){
        int d = this->maxRange;
        return d;
    }
    void set_Loop_Idle(int loopi) {
        this->loopidle = loopi;
    }
    void set_Random_Idle(int randomidle) {
        this->randomidle = randomidle;
    }
    void set_Sens_Run(int sens) {
        this->sensrun = sens;
    }
    void set_Sens_Hurt(int sens) {
        this->sens_hurt = sens;
    }
    void set_Death(bool d) {
        this->b_death = d;
    }
    void set_Oy(float d) {
        this->OriginalY = d;
    }
    const int get_Life(){
        int d = this->life;
        return d;
    }
    void set_Life(int loopi) {
        this->life = loopi;
    }
signals:

};

#endif // E_NIGHTBORNE_H
