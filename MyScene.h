#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include "MyView.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Tile.h"
#include <QGraphicsDropShadowEffect>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <ctime>
#include <QGraphicsColorizeEffect>
#include <QGraphicsOpacityEffect>
#include <QBrush>
#include "E_sorcerer.h"
#include <qfontdatabase.h>
#include "Controltuto.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsSceneMouseEvent>
#include <QBitmap>
#include <QGraphicsOpacityEffect>
#include "Checkpoint.h"
#include "E_wolves.h"
#include "E_nightborne.h"
#include <qlineedit.h>
#include <QGraphicsProxyWidget>
#include <QDialog>
#include <qboxlayout.h>
#include <QLabel>
#include <QPushButton>
#include <QCoreApplication>
#include <QRegExpValidator>


using namespace std;
#define G 1 //3
#define PUISSANCE_SAUT -15 //-25
#define PI 3.14159

class MyScene : public QGraphicsScene {
    Q_OBJECT
private:
    int elapsedMs; //
    bool shaking; //
    int puissanceshake; //
    QPixmap background; //
    QTimer* timer; //
    QGraphicsPixmapItem* Personnage; //
    QVector<QPixmap> ImagesRunPerso; //
    QVector<QPixmap> ImagesBackPerso; //
    QVector<QPixmap> ImagesJumpRightPerso; //
    QVector<QPixmap> ImagesJumpLeftPerso; //
    QVector<QPixmap> ImagesIdlePerso; //
    QVector<QPixmap> ImagesHurtPerso; //
    QVector<QPixmap> ImagesSlidePerso; //
    QVector<QPixmap> ImagesArcPerso; //
    QGraphicsPixmapItem* Compagnion; //
    QGraphicsRectItem* elementcentered; //
    QGraphicsRectItem* rect_chest; //
    QVector<Tile*> plateformes; //
    QVector<QGraphicsDropShadowEffect*> shadow; //
    QVector<QGraphicsEllipseItem*> jumpEffect; //
    QVector<Tile*> Background; //
    QVector<QPointF> PosArbreBack; //
    QVector<QPair<int, int>> plateformeFalltoAnim; //
    QVector<QPair<int, int>> plateformeMoveBouncetoAnim; //
    QVector<int> plateformeMovetoAnim; //
    QPair<bool, int> boolForPlatMoveAndPerso[2]; //
    int intindiceplat[2]; //
    int indiceblockfin;
    //COMPAGNON
    int justesortierect; //
    bool procheperso; //
    QPointF* tabComp[50]; //
    QPointF* tabElementcentered[3]; //
    bool pose; //
    int anglecompagnion; //
    int changementangle; //
    float vitCompagnonX; //
    float vitCompagnonY; //
    bool compagnon_back; //
    bool compagnon_run; //
    int boucle_picorer; //
    int picorer; //
    int anim_compagnon; //
    float angle; //
    //constantes liées au background
    int Ybgmid; //
    int Ybgtier; //
    int Ybglast; //
    int bguntier; //
    int bgdeuxtier; //
    int gap_Y; //
    int gap_X; //
    int width_Perso; //
    int v_Y; //
    int v_X; //
    int vitessedroite; //
    int vitessegauche; //
    int piece; //
    int loop; //
    int loop_Coin; //
    int nbkeypress; //

    //Bool de check
    bool hurt_fall; //
    bool is_staying; //
    bool is_running; //
    bool is_backing; //
    bool is_jumping; //
    bool is_falling; //
    bool is_colisionning_left; //
    bool is_colisionning_right; //
    bool is_colisionning_top; //
    bool is_colisionning_bottom; //
    bool saut; //
    bool espace_Pressed; //
    int timeout_espace; //
    float opacite_Bg; //
    int index_chest_anim; //
    int loop_anim_chest; //
    bool can_anim_particle; //
    int loop_anim_particle; //
    bool can_anim_fall; //
    int loop_anim_fall; //
    int posPlatMove; //
    int sensPlatMove; //
    bool can_open_chest; //
    bool e_press_for_chest; //
    int moduloUpdate; //
    bool pauseGame; //
    void drawBackground(QPainter* painter, const QRectF &rect);
    bool changelevel;

    ///////////////////////////////////////////////////

    QVector<E_Sorcerer*> Sorcerer;
    QVector<QGraphicsRectItem*> rect_Sorcerer;
    QVector<QGraphicsRectItem*> rect_Sorcerer_plat;
    QVector<QGraphicsRectItem*> rect_Sorcerer_perso;
    int cooldown_collide_sorcerer;
    QVector<QPair<QGraphicsPixmapItem*, int>> bullet;
    int nb_bullet;
    bool hurting_attack;

    QVector<QGraphicsPixmapItem*> Heart;
    int life;
    QGraphicsPixmapItem* coin;
    QGraphicsTextItem* nbcoin;
    int loopPieceAth;
    int timeInterLevel;
    QGraphicsRectItem* Interlvl;
    bool interlvl2;
    QGraphicsTextItem* Level;
    int temps_slide;
    int puissance_slide;
    bool is_sliding;
    int sens_slide;
    controlTuto* Q;
    controlTuto* D;
    controlTuto* SPACE;
    controlTuto* SHIFT;
    controlTuto* E;
    controlTuto* R;
    controlTuto* secondE;
    controlTuto* secondQ;
    controlTuto* secondD;
    controlTuto* plus;
    QMediaPlayer* player;
    QMediaPlaylist *playlist;
    QMediaPlayer* coinSound;
    QMediaPlayer* SlideSound;
    QMediaPlayer* HighFall;
    QMediaPlayer* Bow;
    QMediaPlayer* Hit;
    QMediaPlayer* HitFromSlide;
    bool is_arcing;
    QVector<QPair<QGraphicsPixmapItem*, int>> fleche;
    QVector <float> gravitefleche;
    QVector <float> rotationfleche;
    QVector<QPixmap> crystal;
    QVector<QPixmap> crystals;
    QGraphicsPixmapItem* CrystalScene;
    QGraphicsPixmapItem* CrystalSceneSombre;
    int loop_crystal;
    float angle_crystal;
    QGraphicsRectItem* RectFinNiv;
    int loop_Anim_Fin;
    bool can_anim_fin;
    QGraphicsPixmapItem* transi_Perso_Fin;
    bool can_hurt_slide;
    QVector <QGraphicsEllipseItem*> opacTile;
    QVector <CheckPoint*> CheckP;
    QPointF RespawnPoint;
    QVector<E_Wolves*> Wolves;
    QVector<QGraphicsRectItem*> rect_Wolves_perso;
    QVector<E_Nightborne*> NightBorne;
    QVector<QGraphicsRectItem*> rect_NightBorne_perso;
    QVector<QGraphicsRectItem*> rect_NightBorne_atk;
    int vague_in_lvl_2;
    bool change_in_lvl_2;
    QTimer* timerGame;
    int timePerso;
    QGraphicsTextItem* timerPrPerso;
    QDialog* menu;
    QDialog* win;
    QDialog* scbord;
    QDialog* dialpause;
    bool tabLevelDone[4];
    bool isInMenu;
    bool isInTuto;
    bool PlayerWin;
    QString Pseudo;
    QLineEdit* linePseudo;
    QGraphicsTextItem* PseudoText;
    QGraphicsTextItem* ScoreText;
    QGraphicsTextItem* TempsText;
    QGraphicsTextItem* CoinText;
    QGraphicsTextItem* Vie;
    bool is_winning;
    bool Menu_Appuie;
    int loop_anim_chest_piece;
    bool anim_piece_chest;
    QVector<QGraphicsTextItem*> ScoreboardLine;
    QVector<QGraphicsRectItem*> Rectscore;
    QGraphicsPixmapItem* coinchest;
    QGraphicsPixmapItem* pausebg;
public:
    MyScene(QObject* parent = nullptr);
    void LoadImage(string Repo, bool NoirOuBlanc);
    QPixmap ToBlack(QPixmap);
    void CreateScene(string File, int nb, int zIndex, string Repo ="tiles", string Repodecor ="decor");
    void AddVectorToScene();
    void Collision();
    void Animation();
    void Background_Parallax();
    void AnimCompagnion();
    void CheckChest();
    void OpenChest();
    void jumpParticle();
    void animParticle();
    void PlatformeFall(int indice, int indicefromq);
    void PlateformeMove();
    void BouncePlatMove(int indice, int indicefromq);
    void CreateLigne(QPointF** tab, int size, QGraphicsPixmapItem* source, QGraphicsPixmapItem* destination);
    void CreateLigne(QPointF** tab, int size, QGraphicsPixmapItem* source, QGraphicsRectItem* destination);
    void ShakeView();
    const int get_score_coin(){
        int score = this->piece;
        return score;
    }
    void createlvltuto();
    void createlvl1();
    void createlvl2();
    void createlvl3();
    void reinitvariable();
    int current_lvl; //cette variable va nous faire changer de niveau
    void CreateEnnemy();
    void CreateEnnemylvl2_1();
    void CreateEnnemylvl2_2();
    void CreateEnnemylvl2_3();
    void CreateEnnemylvl2_end();
    void CheckEnnemy();
    void AnimBulletSorcerer();
    void Ath();
    void MinusOneLife();
    void AddOneLife();
    void InterLevel();
    void Slide();
    void removecontrolsTuto();
    void ArcAttack();
    void AnimFleche();
    void AnimCrystal();
    void createMenu();
    void createDeath();
    void createWin();
    void createScoreboard();
    void animChestPiece();
    void GameIsPaused();
    virtual ~MyScene(); //virtual
protected:

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void update();
    void updateTimeGame();
    void quit();
    void jouer();
    void Menu();
    void MenuScbrd();
    void MenuPaused();
    void Score();
    void Reprendre();
};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
