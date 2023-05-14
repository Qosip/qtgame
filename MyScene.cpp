#include "MyScene.h"
#include "math.h"

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent) {
    //Init of all the variable
    srand(time(nullptr));
    this->puissanceshake = 15;
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(15); // 30 //7 possible pour anim payante
    this->timerGame = new QTimer(this);
    this->timerGame->start(10);
    this->timePerso = 0;
    connect(timerGame, SIGNAL(timeout()), this, SLOT(updateTimeGame()));
    //Création du PixmapItem sur lequel sera notre personnage
    this->Personnage = new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/character/character1/Idle/idle1.png"));
    this->addItem(Personnage);
    this->width_Perso = Personnage->boundingRect().width();
    this->Personnage->setZValue(4);
    this->Personnage->setPos(100,1.3*bguntier);
    this->Personnage->boundingRect() = QRectF(0,0,52,70);
    this->Compagnion = new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/environement/companion/fly_run/fly1.png"));
    this->addItem(Compagnion);
    this->Compagnion->setZValue(4.1);
    this->Compagnion->setPos(100,1.3*bguntier);
    this->Compagnion->setScale(2);
    this->elementcentered = new QGraphicsRectItem(0, 0, 0, 0);
    this->addItem(elementcentered);
    this->elementcentered->setPos(0,0);
    //Init de la vitesse du perso
    this->pauseGame = false;
    QPixmap back("../qtprojetbase/src/environement/background/backlvl1.png");
    this->background = back;//.load("../qtprojetbase/src/environement/background/backlvl1.png"); //2.0625
    this->setSceneRect(0, 0, background.width()/**6.19*/, background.height()/**6.19*/);
    this->Ybgmid = background.height()/2;
    this->Ybgtier = background.height()/2 - background.height()/3;
    this->Ybglast = background.height()/2 + background.height()/3;
    this->bguntier = background.height()/3;
    this->bgdeuxtier = this->Ybgtier+this->Ybgmid;
    current_lvl= 0;
    changelevel = false;
    ImagesRunPerso = QVector<QPixmap>();
    ImagesBackPerso = QVector<QPixmap>();
    ImagesJumpRightPerso = QVector<QPixmap>();
    ImagesJumpLeftPerso = QVector<QPixmap>();
    ImagesIdlePerso = QVector<QPixmap>();
    ImagesHurtPerso = QVector<QPixmap>();
    plateformes = QVector<Tile*>();
    shadow = QVector<QGraphicsDropShadowEffect*>();
    jumpEffect = QVector<QGraphicsEllipseItem*>();
    Background = QVector<Tile*>();
    plateformeFalltoAnim = QVector<QPair<int, int>>();
    plateformeMoveBouncetoAnim = QVector<QPair<int, int>>();
    plateformeMovetoAnim = QVector<int>();
    PosArbreBack = QVector<QPointF>();
    Heart = QVector<QGraphicsPixmapItem*>();
    ImagesSlidePerso = QVector<QPixmap>();
    ImagesArcPerso = QVector<QPixmap>();
    opacTile = QVector<QGraphicsEllipseItem*>();
    CheckP = QVector<CheckPoint*>();
    Wolves = QVector<E_Wolves*>();
    rect_Wolves_perso = QVector<QGraphicsRectItem*>();
    NightBorne = QVector<E_Nightborne*>();
    rect_NightBorne_perso = QVector<QGraphicsRectItem*>();
    rect_NightBorne_atk = QVector<QGraphicsRectItem*>();
    rect_Sorcerer = QVector<QGraphicsRectItem*>();
    rect_Sorcerer_plat = QVector<QGraphicsRectItem*>();
    rect_Sorcerer_perso = QVector<QGraphicsRectItem*>();
    ScoreboardLine = QVector<QGraphicsTextItem*>();
    Rectscore = QVector<QGraphicsRectItem*>();

    this->nbkeypress = 0;
    Pseudo = QString("");
    Menu_Appuie = false;

    PlayerWin = false;
    hurting_attack = false;
    tabLevelDone[0] = false;
    tabLevelDone[1] = false;
    tabLevelDone[2] = false;
    tabLevelDone[3] = false;

    for(int i = 0; i<5; i++){
        Heart.push_back(new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/character/Heart/heart5.png")));
        Heart[i]->setPos(elementcentered->pos().rx()+17*i, elementcentered->pos().ry());
        Heart[i]->setZValue(20);
        Heart[i]->setScale(1.5);
        addItem(Heart[i]);
    }
    this->piece = 0;
    this->life = 25;
    this->coin = new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/environement/decor/1.png"));
    coin->setScale(3);
    coin->setZValue(20);
    coin->setPos(0,0);
    addItem(coin);

    this->Q = new controlTuto("../qtprojetbase/src/environement/controlstuto/keyQ", 250, 1100);
    addItem(Q);
    this->D = new controlTuto("../qtprojetbase/src/environement/controlstuto/keyD", 300, 1100);
    addItem(D);
    this->SPACE = new controlTuto("../qtprojetbase/src/environement/controlstuto/keySPACE", 176, 1145);
    addItem(SPACE);
    this->R = new controlTuto("../qtprojetbase/src/environement/controlstuto/keyR", 840, 1070);
    addItem(R);
    this->SHIFT = new controlTuto("../qtprojetbase/src/environement/controlstuto/keySHIFT", 1375, 1000);
    addItem(SHIFT);
    this->E = new controlTuto("../qtprojetbase/src/environement/controlstuto/keyE", 4750, 1050);
    addItem(E);
    this->secondE = new controlTuto("../qtprojetbase/src/environement/controlstuto/keyE", 5170, 1350);
    addItem(secondE);
    this->secondQ = new controlTuto("../qtprojetbase/src/environement/controlstuto/keyQ", 1225, 1000);
    addItem(secondQ);
    this->secondD = new controlTuto("../qtprojetbase/src/environement/controlstuto/keyD", 1275, 1000);
    addItem(secondD);
    this->plus = new controlTuto("../qtprojetbase/src/environement/controlstuto/plus", 1325, 1000);
    addItem(plus);

    QPen pen(Qt::transparent);

    nbcoin = new QGraphicsTextItem();
    nbcoin->setZValue(20);
    nbcoin->setPos(0,0);
    QColor white(255, 255, 255);
    nbcoin->setDefaultTextColor(white);
    QFontDatabase::addApplicationFont("../qtprojetbase/src/font/dogicapixel.ttf");
    QFont customFont("dogica pixel", 12);
    nbcoin->setFont(customFont);
    addItem(nbcoin);

    timerPrPerso = new QGraphicsTextItem();
    timerPrPerso->setZValue(20);
    timerPrPerso->setPos(0,0);
    timerPrPerso->setDefaultTextColor(white);
    timerPrPerso->setFont(customFont);
    addItem(timerPrPerso);

    PseudoText = new QGraphicsTextItem();
    PseudoText->setZValue(20);
    PseudoText->setPos(0,0);
    PseudoText->setDefaultTextColor(white);
    PseudoText->setFont(customFont);

    ScoreText = new QGraphicsTextItem();
    ScoreText->setZValue(20);
    ScoreText->setPos(0,0);
    ScoreText->setDefaultTextColor(white);
    ScoreText->setFont(customFont);

    TempsText = new QGraphicsTextItem();
    TempsText->setZValue(20);
    TempsText->setPos(0,0);
    TempsText->setDefaultTextColor(white);
    TempsText->setFont(customFont);

    Vie= new QGraphicsTextItem();
    Vie->setZValue(20);
    Vie->setPos(0,0);
    Vie->setDefaultTextColor(white);
    Vie->setFont(customFont);

    CoinText = new QGraphicsTextItem();
    CoinText->setZValue(20);
    CoinText->setPos(0,0);
    CoinText->setDefaultTextColor(white);
    CoinText->setFont(customFont);

    PseudoText->setPos(550,1100);
    ScoreText->setPos(550,1150);
    TempsText->setPos(550,1200);
    CoinText->setPos(550,1250);
    Vie->setPos(550,1300);

    addItem(PseudoText);
    addItem(ScoreText);
    addItem(TempsText);
    addItem(CoinText);
    addItem(Vie);

    loopPieceAth = 1;

    temps_slide = 20;
    puissance_slide = 1;
    sens_slide = 1;
    anim_piece_chest = false;

    //playlist pour pouvoir loop à l'infini
    player = new QMediaPlayer;
    playlist = new QMediaPlaylist(player);
    playlist->addMedia(QUrl::fromLocalFile("../qtprojetbase/src/Sound/Music/home2.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player->setPlaylist(playlist);
    player->setVolume(30);

    coinSound = new QMediaPlayer;
    coinSound->setVolume(40);
    SlideSound = new QMediaPlayer;
    SlideSound->setVolume(50);
    HighFall = new QMediaPlayer;
    HighFall->setVolume(20);
    Bow = new QMediaPlayer;
    Bow->setVolume(20);
    Hit = new QMediaPlayer;
    Hit->setVolume(20);
    HitFromSlide = new QMediaPlayer;
    HitFromSlide->setVolume(50);
    is_arcing = false;
    CrystalScene = new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/environement/TransitionLevel/c1"));
    CrystalScene->setZValue(3);
    CrystalScene->setScale(0.75);
    CrystalScene->setPos(100,1100);
    addItem(CrystalScene);
    CrystalSceneSombre = new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/environement/TransitionLevel/cs1"));
    CrystalSceneSombre->setZValue(3.1);
    CrystalSceneSombre->setScale(0.75);
    CrystalSceneSombre->setPos(100,1100);
    addItem(CrystalSceneSombre);
    isInMenu = false;
    is_winning = false;

    coinchest = new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/environement/decor/1.png"));
    coinchest->setZValue(3.6);
    coinchest->setPos(-100,-100);
    addItem(coinchest);

    loop_crystal = 1;
    angle_crystal = 0;
    loop_anim_chest_piece= 0;

    RespawnPoint = QPointF(Personnage->pos().rx(),Personnage->pos().ry());

    RectFinNiv = new QGraphicsRectItem(0,0,100,120);
    RectFinNiv->setPos(0,0);
    RectFinNiv->setZValue(4);
    RectFinNiv->setPen(pen);
    addItem(RectFinNiv);

    transi_Perso_Fin = new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/environement/TransitionLevel/transi1"));
    transi_Perso_Fin->setZValue(5);
    transi_Perso_Fin->setPos(100,1100);
    transi_Perso_Fin->setScale(2);
    addItem(transi_Perso_Fin);

    createMenu();

    Interlvl = new QGraphicsRectItem(0, 0, 1300, 800);
    Interlvl->setOpacity(0);
    Interlvl->setZValue(50);
    Interlvl->setPen(pen);
    Interlvl->setBrush(QColor(0, 0, 0));
    addItem(Interlvl);
    timeInterLevel = 0;
    interlvl2 = false;

    Level = new QGraphicsTextItem();
    Level->setZValue(50);
    Level->setPos(0,0);
    Level->setOpacity(0);
    QFont customFont2("dogica pixel", 40);
    Level->setDefaultTextColor(white);
    Level->setFont(customFont2);
    Level->setPlainText("Level 0");
    addItem(Level);
    loop_Anim_Fin = 1;
    can_anim_fin = false;
    can_hurt_slide = true;
    pausebg = new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/environement/background/whitebg.png"));
    pausebg->setPos(0,700);
    pausebg->setZValue(-2);
    addItem(pausebg);
}
void MyScene::createMenu()
{
    //Create the menu, set some values in case of a new game
    isInMenu = true;
    Menu_Appuie = true;
    isInTuto = false;
    PlayerWin = false;
    reinitvariable();
    can_anim_fin = false;
    tabLevelDone[0] = false;
    tabLevelDone[1] = false;
    tabLevelDone[2] = false;
    tabLevelDone[3] = false;
    this->Personnage->setZValue(4);
    CreateScene("z0fondclair", 1, 0);
    CreateScene("z1fondsombre", 1, 1);
    CreateScene("z2arbres", 1, 2);
    CreateScene("text", 1, 10);
    CreateScene("Accueil", 2, 3,"tiles");
    LoadImage("character1", false);
    AddVectorToScene();
    Sorcerer.push_back(new E_Sorcerer("../qtprojetbase/src/character/ennemy/sorcerer/idle/idle1.png",600,1280,500,100));
    addItem(Sorcerer[0]);
    //addItem(Sorcerer[0]->healthdeco);
    //addItem(Sorcerer[0]->bar);
    QPen pen(Qt::transparent);
    this->rect_Sorcerer.push_back(new QGraphicsRectItem(0, 0, 700, 200)); //600 300
    this->addItem(rect_Sorcerer[0]);
    this->rect_Sorcerer[0]->setPos(-1000,-1000);
    this->rect_Sorcerer[0]->setZValue(15);

    this->rect_Sorcerer_plat.push_back(new QGraphicsRectItem(0, 0, 120, 200)); //600 300
    this->addItem(rect_Sorcerer_plat[0]);
    this->rect_Sorcerer_plat[0]->setPos(-1000,-1000);
    this->rect_Sorcerer_plat[0]->setZValue(15);

    this->rect_Sorcerer_perso.push_back(new QGraphicsRectItem(0, 0, 400, 200)); //600 300
    this->addItem(rect_Sorcerer_perso[0]);
    this->rect_Sorcerer_perso[0]->setPos(-1000,-1000);
    this->rect_Sorcerer_perso[0]->setZValue(15);

    this->rect_Sorcerer[0]->setPen(pen);
    this->rect_Sorcerer_plat[0]->setPen(pen);
    this->rect_Sorcerer_perso[0]->setPen(pen);
    Wolves.push_back(new E_Wolves("../qtprojetbase/src/character/ennemy/WolvesAndCanine/Idle/1_1.png",610,1400,240));
    Wolves[0]->set_Oy(Wolves[0]->get_Oy()-Wolves[0]->boundingRect().height()*Wolves[0]->get_Scale());
    Wolves[0]->setPos(Wolves[0]->get_Ox(), Wolves[0]->get_Oy());
    addItem(Wolves[0]);
    //addItem(Wolves[0]->healthdeco);
    //addItem(Wolves[0]->bar);
    this->rect_Wolves_perso.push_back(new QGraphicsRectItem(0, 0, 700, 200)); //600 300
    this->addItem(rect_Wolves_perso[0]);
    this->rect_Wolves_perso[0]->setPos(-1000,-1000);
    this->rect_Wolves_perso[0]->setZValue(15);
    this->rect_Wolves_perso[0]->setPen(pen);
    CrystalScene->setPos(1150, 1190);
    playlist->removeMedia(0);
    playlist->addMedia(QUrl::fromLocalFile("../qtprojetbase/src/Sound/Music/home2.wav"));
    player->setVolume(5);
    player->play();
    this->Personnage->setPos(100,1.3*bguntier);
    menu = new QDialog();
    menu->setWindowFlags(Qt::FramelessWindowHint);
    menu->setAttribute(Qt::WA_TranslucentBackground);
    menu->setModal(true);
    QVBoxLayout* mainLayout;
    mainLayout = new QVBoxLayout();
    QLabel* labelscore = new QLabel();
    QPushButton* jouer = new QPushButton("Jouer");
    QPushButton* score = new QPushButton("Scoreboard");
    QPushButton* quitter = new QPushButton("Quitter");
    linePseudo = new QLineEdit();
    linePseudo->setText("Guest");
    QRegExp regex("^[a-zA-Z0-9 ]*$");
    linePseudo->setValidator(new QRegExpValidator(regex, this));
    linePseudo->setMaxLength(18);
    mainLayout->addWidget(linePseudo);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(jouer);
    buttonLayout->addWidget(score);
    buttonLayout->addWidget(quitter);
    mainLayout->addWidget(labelscore);
    mainLayout->addLayout(buttonLayout);
    menu->setLayout(mainLayout);
    menu->show();
    piece = 0;
    life = 25;
    for (int i =0; i<5; i++){
        Heart[i]->setPixmap(QString("../qtprojetbase/src/character/Heart/heart5.png"));
    }
    connect(quitter, SIGNAL(clicked(bool)), this, SLOT(quit()));
    connect(score, SIGNAL(clicked(bool)), this, SLOT(Score()));
    connect(jouer, SIGNAL(clicked(bool)), this, SLOT(jouer()));
}

void MyScene::GameIsPaused(){
    //When "t" is pressed, show a dialog to continue or go to the menu
    pausebg->setZValue(25);
    dialpause = new QDialog();
    dialpause->setWindowFlags(Qt::FramelessWindowHint);
    dialpause->setAttribute(Qt::WA_TranslucentBackground);
    dialpause->setModal(true);
    QVBoxLayout* mainLayout;
    mainLayout = new QVBoxLayout();
    QLabel* labelscore = new QLabel();
    QPushButton* reprendre = new QPushButton("Reprendre");
    QPushButton* menuu = new QPushButton("Menu");
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(reprendre);
    buttonLayout->addWidget(menuu);
    mainLayout->addWidget(labelscore);
    mainLayout->addLayout(buttonLayout);
    dialpause->setLayout(mainLayout);
    dialpause->show();
    connect(reprendre, SIGNAL(clicked(bool)), this, SLOT(Reprendre()));
    connect(menuu, SIGNAL(clicked(bool)), this, SLOT(MenuPaused()));
}
void MyScene::MenuPaused(){
    //Connector function to quit the dialog and do the action
    pausebg->setZValue(-2);
    pauseGame = false;
    timer->start(15);
    createMenu();
    dialpause->accept();
    timePerso = 0;
}
void MyScene::Reprendre(){
    //Connector function to quit the dialog and do the action
    pausebg->setZValue(-2);
    timer->start(15);
    pauseGame = false;
    dialpause->accept();
}

void MyScene::quit()
{
    //Connector function to quit the dialog and do the action
    QCoreApplication::quit();
}
void MyScene::jouer()
{
    //Connector function to quit the dialog and do the action
    timePerso = 0;
    Pseudo = linePseudo->text();
    createlvltuto();
    menu->accept();
}
void MyScene::Menu()
{
    //Connector function to quit the dialog and do the action
    createMenu();
    win->accept();
    timePerso = 0;
}
void MyScene::Score()
{
    //Connector function to quit the dialog and do the action
    createScoreboard();
    menu->accept();
    timePerso = 0;
}
void MyScene::MenuScbrd(){
    //Connector function to quit the dialog and do the action
    createMenu();
    scbord->accept();
    timePerso = 0;
}

void MyScene::createScoreboard(){
    //Create the score board, sort all the score and show the best on the screen
    reinitvariable();
    playlist->removeMedia(0);
    player->setVolume(5);
    playlist->addMedia(QUrl::fromLocalFile("../qtprojetbase/src/Sound/Music/EndScoreMusic.wav"));
    player->play();
    CreateScene("ScoreBoardBackTxt", 1, 5);
    timePerso = 0;
    CreateScene("WinBack", 2, 0,"tiles3", "decorlvl3");
    CreateScene("ScoreBoard", 2, 6,"tiles3", "decorlvl3");
    LoadImage("character1", false);
    AddVectorToScene();

    ////// réflexion de ma part, code de chat gpt
    std::string ligne;
    std::fstream fichier("../qtprojetbase/src/score.txt", std::ios::in | std::ios::out | std::ios::app);
        // Vérification que l'ouverture s'est bien passée
    if (!fichier)
    {
        qDebug() << "Erreur : impossible d'ouvrir le fichier en mode lecture et écriture.";
    }
    QVector<QString> lines;
    QVector<int> scores;
    QVector<QString> finallines;
    while (std::getline(fichier, ligne))
    {
        std::stringstream ss(ligne);
        lines.push_back(QString::fromStdString(ligne));
    }
    for (int i=0; i < lines.size(); i++){
        QStringList list = lines[i].split(";");
        qDebug()<<list;
        QString score = list[1];
        scores.push_back(score.toInt());
    }
    std::sort(scores.begin(), scores.end(), std::greater<int>());

    int mini = min(7, scores.size());
    for (int j = 0;j<mini; j++){
        QString myString = QString::number(scores[j]);
        for (int i = 0; i < lines.size(); i ++){
            if (lines[i].contains(myString)) {
                finallines.push_back(lines[i]);
            }
        }
    }
    /*Afficher dans la scene*/
    int y = 1050;
    QPen pen(Qt::transparent);
    QColor white(255, 255, 255);
    QFontDatabase::addApplicationFont("../qtprojetbase/src/font/dogicapixel.ttf");
    QFont customFont("dogica pixel", 12);
    ScoreboardLine.push_back(new QGraphicsTextItem());
    ScoreboardLine.last()->setPlainText("Classement | Pseudo | Score | Temps | Pieces | Vie");
    ScoreboardLine.last()->setPos(350, 1000);
    ScoreboardLine.last()->setZValue(20);
    ScoreboardLine.last()->setDefaultTextColor(white);
    ScoreboardLine.last()->setFont(customFont);
    addItem(ScoreboardLine.last());
    Rectscore.push_back(new QGraphicsRectItem(350, 1035, 600, 3));
    Rectscore.last()->setZValue(20);
    Rectscore.last()->setPen(pen);
    Rectscore.last()->setBrush(QBrush(Qt::white));
    addItem(Rectscore.last());
    mini = min(7, finallines.size());
    for (int i = 0; i<mini; i++){
        ScoreboardLine.push_back(new QGraphicsTextItem());
        QStringList list = finallines[i].split(";");
        ScoreboardLine.last()->setPlainText(QString::number(i+1) + "    " + list[0] + "\t"+ list[1] + "\t"+ list[2] + ":"+ list[3] + "\t"+ list[4] + "\t"+ QString::number(std::stoi(list[5].toStdString())/10.0));
        ScoreboardLine.last()->setPos(350, y+50*i);
        ScoreboardLine.last()->setZValue(20);
        ScoreboardLine.last()->setDefaultTextColor(white);
        ScoreboardLine.last()->setFont(customFont);
        addItem(ScoreboardLine.last());
        Rectscore.push_back(new QGraphicsRectItem(350, y+50*i + 30, 600, 3));
        Rectscore.last()->setZValue(20);
        Rectscore.last()->setPen(pen);
        Rectscore.last()->setBrush(QBrush(Qt::white));
        addItem(Rectscore.last());
    }
    ////////////////////////////////////////////////////////////////

    CrystalScene->setPos(5100, 1320);
    RectFinNiv->setPos(CrystalScene->pos().rx()+CrystalScene->boundingRect().width()/2-RectFinNiv->boundingRect().width()/2, CrystalScene->pos().ry());
    this->Personnage->setPos(640,1.5*bguntier);
    scbord = new QDialog();
    scbord->setWindowFlags(Qt::FramelessWindowHint);
    scbord->setAttribute(Qt::WA_TranslucentBackground);
    scbord->setModal(true);
    QVBoxLayout* mainLayout;
    mainLayout = new QVBoxLayout();
    QLabel* labelscore = new QLabel();
    QPushButton* menu = new QPushButton("Menu");
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(menu);
    mainLayout->addWidget(labelscore);
    mainLayout->addLayout(buttonLayout);
    scbord->setLayout(mainLayout);
    scbord->move(1980/2 - 80, 1080/2 + 200);
    scbord->show();
    connect(menu, SIGNAL(clicked(bool)), this, SLOT(MenuScbrd()));
}

void MyScene::createWin(){
    //Create a scene after the player win/death
    reinitvariable();
    isInTuto = false;
    playlist->removeMedia(0);
    player->setVolume(5);
    playlist->addMedia(QUrl::fromLocalFile("../qtprojetbase/src/Sound/Music/EndScoreMusic.wav"));
    player->play();
    if (PlayerWin){
        CreateScene("Winbacktext", 1, 5);
        //ecrire dans fichier
    }
    else {
        CreateScene("Loosebacktext", 1, 5);
    }
    int score = 0;
    score += (timePerso/6000 < 2) ? 600 : (timePerso/6000 < 3) ? 500 : (timePerso/6000 < 4) ? 400 : (timePerso/6000 < 5) ? 300 : 100;
    score += round(piece * 3.5);
    score += (life/5.0) * 75;
    PseudoText->setPlainText("Pseudo : " + Pseudo);
    ScoreText->setPlainText("Score : " + QString::number(score));
    QString minutes(QString::number(timePerso/6000));
    QString secondes(QString::number((timePerso%6000)/100));
    if (timePerso/6000 < 10){
        minutes = "0" + QString::number(timePerso/6000);
    }
    if ((timePerso%6000)/100<10) {
        secondes = "0" + QString::number((timePerso%6000)/100);
    }
    TempsText->setPlainText("Temps : " + minutes+ ":" +secondes);
    CoinText->setPlainText("Coin : " + QString::number(piece));
    if (life>25){
        life = 25;
    }
    Vie->setPlainText("Coeurs : "+QString::number(life/5.0));
    if (PlayerWin){
        std::fstream fichier("../qtprojetbase/src/score.txt", std::ios::in | std::ios::out | std::ios::app);
        if (!fichier){
            qDebug() << "Erreur : impossible d'ouvrir le fichier en mode lecture et écriture.";
        }
        std::string ligne;
        std::string contenu;
        int addscore = std::round((life/5.0)*10);
        int loop = 18-Pseudo.size();
        for (int i = 0 ; i <loop; i++){
            Pseudo +=". ";
        }
        contenu += Pseudo.toStdString()+";"+std::to_string(score)+";"+minutes.toStdString()+";"+secondes.toStdString()+";"+std::to_string(piece)+";"+std::to_string(addscore)+"\n";
        fichier<<contenu;
        fichier.close();
        PlayerWin = false;
    }

    PseudoText->setZValue(20);
    ScoreText->setZValue(20);
    TempsText->setZValue(20);
    CoinText->setZValue(20);
    Vie->setZValue(20);

    life = 25;
    for (int i =0; i<5; i++){
        Heart[i]->setPixmap(QString("../qtprojetbase/src/character/Heart/heart5.png"));
    }
    timePerso = 0;
    CreateScene("WinBack", 2, 0,"tiles3", "decorlvl3");
    CreateScene("Win", 2, 6,"tiles3", "decorlvl3");
    //CreateScene("z3arbresfront", 1, 5);
    LoadImage("character1", false);
    AddVectorToScene();
    CrystalScene->setPos(5100, 1320);
    RectFinNiv->setPos(CrystalScene->pos().rx()+CrystalScene->boundingRect().width()/2-RectFinNiv->boundingRect().width()/2, CrystalScene->pos().ry());
    this->Personnage->setPos(640,1.5*bguntier);
    win = new QDialog();
    win->setWindowFlags(Qt::FramelessWindowHint);
    win->setAttribute(Qt::WA_TranslucentBackground);
    win->setModal(true);
    QVBoxLayout* mainLayout;
    mainLayout = new QVBoxLayout();
    QLabel* labelscore = new QLabel();
    QPushButton* menu = new QPushButton("Menu");
    QPushButton* quitter = new QPushButton("Quitter");
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(menu);
    buttonLayout->addWidget(quitter);
    mainLayout->addWidget(labelscore);
    mainLayout->addLayout(buttonLayout);
    win->setLayout(mainLayout);
    win->move(1980/2 - 122, 1080/2 + 170);
    win->show();
    is_winning = false;
    connect(quitter, SIGNAL(clicked(bool)), this, SLOT(quit()));
    connect(menu, SIGNAL(clicked(bool)), this, SLOT(Menu()));
}

void MyScene::createlvltuto(){
    //Create the tuto level with the controls
    isInMenu = false;
    reinitvariable();
    isInTuto = true;
    tabLevelDone[0] = true;
    current_lvl = 0;
    playlist->removeMedia(0);
    player->setVolume(5);
    playlist->addMedia(QUrl::fromLocalFile("../qtprojetbase/src/Sound/Music/mainmusic.wav"));
    player->play();
    CreateScene("z0fondclair", 1, 0);
    CreateScene("z1fondsombre", 1, 1);
    CreateScene("z2arbres", 1, 2);
    CreateScene("lvltuto", 2, 3,"tiles");
    //CreateScene("z3arbresfront", 1, 5);
    LoadImage("character1", false);
    AddVectorToScene();
    Q->setZValue(20);
    D->setZValue(20);
    SPACE->setZValue(20);
    R->setZValue(20);
    SHIFT->setZValue(20);
    E->setZValue(20);
    secondE->setZValue(20);
    secondQ->setZValue(20);
    secondD->setZValue(20);
    plus->setZValue(20);
    CrystalScene->setPos(5100, 1340);
    RectFinNiv->setPos(CrystalScene->pos().rx()+CrystalScene->boundingRect().width()/2-RectFinNiv->boundingRect().width()/2, CrystalScene->pos().ry());
    this->Personnage->setPos(100,1.3*bguntier);
    interlvl2 = true;
}
void MyScene::createlvl1(){
    //Create the first level
    tabLevelDone[1] = true;
    reinitvariable();
    removecontrolsTuto();
    CreateScene("z0fondclair", 1, 0);
    CreateScene("z1fondsombre", 1, 1);
    CreateScene("z2arbres", 1, 2);
    CreateScene("lvl1", 2, 3,"tiles");
    CreateScene("z3arbresfront", 1, 5);
    LoadImage("character1", false);
    AddVectorToScene();
    CreateEnnemy();
    CrystalScene->setPos(5100, 1260);
    RectFinNiv->setPos(CrystalScene->pos().rx()+CrystalScene->boundingRect().width()/2-RectFinNiv->boundingRect().width()/2, CrystalScene->pos().ry());
    this->Personnage->setPos(100,1.3*bguntier);
    interlvl2 = true;
}
void MyScene::createlvl2(){
    //Create the second level
    tabLevelDone[2] = true;
    reinitvariable();
    CreateScene("z0back", 1, 0);
    CreateScene("lvl2", 2, 3,"tiles2");
    LoadImage("character1", false);
    AddVectorToScene();
    //CreateEnnemylvl2_1();
    playlist->removeMedia(0);
    playlist->addMedia(QUrl::fromLocalFile("../qtprojetbase/src/Sound/Music/boss.wav"));
    player->play();
    CrystalScene->setPos(5100, 1100);
    RectFinNiv->setPos(CrystalScene->pos().rx()+CrystalScene->boundingRect().width()/2-RectFinNiv->boundingRect().width()/2, CrystalScene->pos().ry());
    this->Personnage->setPos(100,1.3*bguntier);
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),33, 29, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),33, 28, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),33, 27, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),33, 26, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile4.png"),33, 25, 4, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),34, 29, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),34, 28, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),34, 27, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),34, 26, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile5.png"),34, 25, 5, 2, 15));
    addItem(plateformes.last());
    CreateEnnemylvl2_1();
    //ligne29 colonne 35 80 122    132
    interlvl2 = true;
}
void MyScene::createlvl3(){
    //Create the third level
    reinitvariable();
    tabLevelDone[3] = true;
    CreateScene("lvl3back", 1, 0);
    CreateScene("lvl3", 2, 3,"tiles3", "decorlvl3");
    LoadImage("character1", true);
    AddVectorToScene();
    playlist->removeMedia(0);
    playlist->addMedia(QUrl::fromLocalFile("../qtprojetbase/src/Sound/Music/lvl3.wav"));
    player->play();
    CrystalScene->setPos(5130, 1100);
    RectFinNiv->setPos(CrystalScene->pos().rx()+CrystalScene->boundingRect().width()/2-RectFinNiv->boundingRect().width()/2, CrystalScene->pos().ry());
    this->Personnage->setPos(100,1.3*bguntier);
    QPixmap pix(QString("../qtprojetbase/src/character/character1/Idle/idle1.png"));
    QPixmap scaledPixmap = pix.scaled(pix.width() * 2, pix.height() * 2);
    scaledPixmap = ToBlack(scaledPixmap);
    Personnage->setPixmap(scaledPixmap);
    for (int i; i < plateformes.size(); i++){
        plateformes[i]->setOpacity(0);
    }
    QPen pen(Qt::transparent);
    opacTile.push_back(new QGraphicsEllipseItem(0, 0, 110, 350));
    opacTile.push_back(new QGraphicsEllipseItem(0, 0, 200, 370));
    opacTile.push_back(new QGraphicsEllipseItem(0, 0, 340, 390));
    opacTile.push_back(new QGraphicsEllipseItem(0, 0, 450, 410));
    opacTile.push_back(new QGraphicsEllipseItem(0, 0, 580, 430));
    opacTile.push_back(new QGraphicsEllipseItem(0, 0, 700, 450));
    opacTile.push_back(new QGraphicsEllipseItem(0, 0, 800, 470));
    opacTile.push_back(new QGraphicsEllipseItem(0, 0, 860, 490));
    opacTile.push_back(new QGraphicsEllipseItem(0, 0, 920, 500));
    opacTile.push_back(new QGraphicsEllipseItem(0, 0, 960, 500));
    for (int i = 0; i<opacTile.size(); i++){
        opacTile[i]->setPen(pen);
        addItem(opacTile[i]);
    }
    for (int i = 0 ; i<plateformes.size(); i ++){
        if (plateformes[i]->get_tile_code()==50){
            QPixmap pix (QString("../qtprojetbase/src/environement/decor/1.png"));
            pix = ToBlack(pix);
            plateformes[i]->setPixmap(pix);
        }
    }
    interlvl2 = true;
}

void MyScene::InterLevel(){
    //Do the animation on the screen with the current level and call the right function to create the level
    if (tabLevelDone[1] == false){
        current_lvl = 1;
    }
    else if (tabLevelDone[2] == false){
        current_lvl = 2;
    }
    else if (tabLevelDone[3] == false){
        current_lvl = 3;
    }
    Level->setPlainText("Level " + QString::number(current_lvl));
    if (timeInterLevel>250){
        QPixmap pix(QString("../qtprojetbase/src/character/character1/Idle/idle1.png"));
        QPixmap scaledPixmap = pix.scaled(pix.width() * 2, pix.height() * 2);
        Personnage->setPixmap(scaledPixmap);
        Personnage->setPos(100,1.3*bguntier);
        Personnage->setZValue(4);
        transi_Perso_Fin->setPos(-200,-200);
        Compagnion->setPos(80,1.25*bguntier);
        transi_Perso_Fin->setZValue(5);
        elementcentered->setPos(Personnage->pos().rx()+v_X+(width_Perso/2), this->Ybgmid);
        //Récupération de la vue
        QGraphicsView* viewPerso = this->views()[0];
        //Update de la vue sur le point central
        viewPerso->centerOn(elementcentered);
        QPointF posFond = QPointF(0,elementcentered->pos().ry()-Interlvl->boundingRect().height()/2);
        Level->setPos(-23 +posFond.rx()+Interlvl->boundingRect().width()/2-Level->boundingRect().width()/2, posFond.ry()+Interlvl->boundingRect().height()/2 - Level->boundingRect().height()/2);
        Interlvl->setPos(posFond);
        if (tabLevelDone[1] == false){
            createlvl1();
        }
        else if (tabLevelDone[2] == false){
            createlvl2();
        }
        else if (tabLevelDone[3] == false){
            createlvl3();
        }
        /*if (current_lvl == 1){
            createlvl1();
        }
        else if (current_lvl == 2){
            createlvl2();
        }
        else if (current_lvl == 3){
            createlvl3();
        }*/
        changelevel = true;
        interlvl2 = true;
    }
    else{
        if (timeInterLevel<101){
            Interlvl->setOpacity((float)timeInterLevel/100);
            Level->setOpacity((float)timeInterLevel/100);
        }
        timeInterLevel++;
    }
}

void MyScene::CreateEnnemy(){
    //Create an ennmy for the first level
    Sorcerer.push_back(new E_Sorcerer("../qtprojetbase/src/character/ennemy/sorcerer/idle/idle1.png",3160,2130,250,100));
    addItem(Sorcerer[0]);
    addItem(Sorcerer[0]->healthdeco);
    addItem(Sorcerer[0]->bar);
    QPen pen(Qt::transparent);
    this->rect_Sorcerer.push_back(new QGraphicsRectItem(0, 0, 700, 200)); //600 300
    this->addItem(rect_Sorcerer[0]);
    this->rect_Sorcerer[0]->setPos(-1000,-1000);
    this->rect_Sorcerer[0]->setZValue(15);

    this->rect_Sorcerer_plat.push_back(new QGraphicsRectItem(0, 0, 120, 200)); //600 300
    this->addItem(rect_Sorcerer_plat[0]);
    this->rect_Sorcerer_plat[0]->setPos(-1000,-1000);
    this->rect_Sorcerer_plat[0]->setZValue(15);

    this->rect_Sorcerer_perso.push_back(new QGraphicsRectItem(0, 0, 400, 200)); //600 300
    this->addItem(rect_Sorcerer_perso[0]);
    this->rect_Sorcerer_perso[0]->setPos(-1000,-1000);
    this->rect_Sorcerer_perso[0]->setZValue(15);

    this->rect_Sorcerer[0]->setPen(pen);
    this->rect_Sorcerer_plat[0]->setPen(pen);
    this->rect_Sorcerer_perso[0]->setPen(pen);
}

void MyScene::CreateEnnemylvl2_1(){
    //Create the first ennemy wave on level 2
    QPen pen(Qt::transparent);
    for (int i = 0; i <6; i ++){
        Sorcerer.push_back(new E_Sorcerer("../qtprojetbase/src/character/ennemy/sorcerer/idle/idle1.png",(rand()%500)+350,1100,350,100)); //350 to max 1200 (lim 1300)
        addItem(Sorcerer[i]);
        addItem(Sorcerer[i]->healthdeco);
        addItem(Sorcerer[i]->bar);

        this->rect_Sorcerer.push_back(new QGraphicsRectItem(0, 0, 700, 200)); //600 300
        this->addItem(rect_Sorcerer[i]);
        this->rect_Sorcerer[i]->setPos(-1000,-1000);
        this->rect_Sorcerer[i]->setZValue(15);

        this->rect_Sorcerer_plat.push_back(new QGraphicsRectItem(0, 0, 120, 200)); //600 300
        this->addItem(rect_Sorcerer_plat[i]);
        this->rect_Sorcerer_plat[i]->setPos(-1000,-1000);
        this->rect_Sorcerer_plat[i]->setZValue(15);

        this->rect_Sorcerer_perso.push_back(new QGraphicsRectItem(0, 0, 400, 200)); //600 300
        this->addItem(rect_Sorcerer_perso[i]);
        this->rect_Sorcerer_perso[i]->setPos(-1000,-1000);
        this->rect_Sorcerer_perso[i]->setZValue(15);

        this->rect_Sorcerer[i]->setPen(pen);
        this->rect_Sorcerer_plat[i]->setPen(pen);
        this->rect_Sorcerer_perso[i]->setPen(pen);
    }
    vague_in_lvl_2 = 1;
}
void MyScene::CreateEnnemylvl2_2(){
    //Create the second ennemy wave on level 2
    for (auto elem : rect_Sorcerer){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : rect_Sorcerer_plat){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : rect_Sorcerer_perso){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : Sorcerer) {
        removeItem(elem);
        delete elem;
    }
    Sorcerer.clear();
    Sorcerer = QVector<E_Sorcerer*>();
    rect_Sorcerer.clear();
    rect_Sorcerer_plat.clear();
    rect_Sorcerer_perso.clear();
    rect_Sorcerer = QVector<QGraphicsRectItem*>();
    rect_Sorcerer_plat = QVector<QGraphicsRectItem*>();
    rect_Sorcerer_perso = QVector<QGraphicsRectItem*>();
    //enlever block arene
    for (int i = 0; i<10; i++){
        removeItem(plateformes.last());
        plateformes.removeLast();
    }
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),66, 29, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),66, 28, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),66, 27, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),66, 26, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile4.png"),66, 25, 4, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),67, 29, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),67, 28, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),67, 27, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),67, 26, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile5.png"),67, 25, 5, 2, 15));
    addItem(plateformes.last());
    //Wolves
    QPen pen(Qt::transparent);
    for (int i = 0; i <6; i ++){
        // mettre du rand dans les pos de départ et les maxR, faire delimitation "arene" pour pas perso aille trop loin
        Wolves.push_back(new E_Wolves("../qtprojetbase/src/character/ennemy/WolvesAndCanine/Idle/1_1.png",(rand()%500) + 1450,1200,600)); //1450 to max 2550 (lim 2610)
        Wolves[i]->set_Oy(Wolves[i]->get_Oy()-Wolves[i]->boundingRect().height()*Wolves[i]->get_Scale());
        Wolves[i]->setPos(Wolves[i]->get_Ox(), Wolves[i]->get_Oy());
        addItem(Wolves[i]);
        addItem(Wolves[i]->healthdeco);
        addItem(Wolves[i]->bar);

        this->rect_Wolves_perso.push_back(new QGraphicsRectItem(0, 0, 700, 200)); //600 300
        this->addItem(rect_Wolves_perso[i]);
        this->rect_Wolves_perso[i]->setPos(-1000,-1000);
        this->rect_Wolves_perso[i]->setZValue(15);
        this->rect_Wolves_perso[i]->setPen(pen);
    }
    vague_in_lvl_2 = 2;
}
void MyScene::CreateEnnemylvl2_3(){
    //Create the third ennemy wave on level 2
    for (auto elem : rect_Wolves_perso){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : Wolves) {
        removeItem(elem);
        delete elem;
    }
    Wolves.clear();
    Wolves = QVector<E_Wolves*>();
    rect_Wolves_perso.clear();
    rect_Wolves_perso = QVector<QGraphicsRectItem*>();
    //enlever block arene
    for (int i = 0; i<10; i++){
        removeItem(plateformes.last());
        plateformes.removeLast();
    }
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),99, 29, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),99, 28, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),99, 27, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),99, 26, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile4.png"),99, 25, 4, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),100, 29, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),100, 28, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),100, 27, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),100, 26, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile5.png"),100, 25, 5, 2, 15));
    addItem(plateformes.last());
    //Sorcerer and Wolves
    QPen pen(Qt::transparent);
    for (int i = 0; i <2; i ++){
        Sorcerer.push_back(new E_Sorcerer("../qtprojetbase/src/character/ennemy/sorcerer/idle/idle1.png",(rand()%450) + 2800,1100,500,100));//2800 to max 3750 (lim 3900)
        addItem(Sorcerer[i]);
        addItem(Sorcerer[i]->healthdeco);
        addItem(Sorcerer[i]->bar);

        this->rect_Sorcerer.push_back(new QGraphicsRectItem(0, 0, 700, 200)); //600 300
        this->addItem(rect_Sorcerer[i]);
        this->rect_Sorcerer[i]->setPos(-1000,-1000);
        this->rect_Sorcerer[i]->setZValue(15);

        this->rect_Sorcerer_plat.push_back(new QGraphicsRectItem(0, 0, 120, 200)); //600 300
        this->addItem(rect_Sorcerer_plat[i]);
        this->rect_Sorcerer_plat[i]->setPos(-1000,-1000);
        this->rect_Sorcerer_plat[i]->setZValue(15);

        this->rect_Sorcerer_perso.push_back(new QGraphicsRectItem(0, 0, 400, 200)); //600 300
        this->addItem(rect_Sorcerer_perso[i]);
        this->rect_Sorcerer_perso[i]->setPos(-1000,-1000);
        this->rect_Sorcerer_perso[i]->setZValue(15);

        this->rect_Sorcerer[i]->setPen(pen);
        this->rect_Sorcerer_plat[i]->setPen(pen);
        this->rect_Sorcerer_perso[i]->setPen(pen);
    }
    for (int i = 0; i <4; i ++){
        // mettre du rand dans les pos de départ et les maxR, faire delimitation "arene" pour pas perso aille trop loin
        Wolves.push_back(new E_Wolves("../qtprojetbase/src/character/ennemy/WolvesAndCanine/Idle/1_1.png",(rand()%450) + 2800,1200,500));//2800 to max 3750 (lim 3900)
        Wolves[i]->set_Oy(Wolves[i]->get_Oy()-Wolves[i]->boundingRect().height()*Wolves[i]->get_Scale());
        Wolves[i]->setPos(Wolves[i]->get_Ox(), Wolves[i]->get_Oy());
        addItem(Wolves[i]);
        addItem(Wolves[i]->healthdeco);
        addItem(Wolves[i]->bar);

        this->rect_Wolves_perso.push_back(new QGraphicsRectItem(0, 0, 700, 200)); //600 300
        this->addItem(rect_Wolves_perso[i]);
        this->rect_Wolves_perso[i]->setPos(-1000,-1000);
        this->rect_Wolves_perso[i]->setZValue(15);
        this->rect_Wolves_perso[i]->setPen(pen);
    }

    vague_in_lvl_2 = 3;
}
void MyScene::CreateEnnemylvl2_end(){
    //Create the last ennemy wave on level 2 (NightBorne)
    for (auto elem : rect_Sorcerer){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : rect_Sorcerer_plat){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : rect_Sorcerer_perso){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : Sorcerer) {
        removeItem(elem);
        delete elem;
    }
    Sorcerer.clear();
    Sorcerer = QVector<E_Sorcerer*>();
    rect_Sorcerer.clear();
    rect_Sorcerer_plat.clear();
    rect_Sorcerer_perso.clear();
    rect_Sorcerer = QVector<QGraphicsRectItem*>();
    rect_Sorcerer_plat = QVector<QGraphicsRectItem*>();
    rect_Sorcerer_perso = QVector<QGraphicsRectItem*>();
    for (auto elem : rect_Wolves_perso){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : Wolves) {
        removeItem(elem);
        delete elem;
    }
    Wolves.clear();
    Wolves = QVector<E_Wolves*>();
    rect_Wolves_perso.clear();
    rect_Wolves_perso = QVector<QGraphicsRectItem*>();
    //enlever block arene
    //enlever block arene
    for (int i = 0; i<10; i++){
        removeItem(plateformes.last());
        plateformes.removeLast();
    }
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),120, 29, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),120, 28, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),120, 27, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile8.png"),120, 26, 8, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile4.png"),120, 25, 4, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),121, 29, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),121, 28, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),121, 27, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile9.png"),121, 26, 9, 2, 15));
    addItem(plateformes.last());
    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/tiles2/tile5.png"),121, 25, 5, 2, 15));
    addItem(plateformes.last());
    //Boss
    NightBorne.push_back(new E_Nightborne("../qtprojetbase/src/character/ennemy/Nightborne/idle/idle1.png",4000,1283,1000));
    NightBorne[0]->set_Oy(NightBorne[0]->get_Oy()-NightBorne[0]->boundingRect().height()*NightBorne[0]->get_Scale());
    NightBorne[0]->setPos(NightBorne[0]->get_Ox(), NightBorne[0]->get_Oy());
    addItem(NightBorne[0]);
    addItem(NightBorne[0]->healthdeco);
    addItem(NightBorne[0]->bar);

    this->rect_NightBorne_perso.push_back(new QGraphicsRectItem(0, 0, 800, 200)); //600 300
    this->addItem(rect_NightBorne_perso[0]);
    this->rect_NightBorne_perso[0]->setPos(-1000,-1000);
    this->rect_NightBorne_perso[0]->setZValue(15);

    this->rect_NightBorne_atk.push_back(new QGraphicsRectItem(0, 0, 200, 200)); //600 300
    this->addItem(rect_NightBorne_atk[0]);
    this->rect_NightBorne_atk[0]->setPos(-1000,-1000);
    this->rect_NightBorne_atk[0]->setZValue(15);
    QPen pen(Qt::transparent);
    this->rect_NightBorne_atk[0]->setPen(pen);
    this->rect_NightBorne_perso[0]->setPen(pen);
    vague_in_lvl_2 = 4;
}

void MyScene::reinitvariable(){
    //After creating a new level or scene, clear all the variables and/or set them to their start value
    isInTuto = false;
    this->elapsedMs = 0;
    this->shaking = false;
    this->rect_chest = new QGraphicsRectItem(0, 0, 100, 100); //600 300
    this->addItem(rect_chest);
    this->rect_chest->setPos(0,0);
    QPen pen(Qt::transparent);
    this->rect_chest->setPen(pen);
    this->intindiceplat[0] = 0;
    this->intindiceplat[1] = 0;
    this->v_X = 0;
    this->v_Y = 0;
    this->angle = 0;
    this->gap_X = 0;
    this->gap_Y = 0;
    this->vitessedroite = 4;
    this->vitessegauche = 4;
    this->loop = 1;
    this->loop_Coin = 1;
    this->saut = false;
    //Init des bool de check
    this->is_staying = false;
    this->is_running = false;
    this->is_backing = false;
    this->is_jumping = false;
    this->is_falling = true;
    this->is_colisionning_left = false;
    this->is_colisionning_right = false;
    this->is_colisionning_top = false;
    this->is_colisionning_bottom = false;
    this->espace_Pressed = false;
    this->timeout_espace = false;
    can_open_chest = false;
    index_chest_anim = 0;
    loop_anim_chest = 1;
    opacite_Bg = 0;
    anglecompagnion = 0;
    changementangle = 0;
    procheperso = true;
    pose = false;
    vitCompagnonX = 1;
    vitCompagnonY = 1;
    compagnon_back = false;
    compagnon_run = true;
    boucle_picorer = 1;
    picorer = 1;
    anim_compagnon = 1;
    hurt_fall = false;
    //qDebug()<<plateformeMovetoAnim;
    posPlatMove = 0;
    sensPlatMove = -1;
    moduloUpdate = 0;
    can_anim_particle = false;
    loop_anim_particle = 15;
    can_anim_fall = false;
    loop_anim_fall = 15;
    this->justesortierect = 0;
    anim_piece_chest = false;
    QPointF** tabElementcentered = new QPointF*[3];
    for (int i = 0; i < 3; i++){
        tabElementcentered[i] = new QPointF(0.0,0.0);
    }
    QPointF** tabComp = new QPointF*[50];
    for (int i = 0; i < 50; i++){
        tabComp[i] = new QPointF(0.0,0.0);
    }
    this->e_press_for_chest = false;
    boolForPlatMoveAndPerso[0] = {false, 0};
    boolForPlatMoveAndPerso[1] = {false, 0};

    for (auto elem : plateformes) {
        removeItem(elem);
        delete elem;
    }
    for (auto elem : jumpEffect) {
        removeItem(elem);
        delete elem;
    }
    for (auto elem : Background) {
        removeItem(elem);
        delete elem;
    }
    for (auto elem : Sorcerer) {
        removeItem(elem);
        delete elem;
    }
    for (auto elem : Wolves) {
        removeItem(elem);
        delete elem;
    }
    for (auto elem : fleche) {
        removeItem(elem.first);
    }
    for (auto elem : bullet) {
        removeItem(elem.first);
    }
    for (auto elem : opacTile) {
        removeItem(elem);
        delete elem;
    }
    for (auto elem : CheckP){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : rect_Wolves_perso){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : rect_NightBorne_perso){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : Rectscore){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : ScoreboardLine){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : rect_Sorcerer){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : rect_Sorcerer_plat){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : rect_Sorcerer_perso){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : rect_NightBorne_atk){
        removeItem(elem);
        delete elem;
    }
    for (auto elem : NightBorne){
        removeItem(elem);
        delete elem;
    }
    /*foreach (QGraphicsItem *item, items()) {
        QGraphicsEffect *effect = item->graphicsEffect();
        if (effect && effect->metaObject()->className() == QString("QGraphicsDropShadowEffect")) {
            item->setGraphicsEffect(nullptr);
            delete effect;
        }
    }*/

    ImagesRunPerso.clear();
    ImagesBackPerso.clear();
    ImagesJumpRightPerso.clear();
    ImagesJumpLeftPerso.clear();
    ImagesIdlePerso.clear();
    ImagesHurtPerso.clear();
    ImagesSlidePerso.clear();
    ImagesArcPerso.clear();
    plateformes.clear();
    shadow.clear();
    jumpEffect.clear();
    Background.clear();
    plateformeFalltoAnim.clear();
    plateformeMoveBouncetoAnim.clear();
    plateformeMovetoAnim.clear();
    gravitefleche.clear();
    rotationfleche.clear();
    PosArbreBack.clear();
    Sorcerer.clear();
    Wolves.clear();
    bullet.clear();
    fleche.clear();
    crystal.clear();
    crystals.clear();
    opacTile.clear();
    CheckP.clear();
    rect_Wolves_perso.clear();
    NightBorne.clear();
    rect_NightBorne_perso.clear();
    Rectscore.clear();
    ScoreboardLine.clear();
    rect_NightBorne_atk.clear();
    rect_Sorcerer.clear();
    rect_Sorcerer_plat.clear();
    rect_Sorcerer_perso.clear();

    ImagesRunPerso = QVector<QPixmap>();
    ImagesBackPerso = QVector<QPixmap>();
    ImagesJumpRightPerso = QVector<QPixmap>();
    ImagesJumpLeftPerso = QVector<QPixmap>();
    ImagesIdlePerso = QVector<QPixmap>();
    ImagesHurtPerso = QVector<QPixmap>();
    ImagesSlidePerso = QVector<QPixmap>();
    ImagesArcPerso = QVector<QPixmap>();
    plateformes = QVector<Tile*>();
    shadow = QVector<QGraphicsDropShadowEffect*>();
    jumpEffect = QVector<QGraphicsEllipseItem*>();
    Background = QVector<Tile*>();
    plateformeFalltoAnim = QVector<QPair<int, int>>();
    plateformeMoveBouncetoAnim = QVector<QPair<int, int>>();
    plateformeMovetoAnim = QVector<int>();
    PosArbreBack = QVector<QPointF>();
    Sorcerer = QVector<E_Sorcerer*>();
    Wolves = QVector<E_Wolves*>();
    bullet = QVector<QPair<QGraphicsPixmapItem*, int>>();
    fleche = QVector<QPair<QGraphicsPixmapItem*, int>>();
    gravitefleche = QVector<float>();
    rotationfleche = QVector<float>();
    crystal = QVector<QPixmap>();
    crystals = QVector<QPixmap>();
    opacTile = QVector<QGraphicsEllipseItem*>();
    CheckP = QVector<CheckPoint*>();
    rect_Wolves_perso = QVector<QGraphicsRectItem*>();
    NightBorne = QVector<E_Nightborne*>();
    rect_NightBorne_perso = QVector<QGraphicsRectItem*>();
    Rectscore = QVector<QGraphicsRectItem*>();
    rect_NightBorne_atk = QVector<QGraphicsRectItem*>();
    rect_Sorcerer = QVector<QGraphicsRectItem*>();
    rect_Sorcerer_plat = QVector<QGraphicsRectItem*>();
    rect_Sorcerer_perso = QVector<QGraphicsRectItem*>();
    ScoreboardLine = QVector<QGraphicsTextItem*>();
    Q->setZValue(-2);
    D->setZValue(-2);
    SPACE->setZValue(-2);
    R->setZValue(-2);
    SHIFT->setZValue(-2);
    E->setZValue(-2);
    secondE->setZValue(-2);
    secondQ->setZValue(-2);
    secondD->setZValue(-2);
    plus->setZValue(-2);

    PseudoText->setZValue(-3);
    ScoreText->setZValue(-3);
    TempsText->setZValue(-3);
    Vie->setZValue(-3);
    CoinText->setZValue(-3);
    this->cooldown_collide_sorcerer = 50;
    this->nb_bullet = 0;
    timeInterLevel = 100;
    RespawnPoint = QPointF(Personnage->pos().rx(),Personnage->pos().ry());
    vague_in_lvl_2 = 0;
    change_in_lvl_2 = false;
    loop_anim_chest_piece = 0;
    coinchest->setPos(-100,-100);
}

void MyScene::updateTimeGame(){
    //Time for the stopwatch
    timePerso ++;
}

QPixmap MyScene::ToBlack(QPixmap pix){
    //Take a pixmap and change it to a black and white version
    QImage originalImage = pix.toImage();
    QImage grayImage = originalImage.convertToFormat(QImage::Format_Grayscale8);
    QPixmap grayPixmap = QPixmap::fromImage(grayImage);
    grayPixmap.setMask(pix.mask());
    return grayPixmap;
}

void MyScene::LoadImage(string Repo, bool NoirOuBlanc){
    //Load all the image of the Personnage and store them in a qvector
    for (int b = 1; b<19; b++){
        QPixmap pix(QString("../qtprojetbase/src/character/") + QString::fromStdString(Repo) + QString("/Idle/idle") + QString::QString::number(b) + QString(".png"));
        QPixmap scaledPixmap = pix.scaled(pix.width() * 2, pix.height() * 2);
        if (NoirOuBlanc){
            scaledPixmap = ToBlack(scaledPixmap);
        }
        ImagesIdlePerso.push_back(scaledPixmap);
    }
    for (int b = 1; b<25; b++){
        QPixmap pix(QString("../qtprojetbase/src/character/") + QString::fromStdString(Repo) + QString("/Run/run") + QString::QString::number(b) + QString(".png"));
        QPixmap scaledPixmap = pix.scaled(pix.width() * 2, pix.height() * 2);
        if (NoirOuBlanc){
            scaledPixmap = ToBlack(scaledPixmap);
        }
        ImagesRunPerso.push_back(scaledPixmap);
    }
    for (int b = 1; b<25; b++){
        QPixmap pix(QString("../qtprojetbase/src/character/") + QString::fromStdString(Repo) + QString("/Back/back") + QString::QString::number(b) + QString(".png"));
        QPixmap scaledPixmap = pix.scaled(pix.width() * 2, pix.height() * 2);
        if (NoirOuBlanc){
            scaledPixmap = ToBlack(scaledPixmap);
        }
        ImagesBackPerso.push_back(scaledPixmap);
    }
    for (int b = 1; b<20; b++){
        QPixmap pix(QString("../qtprojetbase/src/character/") + QString::fromStdString(Repo) + QString("/JumpRight/jump") + QString::QString::number(b) + QString(".png"));
        QPixmap scaledPixmap = pix.scaled(pix.width() * 2, pix.height() * 2);
        if (NoirOuBlanc){
            scaledPixmap = ToBlack(scaledPixmap);
        }
        ImagesJumpRightPerso.push_back(scaledPixmap);
    }
    for (int b = 1; b<8; b++){
        QPixmap pix(QString("../qtprojetbase/src/character/") + QString::fromStdString(Repo) + QString("/Hurt/hurt") + QString::QString::number(b) + QString(".png"));
        QPixmap scaledPixmap = pix.scaled(pix.width() * 2, pix.height() * 2);
        if (NoirOuBlanc){
            scaledPixmap = ToBlack(scaledPixmap);
        }
        ImagesHurtPerso.push_back(scaledPixmap);
    }
    for (int b = 1; b<20; b++){
        QPixmap pix(QString("../qtprojetbase/src/character/") + QString::fromStdString(Repo) + QString("/JumpLeft/jump") + QString::QString::number(b) + QString(".png"));
        QPixmap scaledPixmap = pix.scaled(pix.width() * 2, pix.height() * 2);
        if (NoirOuBlanc){
            scaledPixmap = ToBlack(scaledPixmap);
        }
        ImagesJumpLeftPerso.push_back(scaledPixmap);
    }
    for (int b = 1; b<5; b++){
        QPixmap pix(QString("../qtprojetbase/src/character/") + QString::fromStdString(Repo) + QString("/SlideLeft/slide") + QString::QString::number(b) + QString(".png"));
        QPixmap scaledPixmap = pix.scaled(pix.width() * 2, pix.height() * 2);
        if (NoirOuBlanc){
            scaledPixmap = ToBlack(scaledPixmap);
        }
        ImagesSlidePerso.push_back(scaledPixmap);
    }
    for (int b = 1; b<10; b++){
        QPixmap pix(QString("../qtprojetbase/src/character/") + QString::fromStdString(Repo) + QString("/ArcAttack/atk") + QString::QString::number(b) + QString(".png"));
        QPixmap scaledPixmap = pix.scaled(pix.width() * 2, pix.height() * 2);
        if (NoirOuBlanc){
            scaledPixmap = ToBlack(scaledPixmap);
        }
        ImagesArcPerso.push_back(scaledPixmap);
    }
    for (int b = 1; b<7; b++){
        QPixmap pix(QString("../qtprojetbase/src/environement/TransitionLevel/c") + QString::QString::number(b) + QString(".png"));
        crystal.push_back(pix);
        QPixmap pix2(QString("../qtprojetbase/src/environement/TransitionLevel/cs") + QString::QString::number(b) + QString(".png"));
        crystals.push_back(pix2);
    }
}

void MyScene::AddVectorToScene(){
    //Add the background vector and the platfeorme vector to the scene
    for (unsigned int i = 0; i < Background.size(); i++) {
        Tile* pl = Background[i];
        //pl->setScale(2.0639);//2.0625
        if (i>11 && i<24){
            pl->setOpacity(0);
        }
        if (i>23){
            //qDebug()<<pl->pos();
            PosArbreBack.push_back(pl->pos());
        }
        addItem(pl);
    }
    for (unsigned int i = 0; i < plateformes.size(); i++) {
        Tile* pl = plateformes[i];
        QGraphicsDropShadowEffect* drop = shadow[i];
        if (pl->get_tile_code()==50){
            pl->setPos(pl->pos().rx()+10, pl->pos().ry()-20);
            drop->setBlurRadius(20);
            drop->setColor(QColor(0, 0, 0, 255));
            drop->setOffset(0, 0);
            pl->setGraphicsEffect(drop);
        }
        else{
            pl->setScale(2.5);
        }
        addItem(pl);
    }
    for (unsigned int i = 0; i < plateformes.size(); i++) {
        if (plateformes[i]->get_tile_code()==18){
            plateformeMovetoAnim.push_back(i);
        }
        if (plateformes[i]->get_tile_code()==1049 || plateformes[i]->get_tile_code()==1048){
            indiceblockfin = i;
        }
    }
    for (unsigned int i = 0; i < CheckP.size(); i++) {
        addItem(CheckP[i]);
    }
}

//Création des éléments de la scène
void MyScene::CreateScene(string File, int nb, int zIndex, string Repo, string Repodecor){
    /*
     * Proud of this way of creating my scene
     * This function take a name of a csv doc and read it
     * with the column and row of a number I place the block
     * with the value of the block I apply the right pixmap
     * I store the value, I will use it to do my collision and detect if I'm touching right/left/bottom/coin etc...
    */
    string filename = "../qtprojetbase/src/map/"+File+".csv";
    ifstream infile(filename);
    if (!infile.is_open()) {
        qDebug() << "Erreur lors de l'ouverture du fichier";
    }
    vector<int> data;
    string line, field;
    int ligne = 0;
    int colonne = 0;
    if (nb==1){
        while (getline(infile, line)) {
            stringstream ss(line);
            while (getline(ss, field, ';')) { // Extrait chaque champ de la ligne
                int value = stoi(field); // Convertit le champ en entier
                colonne++;
                if (value!=0 && value>99){
                    Background.push_back(new Tile(QString("../qtprojetbase/src/environement/background/") + QString::QString::number(value) + QString(".png"),colonne, ligne, value,3, zIndex));
                }
                else if (value!=0){
                    Background.push_back(new Tile(QString("../qtprojetbase/src/environement/background/") + QString::QString::number(value) + QString(".png"),colonne, ligne, value,1, zIndex));
                }
            }
            colonne=0;
            ligne++;
        }
        infile.close();
    }
    else if (nb ==2){
        while (getline(infile, line)) {
            stringstream ss(line);
            while (getline(ss, field, ';')) { // Extrait chaque champ de la ligne
                //qDebug()<<QString::fromStdString(field);
                int value = stoi(field); // Convertit le champ en entier
                colonne++;
                //qDebug()<<ligne<<colonne;
                if (value == 555){
                    CheckP.push_back(new CheckPoint(colonne, ligne, value));
                }
                else if (value==50){
                    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/"+ QString::fromStdString(Repodecor) +"/") + QString::QString::number(1) + QString(".png"),colonne, ligne, value, 2, zIndex));
                }
                else if (value>50){
                    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/"+ QString::fromStdString(Repodecor) +"/decor") + QString::QString::number(value-50) + QString(".png"),colonne, ligne, value, 2, zIndex));
                }
                else if (value!=0){
                    plateformes.push_back(new Tile(QString("../qtprojetbase/src/environement/"+ QString::fromStdString(Repo) +"/tile") + QString::QString::number(value) + QString(".png"),colonne, ligne, value, 2, zIndex));
                }
                shadow.push_back(new QGraphicsDropShadowEffect());
                data.push_back(value); // Ajoutez chaque entier au vecteur "data"
            }
            colonne=0;
            ligne++;
        }
        infile.close();
    }
}

void MyScene::CreateLigne(QPointF** tab, int size, QGraphicsPixmapItem* source, QGraphicsPixmapItem* destination){
    //creating a ligne beetween two QGraphicsPixmapItems
    for (int i = 0; i < size; i++) {
        //qDebug()<<i;
        qreal x = destination->pos().rx() + i * (source->pos().rx() - destination->pos().rx()) / size;
        qreal y = destination->pos().ry() + i * (source->pos().ry() - destination->pos().ry()) / size;
        tab[i] = new QPointF(x,y);
    }
}
void MyScene::CreateLigne(QPointF** tab, int size, QGraphicsPixmapItem* source, QGraphicsRectItem* destination){
    //creating a ligne beetween QGraphicsPixmapItem and QGraphicsRectItem
    for (int i = 0; i < size; i++) {
        //qDebug()<<i;
        qreal x = destination->pos().rx() + i * (source->pos().rx() - destination->pos().rx()) / size;
        qreal y = destination->pos().ry() + i * (source->pos().ry() - destination->pos().ry()) / size;
        tab[i] = new QPointF(x,y);
    }
}

void MyScene::update(){
    //The update function of the game, every 15ms
    if(!changelevel && !is_winning){
        if (current_lvl == 2){
            if (change_in_lvl_2){
                if (vague_in_lvl_2 == 1){
                    CreateEnnemylvl2_2();
                    change_in_lvl_2 = false;
                }
                else if (vague_in_lvl_2 == 2){
                    CreateEnnemylvl2_3();
                    change_in_lvl_2 = false;
                }
                else if (vague_in_lvl_2 == 3) {
                    CreateEnnemylvl2_end();
                    change_in_lvl_2 = false;
                }
                else if (vague_in_lvl_2 == 4){
                    for (int i = 0; i<10; i++){
                        removeItem(plateformes.last());
                        plateformes.removeLast();
                    }
                    change_in_lvl_2 = false;
                    vague_in_lvl_2++;
                }
            }
            if (vague_in_lvl_2 == 1){
                bool check = false;
                for (int i = 0; i<Sorcerer.size(); i++){
                    if (!Sorcerer[i]->get_Full_Dead()){
                        check = true;
                    }
                }
                if (!check){
                    change_in_lvl_2 = true;
                }
            }
            else if (vague_in_lvl_2 == 2){
                bool check = false;
                for (int i = 0; i<Wolves.size(); i++){
                    if (!Wolves[i]->get_Full_Dead()){
                        check = true;
                    }
                }
                if (!check){
                    change_in_lvl_2 = true;
                }
            }
            else if (vague_in_lvl_2 == 3){
                bool check = false;
                for (int i = 0; i<Wolves.size(); i++){
                    if (!Wolves[i]->get_Full_Dead()){
                        check = true;
                    }
                }
                for (int i = 0; i<Sorcerer.size(); i++){
                    if (!Sorcerer[i]->get_Full_Dead()){
                        check = true;
                    }
                }
                if (!check){
                    change_in_lvl_2 = true;
                }
            }
            else if (vague_in_lvl_2 == 4){
                bool check = false;
                for (int i = 0; i<NightBorne.size(); i++){
                    if (!NightBorne[i]->get_Full_Dead()){
                        check = true;
                    }
                }
                if (!check){
                    change_in_lvl_2 = true;
                }
            }
        }

        float xperso = Personnage->pos().x() + Personnage->boundingRect().width()/2;
        float yperso = Personnage->pos().y() + Personnage->boundingRect().height()/2;
        for (int i = 0; i<opacTile.size();i++){
            QPointF newSourcePos(xperso - opacTile[i]->boundingRect().width()/2, yperso - opacTile[i]->boundingRect().height()/2);
            opacTile[i]->setPos(newSourcePos.rx(), newSourcePos.ry());
        }
        for (int i = 0; i<CheckP.size(); i++){
            CheckP[i]->Anim();
        }

        QPointF newSourcePos((Personnage->pos().x() + Personnage->boundingRect().width()/2) - rect_chest->boundingRect().width()/2, (Personnage->pos().y() + Personnage->boundingRect().height()/2) - rect_chest->boundingRect().height()/2);
        rect_chest->setPos(newSourcePos);

        for (int i = 0; i<Sorcerer.size(); i++){
            QPointF newRectPos((Sorcerer[i]->pos().x() + Sorcerer[i]->boundingRect().width()/2) - rect_Sorcerer[i]->boundingRect().width()/2, (Sorcerer[i]->pos().y() + Sorcerer[i]->boundingRect().height()/2) - rect_Sorcerer[i]->boundingRect().height()/2);
            rect_Sorcerer[i]->setPos(newRectPos);
            QPointF newRectPosmini((Sorcerer[i]->pos().x() + Sorcerer[i]->boundingRect().width()/2) - rect_Sorcerer_plat[i]->boundingRect().width()/2, (Sorcerer[i]->pos().y() + Sorcerer[i]->boundingRect().height()/2) - rect_Sorcerer_plat[i]->boundingRect().height()/2);
            rect_Sorcerer_plat[i]->setPos(newRectPosmini);
            QPointF newRectPosSorcPerso((Sorcerer[i]->pos().x() + Sorcerer[i]->boundingRect().width()/2) - rect_Sorcerer_perso[i]->boundingRect().width()/2, (Sorcerer[i]->pos().y() + Sorcerer[i]->boundingRect().height()/2) - rect_Sorcerer_perso[i]->boundingRect().height()/2);
            rect_Sorcerer_perso[i]->setPos(newRectPosSorcPerso);
        }
        for (int i = 0; i<Wolves.size(); i++){
            QPointF newRectPos((Wolves[i]->pos().x() + Wolves[i]->boundingRect().width()/2) - rect_Wolves_perso[i]->boundingRect().width()/2, (Wolves[i]->pos().y() + Wolves[i]->boundingRect().height()/2) - rect_Wolves_perso[i]->boundingRect().height()/2);
            rect_Wolves_perso[i]->setPos(newRectPos);
        }
        for (int i = 0; i<NightBorne.size(); i++){
            QPointF newRectPos((NightBorne[i]->pos().x() + NightBorne[i]->get_Scale()*NightBorne[i]->boundingRect().width()/2) - rect_NightBorne_perso[i]->boundingRect().width()/2, (NightBorne[i]->pos().y() + NightBorne[i]->get_Scale()*NightBorne[i]->boundingRect().height()/2) - rect_NightBorne_perso[i]->boundingRect().height()/2);
            rect_NightBorne_perso[i]->setPos(newRectPos);
            QPointF newRectPos2((NightBorne[i]->pos().x() + NightBorne[i]->get_Scale()*NightBorne[i]->boundingRect().width()/2) - rect_NightBorne_atk[i]->boundingRect().width()/2, (NightBorne[i]->pos().y() + NightBorne[i]->get_Scale()*NightBorne[i]->boundingRect().height()/2) - rect_NightBorne_atk[i]->boundingRect().height()/2);
            rect_NightBorne_atk[i]->setPos(newRectPos2);
        }
        if (nbkeypress==0){
            v_X=0;
            vitessegauche = 0;
            vitessedroite = 0;
            puissance_slide = 1;
        }
        if(v_X>4){
            v_X = 4;
        }
        if(v_X<-4){
            v_X = -4;
        }
        //Mouvement de notre personnage
        QPointF pos = Personnage->pos(); //récupération de la position de l'objet qgti

        if (pos.ry()>background.height()+50 || pos.rx()>background.width()+20 || pos.rx()<-50){
            Personnage->setPos(RespawnPoint.rx(), RespawnPoint.ry()-150);
            MinusOneLife();
            is_colisionning_left = false;
            is_colisionning_right = false;
            is_colisionning_top = false;
            is_colisionning_bottom = false;
             //
            is_falling = true;
            is_jumping = true;
            //
            posPlatMove = 0;
            sensPlatMove = -1;

            for (unsigned int i = 24; i < Background.size(); i++) {
                Background[i]->setPos(PosArbreBack[i-24].rx(), PosArbreBack[i-24].ry());//recuperer les coordonnées à l'init puis réafecter
            }
            for (int i = 0; i  < plateformeMoveBouncetoAnim.size(); i++){
                plateformeMoveBouncetoAnim.removeAt(i);
            }
            for (int i = 0; i  < plateformeMovetoAnim.size(); i++){
                plateformes[plateformeMovetoAnim[i]]->setPos(plateformes[plateformeMovetoAnim[i]]->get_OriginalX(), plateformes[plateformeMovetoAnim[i]]->get_OriginalY());
            }
            plateformeMoveBouncetoAnim.clear();
            opacite_Bg = 0;
            v_Y = 0;
        }
        //si touche plateforme moove
        float vplat = 0;
        //qDebug()<<boolForPlatMoveAndPerso[0]<<boolForPlatMoveAndPerso[1];
        intindiceplat[1] = intindiceplat [0];
        for (int i = 0; i  < plateformeMovetoAnim.size(); i++){
            //int indice = plateformes.indexOf(boolForPlatMoveAndPerso[0].second);
            int indice2 = plateformeMovetoAnim.indexOf(boolForPlatMoveAndPerso[0].second);
            intindiceplat [0] = indice2;
            //qDebug()<<indice2;
            if ((intindiceplat [0]%2 ==0 || intindiceplat [1]%2 ==0)  && (boolForPlatMoveAndPerso[0].first==true || boolForPlatMoveAndPerso[1].first == true) ){ // BOOL TRUE QUE UNE FOIS SUR DEUX APRES "R" WHYYYYYYYYYY
                //qDebug()<<"collide1";
                vplat = posPlatMove/8;
            }
            else if(boolForPlatMoveAndPerso[0].first==true || boolForPlatMoveAndPerso[1].first == true) {
                //qDebug()<<"collide2";
                vplat = -posPlatMove/8;
            }
        }
        pos = Personnage->pos();
        if (pos.rx()<=6000){ //2454
            if (is_colisionning_left && is_backing){
                v_X = 0;
            }
            else if (is_colisionning_left) {
                v_X = 0;
            }
            /*if (current_lvl == 0){
                v_X = 1;
                is_running = true;
            }*/
            Personnage->setPos(pos.rx()+puissance_slide*(v_X)+vplat, pos.ry()+v_Y);
            v_Y += G;
        }
        // savoir dans quelle scene on place notre point à suivre///////////////////////////////
        if (pos.ry()+v_Y<this->bguntier){
            elementcentered->setPos(pos.rx()+v_X+(width_Perso/2), this->Ybgtier);
        }
        else if (pos.ry()+v_Y>=this->bguntier && pos.ry()+v_Y<this->bgdeuxtier){
            elementcentered->setPos(pos.rx()+v_X+(width_Perso/2), this->Ybgmid);
        }
        else{
            elementcentered->setPos(pos.rx()+v_X+(width_Perso/2), this->Ybglast);
        }
        ////////////////////////////////////////////////////////////////////////////////////////

        if (shaking && elapsedMs < max(10,min(puissanceshake,16))){
            //qDebug()<<max(10,min(puissanceshake,16));
            ShakeView();
        }
        else if (shaking){
            shaking = false;
            elapsedMs = 0;
        }

        //Récupération de la vue
        QGraphicsView* viewPerso = this->views()[0];

        //Update de la vue sur le point central
        viewPerso->centerOn(elementcentered);
        //Appel pour gérer les coffres
        CheckChest();
        //Appel pour gérer le compagnon
        AnimCompagnion();
        //Appel pour gérer le parallax
        Background_Parallax();
        //Appel pour gérer les collisions du personnage
        Collision();
        //Appel pour gérer les animations
        Animation();
        //Appel pour gérer les plateformes qui bougent

        PlateformeMove();
        moduloUpdate++;

        if (can_anim_particle){
            if (loop_anim_particle <=0){
                can_anim_particle = false;
                for (auto ellipse : jumpEffect) {
                    removeItem(ellipse); // supprime l'ellipse de la scène
                    delete ellipse; // libère la mémoire occupée par l'ellipse
                }
                jumpEffect.clear();
            }
            else{
                animParticle();
            }
        }
        if (plateformeFalltoAnim.size() != 0){
            for (int i = 0; i<plateformeFalltoAnim.size(); i++){
                if (plateformeFalltoAnim[i].second <=0){
                    plateformes[plateformeFalltoAnim[i].first]->setPos(plateformes[plateformeFalltoAnim[i].first]->pos().rx(), plateformes[plateformeFalltoAnim[i].first]->pos().ry()+5000);
                    plateformeFalltoAnim[i].second = 300;
                }
                else if(plateformeFalltoAnim[i].second>100){
                    plateformeFalltoAnim[i].second --;
                }
                else if (plateformeFalltoAnim[i].second == 100){
                    plateformes[plateformeFalltoAnim[i].first]->setPos(plateformes[plateformeFalltoAnim[i].first]->get_OriginalX(), plateformes[plateformeFalltoAnim[i].first]->get_OriginalY());
                    plateformeFalltoAnim.removeAt(i);
                }
                else{
                    PlatformeFall(plateformeFalltoAnim[i].first, i);
                }
            }
        }
        if (plateformeMoveBouncetoAnim.size() != 0){
            for (int i = 0; i<plateformeMoveBouncetoAnim.size(); i++){
                if (plateformeMoveBouncetoAnim[i].second >0){
                    BouncePlatMove(plateformeMoveBouncetoAnim[i].first, i);
                }
            }
        }

        if (Personnage->collidesWithItem(plateformes[indiceblockfin])){
            //pauseGame = true;

            //if (plateformes[indiceblockfin]->get_tile_code() == 1048 && !tabchangelvl[0] && !tabchangelvl[1]){
            if (current_lvl >= 3){
                current_lvl = 0;
                is_winning = true;
                createWin();
            }
            else{
                transi_Perso_Fin->setPixmap(QString("../qtprojetbase/src/environement/TransitionLevel/transi1.png"));
                transi_Perso_Fin->setZValue(-1);
                current_lvl++;
                changelevel = true;
                timeInterLevel = 0;
            }
            //}
        }
        CheckEnnemy();
        AnimBulletSorcerer();
        Ath();
        if (is_arcing){
            ArcAttack();
        }
        AnimFleche();
        if (temps_slide<0){
            is_sliding = false;
            puissance_slide = 1;
            temps_slide = 20;
        }
        else if (is_sliding) {
            Slide();
        }
        AnimCrystal();
        if (Personnage->collidesWithItem(RectFinNiv) && can_anim_fin){
            if (loop_Anim_Fin == 18){
                Personnage->setZValue(-1);
            }
            if (loop_Anim_Fin<97 && loop_Anim_Fin%6 == 0){
                transi_Perso_Fin->setZValue(5);
                transi_Perso_Fin->setPos(Personnage->pos().rx()-1.1*transi_Perso_Fin->boundingRect().width()/2, Personnage->pos().ry()-Personnage->boundingRect().height()+transi_Perso_Fin->boundingRect().height());
                transi_Perso_Fin->setPixmap(QString("../qtprojetbase/src/environement/TransitionLevel/transi") + QString::QString::number(loop_Anim_Fin/6) + QString(".png"));
            }
            else if (loop_Anim_Fin%6 == 0){
                if (current_lvl >= 3){
                    current_lvl = 0;
                    PlayerWin = true;
                    is_winning = true;
                    createWin();
                }
                else{
                    transi_Perso_Fin->setPixmap(QString("../qtprojetbase/src/environement/TransitionLevel/transi1.png"));
                    transi_Perso_Fin->setZValue(-1);
                    current_lvl++;
                    changelevel = true;
                    timeInterLevel = 0;
                }
            }
            loop_Anim_Fin++;
        }
        else {
            loop_Anim_Fin = 1;
            Personnage->setZValue(4);
            transi_Perso_Fin->setZValue(-1);
        }
    }
    else if (changelevel && interlvl2){
        interlvl2 = true;
        if (timeInterLevel>0){
            Interlvl->setOpacity(timeInterLevel/100.0);
            Level->setOpacity(timeInterLevel/100.0);
        }
        else {
            Interlvl->setOpacity(0);
            Level->setOpacity(0);
            timeInterLevel = 0;
            interlvl2 = false;
            changelevel = false;
        }
        timeInterLevel--;
    }
    else if (is_winning){

    }
    else{
        InterLevel();
    }
}

void MyScene::AnimCrystal(){
    //Animate the end crystal and the checkpoint of the scene
    if (loop_crystal<43 && loop_crystal%7 == 0){
        CrystalScene->setPixmap(crystal[(loop_crystal/7)-1]);
        CrystalSceneSombre->setPixmap(crystals[(loop_crystal/7)-1]);
    }
    else if (loop_crystal%7 == 0) {
        loop_crystal = 7;
        CrystalScene->setPixmap(crystal[(loop_crystal/7)-1]);
        CrystalSceneSombre->setPixmap(crystals[(loop_crystal/7)-1]);
    }
    loop_crystal ++;
    angle_crystal += PI/50;
    CrystalScene->setPos(CrystalScene->pos().rx(), CrystalScene->pos().ry()+sin(angle_crystal));
    CrystalSceneSombre->setPos(CrystalScene->pos().rx(), CrystalScene->pos().ry());
    CrystalSceneSombre->setOpacity((sin(angle_crystal)+1)/2);
}


void MyScene::removecontrolsTuto(){
    //when we are not in the tuto level, set the z value at -2
    Q->setZValue(-2);
    D->setZValue(-2);
    SPACE->setZValue(-2);
    E->setZValue(-2);
    SHIFT->setZValue(-2);
    E->setZValue(-2);
    secondE->setZValue(-2);
    secondQ->setZValue(-2);
    secondD->setZValue(-2);
    plus->setZValue(-2);
    /*removeItem(Q);
    removeItem(D);
    removeItem(SPACE);
    removeItem(SHIFT);
    removeItem(E);
    removeItem(secondE);
    removeItem(secondQ);
    removeItem(secondD);
    removeItem(plus);
    delete Q;
    delete D;
    delete SPACE;
    delete SHIFT;
    delete E;
    delete secondE;
    delete secondQ;
    delete secondD;
    delete plus;*/
}

void MyScene::Ath(){
    //placement of the ATH (heart, time, coin)
    QPointF posFond((elementcentered->pos().x() + elementcentered->boundingRect().width()/2) - Interlvl->boundingRect().width()/2, (elementcentered->pos().y() + elementcentered->boundingRect().height()/2) - Interlvl->boundingRect().height()/2);
    QPointF posHeart(elementcentered->pos().rx()+500, elementcentered->pos().ry()-340);
    QPointF posprBg(elementcentered->pos().rx()-pausebg->boundingRect().width()/2, elementcentered->pos().ry());
    //Loop de la pièce
    if (loopPieceAth%8==0 && loopPieceAth<81){
        coin->setPixmap(QString("../qtprojetbase/src/environement/decor/") + QString::QString::number(loopPieceAth/8) + QString(".png"));
    }
    else if (loopPieceAth%8==0) {
        loopPieceAth = 8;
        coin->setPixmap(QString("../qtprojetbase/src/environement/decor/") + QString::QString::number(loopPieceAth/8) + QString(".png"));
    }
    loopPieceAth++;
    //Placement de l'ATH
    if (elementcentered->pos().rx()<=640){
        posHeart = QPointF(1139, elementcentered->pos().ry()-340);
        posFond = QPointF(0,elementcentered->pos().ry()-Interlvl->boundingRect().height()/2);
        posprBg = QPointF(pausebg->boundingRect().width()/2, elementcentered->pos().ry());
    }
    else if (elementcentered->pos().rx()>=4643){
        posHeart = QPointF(5142, elementcentered->pos().ry()-340);
        posprBg = QPointF(background.width()-pausebg->boundingRect().width()*3/2, elementcentered->pos().ry());
        posFond = QPointF(background.width()-Interlvl->boundingRect().width(),elementcentered->pos().ry()-Interlvl->boundingRect().height()/2);
    }
    pausebg->setPos(posprBg.rx(), posprBg.ry()- pausebg->boundingRect().height()/2);
    Level->setPos(posFond.rx()+Interlvl->boundingRect().width()/2-Level->boundingRect().width()/2, posFond.ry()+Interlvl->boundingRect().height()/2 - Level->boundingRect().height()/2);
    Interlvl->setPos(posFond);
    //posHeart = new QPointF(elementcentered->pos().rx()+500, elementcentered->pos().ry()-340);
    nbcoin->setPlainText("X " + QString::number(piece));
    nbcoin->setPos(posHeart.rx()-80, posHeart.ry() + 2);
    coin->setPos(posHeart.rx()-105, posHeart.ry() + 1);
    QString minutes(QString::number(timePerso/6000));
    QString secondes(QString::number((timePerso%6000)/100));
    if (timePerso/6000 < 10){
        minutes = "0" + QString::number(timePerso/6000);
    }
    if ((timePerso%6000)/100<10) {
        secondes = "0" + QString::number((timePerso%6000)/100);
    }
    timerPrPerso->setPlainText(minutes+ ":" +secondes/*+":"+QString::number((timePerso%6000)%60)*/);//décommenter pour les ms
    timerPrPerso->setPos(posHeart.rx()-190, posHeart.ry() + 2); //-230 si avec ms
    for(int i = 0; i<Heart.size(); i++){
        Heart[i]->setPos(posHeart.rx()+1.5*Heart[i]->boundingRect().width()*i, posHeart.ry());
    }
}

void MyScene::MinusOneLife(){
    //Update the heart ATH and set the life of the personnage
    this->life--;
    if (life<=0){
        is_winning = true;
        current_lvl = 0;
        qDebug()<<"ui";
        createWin();
    }
    else {
        if (life%5 == 0){
            this->life--;
        }
        int var = (life > 25) ? 5 :(life > 20) ? 4 : (life > 15) ? 3 : (life > 10) ? 2 : (life > 5) ? 1 : (life > 0) ? 0 : -1;
        if (var==-1) {
            Personnage->setPos(100,0);
            is_colisionning_left = false;
            is_colisionning_right = false;
            is_colisionning_top = false;
            is_colisionning_bottom = false;
            //
            is_falling = true;
            is_jumping = true;
            //
            posPlatMove = 0;
            sensPlatMove = -1;

            for (unsigned int i = 24; i < Background.size(); i++) {
                Background[i]->setPos(PosArbreBack[i-24].rx(), PosArbreBack[i-24].ry());//recuperer les coordonnées à l'init puis réafecter
            }
            for (int i = 0; i  < plateformeMoveBouncetoAnim.size(); i++){
                plateformeMoveBouncetoAnim.removeAt(i);
            }
            for (int i = 0; i  < plateformeMovetoAnim.size(); i++){
                plateformes[plateformeMovetoAnim[i]]->setPos(plateformes[plateformeMovetoAnim[i]]->get_OriginalX(), plateformes[plateformeMovetoAnim[i]]->get_OriginalY());
            }
            plateformeMoveBouncetoAnim.clear();
            opacite_Bg = 0;
            v_Y = 0;
        }
        else {
            Heart[var]->setPixmap(QString("../qtprojetbase/src/character/Heart/heart") + QString::QString::number(life%5) + QString(".png"));
        }
        //qDebug()<<life;
    }
}
void MyScene::AddOneLife(){
    //Update the heart ATH and set the life of the personnage
    if (life<25){
        this->life++;
        if (life%5 == 0){
            this->life++;
        }
        int var = (life > 20) ? 4 : (life > 15) ? 3 : (life > 10) ? 2 : (life > 5) ? 1 : (life > 0) ? 0 : -1;
        if (var==-1) {
            Personnage->setPos(100,0);
            is_colisionning_left = false;
            is_colisionning_right = false;
            is_colisionning_top = false;
            is_colisionning_bottom = false;
            //
            is_falling = true;
            is_jumping = true;
            //
            posPlatMove = 0;
            sensPlatMove = -1;

            for (unsigned int i = 24; i < Background.size(); i++) {
                Background[i]->setPos(PosArbreBack[i-24].rx(), PosArbreBack[i-24].ry());//recuperer les coordonnées à l'init puis réafecter
            }
            for (int i = 0; i  < plateformeMoveBouncetoAnim.size(); i++){
                plateformeMoveBouncetoAnim.removeAt(i);
            }
            for (int i = 0; i  < plateformeMovetoAnim.size(); i++){
                plateformes[plateformeMovetoAnim[i]]->setPos(plateformes[plateformeMovetoAnim[i]]->get_OriginalX(), plateformes[plateformeMovetoAnim[i]]->get_OriginalY());
            }
            plateformeMoveBouncetoAnim.clear();
            opacite_Bg = 0;
            v_Y = 0;
        }
        else {
            Heart[var]->setPixmap(QString("../qtprojetbase/src/character/Heart/heart") + QString::QString::number(life%5) + QString(".png"));
        }
        if (life >20){
            Heart[3]->setPixmap(QString("../qtprojetbase/src/character/Heart/heart5.png"));
        }
        if (life >15){
            Heart[2]->setPixmap(QString("../qtprojetbase/src/character/Heart/heart5.png"));
        }
        if (life >10){
            Heart[1]->setPixmap(QString("../qtprojetbase/src/character/Heart/heart5.png"));
        }
        if (life >5){
            Heart[0]->setPixmap(QString("../qtprojetbase/src/character/Heart/heart5.png"));
        }
    }
    else {
        for (int i =0; i<5; i++){
            Heart[i]->setPixmap(QString("../qtprojetbase/src/character/Heart/heart5.png"));
        }
    }
}

void MyScene::CheckEnnemy(){
    //Function for all the ennemy
    for (int i = 0; i<Sorcerer.size(); i++){
        if (!Sorcerer[i]->get_Death()){
        Sorcerer[i]->health();
        if (Personnage->collidesWithItem(Sorcerer[i]) && is_sliding && can_hurt_slide){
            can_hurt_slide = false;
            if (Sorcerer[i]->get_Life()-40>0){
                Sorcerer[i]->set_Life(Sorcerer[i]->get_Life()-40);
                Sorcerer[i]->set_Hurt(true);
                Sorcerer[i]->set_Loop(3);
                if (signbit(v_X)){
                    Sorcerer[i]->set_Sens_Hurt(-1);
                }
                else {
                    Sorcerer[i]->set_Sens_Hurt(1);
                }
            }
            else {
                Sorcerer[i]->bar->setZValue(-2);
                Sorcerer[i]->healthdeco->setZValue(-2);
                Sorcerer[i]->set_Death(true);
                Sorcerer[i]->set_Loop(4);
                AddOneLife();
                AddOneLife();
                //animdeath
            }
            HitFromSlide->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/HitFromSlide.wav"));
            HitFromSlide->play();
        }
        if (Sorcerer[i]->get_Hurt()){
            Sorcerer[i]->hurt();
        }
        else if (Personnage->collidesWithItem(rect_Sorcerer_perso[i]) && nb_bullet<4){
            // Collide avec la box du sorcerer (attaque)
            if (Personnage->pos().rx()<Sorcerer[i]->pos().rx()+Sorcerer[i]->boundingRect().width()/2){
                Sorcerer[i]->attack(1);
                if (Sorcerer[i]->get_Loop() == 2){
                    QPair<QGraphicsPixmapItem*, int> myPair(new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/character/ennemy/sorcerer/bullet/bullet1.png")), -1);
                    bullet.push_back(myPair);
                    bullet.last().first->setScale(1.6);
                    bullet.last().first->setZValue(13);
                    bullet.last().first->setPos(Sorcerer[i]->pos().rx()-bullet.last().first->boundingRect().width()/2, Sorcerer[i]->pos().ry() + 40);
                    addItem(bullet.last().first);
                    nb_bullet ++;
                }
            }
            else {
                Sorcerer[i]->attack(-1);
                if (Sorcerer[i]->get_Loop() == 2){
                    QTransform transform;
                    transform.scale(-1, 1);
                    QPixmap pixmap("../qtprojetbase/src/character/ennemy/sorcerer/bullet/bullet1.png");
                    pixmap = pixmap.transformed(transform);
                    QPair<QGraphicsPixmapItem*, int> myPair(new QGraphicsPixmapItem(pixmap), 1);
                    bullet.push_back(myPair);
                    bullet.last().first->setScale(1.6);
                    bullet.last().first->setZValue(13);
                    bullet.last().first->setPos(Sorcerer[i]->pos().rx()+Sorcerer[i]->boundingRect().width()-bullet.last().first->boundingRect().width()/2, Sorcerer[i]->pos().ry() + 40);
                    addItem(bullet.last().first);
                    nb_bullet ++;
                }
            }
        }
        else if (nb_bullet >= 4){
            if (Personnage->pos().rx()<Sorcerer[i]->pos().rx()+Sorcerer[i]->boundingRect().width()/2){
                Sorcerer[i]->idle(1);
            }
            else {
                Sorcerer[i]->idle(-1);
            }
        }
        else if (Personnage->collidesWithItem(rect_Sorcerer[i]) && (abs(Sorcerer[i]->get_Ox()+ Sorcerer[i]->get_Range())>abs(Personnage->pos().rx()))){
            // Collide avec la grande box du sorcerer (run)
            int nbpassage = 0;
            for (auto plateforme : plateformes){
                if (rect_Sorcerer_plat[i]->collidesWithItem(plateforme)){
                    if (plateforme->get_tile_code()==4 || plateforme->get_tile_code()==5 || plateforme->get_tile_code()==8 || plateforme->get_tile_code()==9){
                        nbpassage++;
                    }
                }
            }
            if (nbpassage == 0 && (Sorcerer[i]->get_Ox() + Sorcerer[i]->get_Range())>Sorcerer[i]->pos().rx() && (Sorcerer[i]->get_Ox() - Sorcerer[i]->get_Range())<Sorcerer[i]->pos().rx()){
                if (Personnage->pos().rx()<Sorcerer[i]->pos().rx()+Sorcerer[i]->boundingRect().width()/2){
                    Sorcerer[i]->run(1);
                    Sorcerer[i]->setPos(Sorcerer[i]->pos().rx() - 2, Sorcerer[i]->pos().ry());
                }
                else {
                    Sorcerer[i]->run(-1);
                    Sorcerer[i]->setPos(Sorcerer[i]->pos().rx() + 2, Sorcerer[i]->pos().ry());
                }
            }
            else {
                Sorcerer[i]->setPos(Sorcerer[i]->get_Ox(), Sorcerer[i]->get_Oy());
            }
        }
        else {
            //savoir si on est en idle ou en run quand le personnage n'est pas en collision
            if (Sorcerer[i]->get_Loop_Idle()<0){
                Sorcerer[i]->set_Loop_Idle(rand()%200+50);
                Sorcerer[i]->set_Random_Idle(rand()%2);
            }
            //pour sorcerer idle
            if (Sorcerer[i]->get_Random_Idle() == 0){
                if (Personnage->pos().rx()<Sorcerer[i]->pos().rx()+Sorcerer[i]->boundingRect().width()/2){
                    Sorcerer[i]->idle(1);
                }
                else {
                    Sorcerer[i]->idle(-1);
                }
            }
            //pour sorcerer run
            else if (Sorcerer[i]->get_Random_Idle() == 1){
                int nbpassage = 0;
                for (auto plateforme : plateformes){
                    if (rect_Sorcerer_plat[i]->collidesWithItem(plateforme)){
                        if (plateforme->get_tile_code()==4 || plateforme->get_tile_code()==5 || plateforme->get_tile_code()==8 || plateforme->get_tile_code()==9){
                            nbpassage++;
                        }
                    }
                }
                if (nbpassage>0 && this->cooldown_collide_sorcerer<0){
                    Sorcerer[i]->set_Sens_Run(Sorcerer[i]->get_Sens_Run()*-1);
                    this->cooldown_collide_sorcerer = 100;
                }
                this->cooldown_collide_sorcerer --;
                if ((Sorcerer[i]->get_Ox() + Sorcerer[i]->get_Range())>Sorcerer[i]->pos().rx() && (Sorcerer[i]->get_Ox() - Sorcerer[i]->get_Range())<Sorcerer[i]->pos().rx()){
                    Sorcerer[i]->setPos(Sorcerer[i]->pos().rx() + 2*Sorcerer[i]->get_Sens_Run(), Sorcerer[i]->pos().ry());
                }
                else {
                    Sorcerer[i]->set_Sens_Run(Sorcerer[i]->get_Sens_Run() * -1);
                    Sorcerer[i]->run(-Sorcerer[i]->get_Sens_Run());
                    Sorcerer[i]->setPos(Sorcerer[i]->pos().rx() + 10 * Sorcerer[i]->get_Sens_Run(), Sorcerer[i]->pos().ry());
                }
                Sorcerer[i]->run(-Sorcerer[i]->get_Sens_Run());
            }
            Sorcerer[i]->set_Loop_Idle(Sorcerer[i]->get_Loop_Idle() - 1);
        }
        Sorcerer[i]->setPos(Sorcerer[i]->pos().rx(), Sorcerer[i]->pos().ry()+sin(Sorcerer[i]->get_Angle()));
        if (!Sorcerer[i]->get_Death()){
            Sorcerer[i]->set_Angle(Sorcerer[i]->get_Angle() + 3.14/40);
        }
        }
        else {
            Sorcerer[i]->death();
        }
    }
    ////////// Wolves
    for (int i = 0; i<Wolves.size(); i++){
        if (!Wolves[i]->get_Death()){
            Wolves[i]->health();
            if (Personnage->collidesWithItem(Wolves[i]) && is_sliding && can_hurt_slide){
                can_hurt_slide = false;
                if (Wolves[i]->get_Life()-22>0){
                    Wolves[i]->set_Life(Wolves[i]->get_Life()-22);
                    Wolves[i]->set_Hurt(true);
                    Wolves[i]->set_Loop(3);
                    if (signbit(v_X)){
                        Wolves[i]->set_Sens_Hurt(-1);
                    }
                    else {
                        Wolves[i]->set_Sens_Hurt(1);
                    }
                }
                else {
                    Wolves[i]->bar->setZValue(-2);
                    Wolves[i]->healthdeco->setZValue(-2);
                    Wolves[i]->set_Death(true);
                    Wolves[i]->set_Loop(4);
                    AddOneLife();
                    AddOneLife();
                    //animdeath
                }
                HitFromSlide->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/HitFromSlide.wav"));
                HitFromSlide->play();
            }
            if (Wolves[i]->get_Hurt()){
                Wolves[i]->hurt();
            }
            else if (Personnage->collidesWithItem(Wolves[i])){
                // Collide avec la box du Wolves (attaque)
                if (Personnage->pos().rx()<Wolves[i]->pos().rx()+Wolves[i]->boundingRect().width()/2){
                    Wolves[i]->attack(1);
                    if (Wolves[i]->get_Loop() == 24){
                        this->hurting_attack = true;
                        this->loop = 2;
                        MinusOneLife();
                        Hit->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/Hit.wav"));
                        Hit->play();
                    }
                }
                else {
                    Wolves[i]->attack(-1);
                    if (Wolves[i]->get_Loop() == 24){
                        this->hurting_attack = true;
                        this->loop = 2;
                        MinusOneLife();
                        Hit->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/Hit.wav"));
                        Hit->play();
                    }
                }
            }
            else if (Personnage->collidesWithItem(rect_Wolves_perso[i]) && (Wolves[i]->get_Ox() + Wolves[i]->get_Range())>Wolves[i]->pos().rx() && (Wolves[i]->get_Ox() - Wolves[i]->get_Range())<Wolves[i]->pos().rx()){
                // Collide avec la grande box du Wolves (run)
                if (Personnage->pos().rx()<Wolves[i]->pos().rx()+Wolves[i]->boundingRect().width()/2){
                    Wolves[i]->run(1);
                    if ((Wolves[i]->get_Ox() + Wolves[i]->get_Range())>Wolves[i]->pos().rx() && (Wolves[i]->get_Ox() - Wolves[i]->get_Range())<Wolves[i]->pos().rx()){
                        Wolves[i]->setPos(Wolves[i]->pos().rx() - 3, Wolves[i]->pos().ry());
                    }
                    else {
                        Wolves[i]->setPos(Wolves[i]->get_Ox(), Wolves[i]->get_Oy());
                    }
                }
                else {
                    Wolves[i]->run(-1);
                    if ((Wolves[i]->get_Ox() + Wolves[i]->get_Range())>Wolves[i]->pos().rx() && (Wolves[i]->get_Ox() - Wolves[i]->get_Range())<Wolves[i]->pos().rx()){
                        Wolves[i]->setPos(Wolves[i]->pos().rx() + 3, Wolves[i]->pos().ry());
                    }
                    else {
                        Wolves[i]->setPos(Wolves[i]->get_Ox(), Wolves[i]->get_Oy());
                    }
                }
            }
            else {
                //savoir si on est en idle ou en run quand le personnage n'est pas en collision
                if (Wolves[i]->get_Loop_Idle()<0){
                    Wolves[i]->set_Loop_Idle(rand()%200+50);
                    Wolves[i]->set_Random_Idle(rand()%2);
                }
                //pour Wolves idle
                if (Wolves[i]->get_Random_Idle() == 0){
                    if (Personnage->pos().rx()<Wolves[i]->pos().rx()+Wolves[i]->boundingRect().width()/2){
                        Wolves[i]->idle(1);
                    }
                    else {
                        Wolves[i]->idle(-1);
                    }
                }
                //pour Wolves run
                else if (Wolves[i]->get_Random_Idle() == 1){
                    if ((Wolves[i]->get_Ox() + Wolves[i]->get_Range())>=Wolves[i]->pos().rx() && (Wolves[i]->get_Ox() - Wolves[i]->get_Range())<=Wolves[i]->pos().rx()){
                        Wolves[i]->setPos(Wolves[i]->pos().rx() + 3*Wolves[i]->get_Sens_Run(), Wolves[i]->pos().ry());
                    }
                    else {
                        Wolves[i]->set_Sens_Run(Wolves[i]->get_Sens_Run() * -1);
                        Wolves[i]->run(-Wolves[i]->get_Sens_Run());
                        Wolves[i]->setPos(Wolves[i]->pos().rx() + 20 * Wolves[i]->get_Sens_Run(), Wolves[i]->pos().ry());
                    }
                    Wolves[i]->run(-Wolves[i]->get_Sens_Run());
                }
                Wolves[i]->set_Loop_Idle(Wolves[i]->get_Loop_Idle() - 1);

        // ICI BUG
                //if (Wolves.size()!=0){
                    if (Wolves[i]->get_Ox() + Wolves[i]->get_Range() +10 <Wolves[i]->pos().rx() ||  Wolves[i]->get_Ox() - Wolves[i]->get_Range() - 10 >Wolves[i]->pos().rx()){
                        Wolves[i]->setPos(Wolves[i]->get_Ox(), Wolves[i]->get_Oy());
                    }
                //}
            }
        }
        else{
            Wolves[i]->death();
        }
    }
    ////////// NightBorne
    for (int i = 0; i<NightBorne.size(); i++){
        if (!NightBorne[i]->get_Death()){
        NightBorne[i]->health();
        if (Personnage->collidesWithItem(NightBorne[i]) && is_sliding && can_hurt_slide){
            can_hurt_slide = false;
            if (NightBorne[i]->get_Life()-32>0){
                NightBorne[i]->set_Life(NightBorne[i]->get_Life()-32);
                NightBorne[i]->set_Hurt(true);
                NightBorne[i]->set_Loop(3);
                if (signbit(v_X)){
                    NightBorne[i]->set_Sens_Hurt(-1);
                }
                else {
                    NightBorne[i]->set_Sens_Hurt(1);
                }
            }
            else {
                NightBorne[i]->bar->setZValue(-2);
                NightBorne[i]->healthdeco->setZValue(-2);
                NightBorne[i]->set_Death(true);
                NightBorne[i]->set_Loop(4);
                AddOneLife();
                AddOneLife();
                AddOneLife();
                AddOneLife();
                AddOneLife();
                //animdeath
            }
            HitFromSlide->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/HitFromSlide.wav"));
            HitFromSlide->play();
        }
        if (NightBorne[i]->get_Hurt()){
            NightBorne[i]->hurt();
        }
        else if (Personnage->collidesWithItem(rect_NightBorne_atk[i])){
            // Collide avec la box du NightBorne (attaque)
            if (Personnage->pos().rx()<NightBorne[i]->pos().rx()+NightBorne[i]->boundingRect().width()/2){
                NightBorne[i]->attack(1);
                if (NightBorne[i]->get_Loop() == 60){
                    this->hurting_attack = true;
                    this->loop = 2;
                    MinusOneLife();
                    MinusOneLife();
                    Hit->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/Hit.wav"));
                    Hit->play();
                }
            }
            else {
                NightBorne[i]->attack(-1);
                if (NightBorne[i]->get_Loop() == 60){
                    this->hurting_attack = true;
                    this->loop = 2;
                    MinusOneLife();
                    MinusOneLife();
                    Hit->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/Hit.wav"));
                    Hit->play();
                }
            }
        }
        else if (Personnage->collidesWithItem(rect_NightBorne_perso[i])){
            // Collide avec la grande box du NightBorne (run)
            if (Personnage->pos().rx()<NightBorne[i]->pos().rx()+NightBorne[i]->boundingRect().width()/2){
                NightBorne[i]->run(1);
                if ((NightBorne[i]->get_Ox() + NightBorne[i]->get_Range())>NightBorne[i]->pos().rx() && (NightBorne[i]->get_Ox() - NightBorne[i]->get_Range())<NightBorne[i]->pos().rx()){
                    NightBorne[i]->setPos(NightBorne[i]->pos().rx() - 4.5, NightBorne[i]->pos().ry());
                }
                else {
                    NightBorne[i]->setPos(NightBorne[i]->get_Ox(), NightBorne[i]->get_Oy());
                }
            }
            else {
                NightBorne[i]->run(-1);
                if ((NightBorne[i]->get_Ox() + NightBorne[i]->get_Range())>NightBorne[i]->pos().rx() && (NightBorne[i]->get_Ox() - NightBorne[i]->get_Range())<NightBorne[i]->pos().rx()){
                    NightBorne[i]->setPos(NightBorne[i]->pos().rx() + 4.5, NightBorne[i]->pos().ry());
                }
                else {
                    NightBorne[i]->setPos(NightBorne[i]->get_Ox(), NightBorne[i]->get_Oy());
                }

            }
        }
        else {
            //savoir si on est en idle ou en run quand le personnage n'est pas en collision
            if (NightBorne[i]->get_Loop_Idle()<0){
                NightBorne[i]->set_Loop_Idle(rand()%200+50);
                NightBorne[i]->set_Random_Idle(rand()%2);
            }
            //pour NightBorne idle
            if (NightBorne[i]->get_Random_Idle() == 0){
                if (Personnage->pos().rx()<NightBorne[i]->pos().rx()+NightBorne[i]->boundingRect().width()/2){
                    NightBorne[i]->idle(1);
                }
                else {
                    NightBorne[i]->idle(-1);
                }
            }
            //pour NightBorne run
            else if (NightBorne[i]->get_Random_Idle() == 1){
                if ((NightBorne[i]->get_Ox() + NightBorne[i]->get_Range())>NightBorne[i]->pos().rx() && (NightBorne[i]->get_Ox() - NightBorne[i]->get_Range())<NightBorne[i]->pos().rx()){
                    NightBorne[i]->setPos(NightBorne[i]->pos().rx() + 4.5*NightBorne[i]->get_Sens_Run(), NightBorne[i]->pos().ry());
                }
                else {
                    NightBorne[i]->set_Sens_Run(NightBorne[i]->get_Sens_Run() * -1);
                    NightBorne[i]->run(-NightBorne[i]->get_Sens_Run());
                    NightBorne[i]->setPos(NightBorne[i]->pos().rx() + 10 * NightBorne[i]->get_Sens_Run(), NightBorne[i]->pos().ry());
                }
                NightBorne[i]->run(-NightBorne[i]->get_Sens_Run());
            }
            NightBorne[i]->set_Loop_Idle(NightBorne[i]->get_Loop_Idle() - 1);
        }
        }
        else {
            NightBorne[i]->death();
        }
    }
}

void MyScene::AnimBulletSorcerer(){
    //Animate bullets for sorcerer and detect collisions
    for (int i = 0; i < bullet.size(); i++){
        bullet[i].first->setPos(bullet[i].first->pos().rx() + 2.5*bullet[i].second, bullet[i].first->pos().ry());
        int check = 0; //check si la balle doit etre enlevée ou pas, à ne pas fair eles les boucles sinon erreur d'index
        for (auto plateforme : plateformes){
            if (bullet[i].first->collidesWithItem(plateforme)){
                if (plateforme->get_tile_code()!=50){
                    check ++;
                }
            }
        }
        if (bullet[i].first->collidesWithItem(Personnage) && check == 0){
            check ++;
            this->hurting_attack = true;
            this->loop = 2;
            MinusOneLife();
            Hit->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/Hit.wav"));
            Hit->play();
            //enlever point de vie au perso et faire animation hurt
        }
        if (check != 0 && bullet.size()!=0){
            removeItem(bullet[i].first);
            bullet.removeAt(i);
            nb_bullet --;
        }
    }
}

void MyScene::PlateformeMove(){
    //Move the differents plateformes
    moduloUpdate = 0;
    if (posPlatMove<=-50){
        sensPlatMove = 1;
    }
    else if (posPlatMove>=50){
        sensPlatMove = -1;
    }
    if (sensPlatMove ==1){
        posPlatMove ++;
    }
    else{
        posPlatMove --;
    }

    for (int i = 0; i  < plateformeMovetoAnim.size(); i++){
        if (i%2 == 0){
            plateformes[plateformeMovetoAnim[i]]->setPos(plateformes[plateformeMovetoAnim[i]]->pos().rx()+posPlatMove/8, plateformes[plateformeMovetoAnim[i]]->pos().ry());
        }
        else {
            plateformes[plateformeMovetoAnim[i]]->setPos(plateformes[plateformeMovetoAnim[i]]->pos().rx()-posPlatMove/8, plateformes[plateformeMovetoAnim[i]]->pos().ry());
        }
    }
}

void MyScene::BouncePlatMove(int indice, int indicefromq){
    //Make the little bounce on the moving plateformes
    float y = plateformes[indice]->get_OriginalY();
    if (plateformeMoveBouncetoAnim[indicefromq].second>5){
        y += (10 - plateformeMoveBouncetoAnim[indicefromq].second);
    }
    else {
        y += plateformeMoveBouncetoAnim[indicefromq].second;
    }
    plateformeMoveBouncetoAnim[indicefromq].second --;
    plateformes[indice]->setPos(plateformes[indice]->pos().rx(), y);
}

void MyScene::jumpParticle(){
    //Creates the jump particles
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect;
    blurEffect->setBlurRadius(100);
    for (int i = 0; i<7; i++){
        QGraphicsEllipseItem *circleItem = new QGraphicsEllipseItem(0, 0, 4, 4);
        circleItem->setPos(5+Personnage->pos().rx()+rand()%(int)2*Personnage->boundingRect().width()/5, Personnage->pos().ry()-5+Personnage->boundingRect().height());
        circleItem->setBrush(QBrush(QColor(249, 231, 159, 128)));
        circleItem->setGraphicsEffect(blurEffect);
        QPen pen(Qt::NoPen);
        circleItem->setPen(pen);
        circleItem->setZValue(4);
        jumpEffect.push_back(circleItem);
        addItem(circleItem);
    }
    can_anim_particle = true;
    loop_anim_particle = 15;
}

void MyScene::animParticle(){
    //Animates the jump particles
    for (int i = 0; i<7; i++){
        float x = jumpEffect[i]->pos().rx();
        float y = jumpEffect[i]->pos().ry();
        if (jumpEffect[i]->pos().ry()<Personnage->pos().ry()+3*Personnage->boundingRect().height()/4){
            y = jumpEffect[i]->pos().ry();
        }
        else{
            y = jumpEffect[i]->pos().ry()+rand()%10-10;
        }
        if (v_X>0){
            x = jumpEffect[i]->pos().rx()+2.5;
        }
        else if (v_X<0) {
            x = jumpEffect[i]->pos().rx()-2.5;
        }
        jumpEffect[i]->setPos(x, y);
    }
    loop_anim_particle --;
}

void MyScene::animChestPiece(){
    //Animate the coin when a chest is open
    QPointF pos_Coin = plateformes[index_chest_anim]->pos();
    if(this->loop_anim_chest_piece<81 && this->loop_anim_chest_piece%8==0){
        QPixmap pix(QString("../qtprojetbase/src/environement/decor/") + QString::QString::number(loop_anim_chest_piece/8) + QString(".png"));
        if (current_lvl == 3){
            pix = ToBlack(pix);
        }
        coinchest->setScale(3);
        coinchest->setPixmap(pix);
    }
    else if (this->loop_anim_chest_piece%8==0){
        QPixmap pix(QString("../qtprojetbase/src/environement/decor/") + QString::QString::number(1) + QString(".png"));
        if (current_lvl == 3){
            pix = ToBlack(pix);
        }
        coinchest->setScale(3);
        coinchest->setPixmap(pix);
        anim_piece_chest = false;
    }
    if (!anim_piece_chest){
        coinchest->setPos(-100,-100);
    }
    else {
        coinchest->setPos(pos_Coin.rx()+plateformes[index_chest_anim]->boundingRect().width()/2, pos_Coin.ry()+plateformes[index_chest_anim]->boundingRect().height()/2 + 15 - loop_anim_chest_piece/3);
    }
    loop_anim_chest_piece++;
}

void MyScene::CheckChest(){
    //Check if the personnage collide with a chest
    int check_collides_chest = 0;
    for (auto plateforme : plateformes){
        if (rect_chest->collidesWithItem(plateforme)){
            if (plateforme->get_tile_code()==67){
                check_collides_chest ++;
                can_open_chest = true;
                index_chest_anim = plateformes.indexOf(plateforme);
            }
        }
    }
    if (check_collides_chest == 0){
        loop_anim_chest = 3;
    }
    else if(loop_anim_chest < 31 && can_open_chest && e_press_for_chest){
        OpenChest();
    }
    else if(loop_anim_chest > 30 && can_open_chest){
        plateformes[index_chest_anim]->set_Value(130);
    }
    if (anim_piece_chest){
        animChestPiece();
    }
}


void MyScene::OpenChest(){
    //Do the animation when the action to open a chest is made
    if (loop_anim_chest%3 == 0){
        QPixmap pix(QString("../qtprojetbase/src/environement/Animated_Chest/Wood_Chest/open") + QString::QString::number(loop_anim_chest/3) + QString(".png"));
        if (current_lvl == 3){
            pix = ToBlack(pix);
        }
        plateformes[index_chest_anim]->setPixmap(pix);
        if (loop_anim_chest == 27){
            anim_piece_chest = true;
            loop_anim_chest_piece = 0;
            piece += rand()%20+10;
        }
    }
    this->loop_anim_chest ++;
}

void MyScene::Background_Parallax(){
    //Update position and opacity of the backgrounds layers
    for (unsigned int i = 0; i < Background.size(); i++) {
        if (i>11 && i<24){
            Background[i]->setOpacity(opacite_Bg);
        }
        if (i>23){
            Background[i]->setPos(Background[i]->pos().rx()-v_X*0.1, Background[i]->pos().ry());
        }
    }
    if(Personnage->pos().rx()>background.width()/4){
        opacite_Bg = (Personnage->pos().rx()-background.width()/4)*0.0004;
    }
}

void MyScene::AnimCompagnion(){
    //Animate the bird with differents actions
    //Si le compagnon est dans le rectangle du perso + check bool si on peut remettre l'anim
    if (abs(Compagnion->pos().rx()-Personnage->pos().rx()) < 300 && abs(Compagnion->pos().ry()-Personnage->pos().ry()) <150 && procheperso==true && pose == false){
        justesortierect = 0;
        // Calculer une nouvelle direction aléatoire avec un certain coefficient d'inertie
        float angleajouter = 0;
        if(changementangle>75){
            vitCompagnonY = 1 *rand() % 3 - 1;
            vitCompagnonX = 1 *rand() % 2 == 0 ? -1 : 1;
            //qDebug()<<vitCompagnonX<<vitCompagnonY;
            changementangle = 0;
            if(vitCompagnonX==0 || vitCompagnonY==0){
                vitCompagnonX = 0;
                vitCompagnonY = 0;
            }
        }
        if (vitCompagnonX>0){
            compagnon_back = false;
            compagnon_run = true;
        }
        else if (vitCompagnonX<0){
            compagnon_run = false;
            compagnon_back = true;
        }
        else {
            compagnon_run = true;
        }
        // Déplacer l'objet en fonction de la nouvelle vitesse
        Compagnion->setPos(Compagnion->pos().rx() + vitCompagnonX/2, Compagnion->pos().ry() + vitCompagnonY/2);
        changementangle ++;
        //detection de collision avec le sol
        for (auto plateforme : plateformes){
            if (Compagnion->collidesWithItem(plateforme)){
                if (plateforme->get_tile_code()==2 || plateforme->get_tile_code()==4 || plateforme->get_tile_code()==5 || plateforme->get_tile_code()==15 || plateforme->get_tile_code()==20 || plateforme->get_tile_code()==21 || plateforme->get_tile_code()==22 || plateforme->get_tile_code()==28 || plateforme->get_tile_code()==29 || plateforme->get_tile_code()==30 || plateforme->get_tile_code()==34 || plateforme->get_tile_code()==35 || plateforme->get_tile_code()==36){ // collide Haut
                    gap_Y = Compagnion->pos().ry() - plateforme->pos().ry();
                    if (gap_Y!=0){
                        Compagnion->setPos(plateforme->pos().rx(), plateforme->pos().ry()-2*Compagnion->boundingRect().height());

                    }
                    pose = true;
                }
            }
        }

    }
    else if(pose == true){
        Compagnion->setPos(Compagnion->pos().rx(), Compagnion->pos().ry());
        if(abs(Compagnion->pos().rx()-Personnage->pos().rx()) > 300 || abs(Compagnion->pos().ry()-Personnage->pos().ry()) >150){
            pose = false;
        }
        if (picorer <400){
            picorer++;
            boucle_picorer = 1;
        }
    }
    //Si le compagnon est en dehors [[ ajouter bool pour le remettre pret du perso
    else {
        if (v_X>0){
            compagnon_back = false;
            compagnon_run = true;
        }
        else if(v_X<0){
            compagnon_run = false;
            compagnon_back = true;
        }
        else{
            compagnon_run = true;
        }
        pose = false;
        procheperso = false;
        if (justesortierect == 0) {
            CreateLigne(tabComp, 50, Personnage, Compagnion);
        }
        if(abs(Compagnion->pos().rx()-Personnage->pos().rx()) < 60 && abs(Compagnion->pos().ry()-Personnage->pos().ry()) <60){
            procheperso = true;
        }
        else if (justesortierect > 29){
            CreateLigne(tabComp, 50, Personnage, Compagnion);
            justesortierect = 0;
        }
        if (justesortierect < 30) {
            Compagnion->setPos(tabComp[justesortierect]->rx(), tabComp[justesortierect]->ry());
            justesortierect++;
        }
    }

}

void MyScene::PlatformeFall(int indice, int indicefromq){
    //Break a plateforme
    float x = plateformes[indice]->get_OriginalX()+(rand()%3-1);
    float y = plateformes[indice]->get_OriginalY()+(rand()%3-1);
    plateformeFalltoAnim[indicefromq].second --;
    plateformes[indice]->setPos(x, y);
}

//On gère les collisions des plateformes et personnages en aggissant en conséquence
void MyScene::Collision(){
    //Check all the collisions with the personnage
    QPointF pos = Personnage->pos();
    int indice = 0;
    int indice18 = 0;
    for (auto cp : CheckP){
        if (Personnage->collidesWithItem(cp)){
            if (!cp->get_active()){
                cp->set_Active(true);
                RespawnPoint = cp->get_Point();
            }
        }
    }
    for (auto plateforme : plateformes){
        if (opacTile.size()!=0){
            //la majorité des tiles sont en opacité 0 donc pour de meilleures performances je fais deja une premiere selection des plateformes à mettre opacité 0
            if (abs(plateforme->pos().rx()-Personnage->pos().rx())>500 || abs(plateforme->pos().ry()-Personnage->pos().ry())>260){
                plateforme->setOpacity(0);
            }
            else if (opacTile[0]->collidesWithItem(plateforme)){
                plateforme->setOpacity(1);
            }
            else if (opacTile[1]->collidesWithItem(plateforme)){
                plateforme->setOpacity(0.8);
            }
            else if (opacTile[2]->collidesWithItem(plateforme)){
                plateforme->setOpacity(0.6);
            }
            else if (opacTile[3]->collidesWithItem(plateforme)){
                plateforme->setOpacity(0.4);
            }
            else if (opacTile[4]->collidesWithItem(plateforme)){
                plateforme->setOpacity(0.25);
            }
            else if (opacTile[5]->collidesWithItem(plateforme)){
                plateforme->setOpacity(0.175);
            }
            else if (opacTile[6]->collidesWithItem(plateforme)){
                plateforme->setOpacity(0.125);
            }
            else if (opacTile[7]->collidesWithItem(plateforme)){
                plateforme->setOpacity(0.09);
            }
            else if (opacTile[8]->collidesWithItem(plateforme)){
                plateforme->setOpacity(0.07);
            }
            else if (opacTile[9]->collidesWithItem(plateforme)){
                plateforme->setOpacity(0.05);
            }
            else {
                plateforme->setOpacity(0);
            }
        }
            if (Personnage->collidesWithItem(plateforme) && !changelevel){ // IF GAP < 0 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                if (v_Y>30 && plateforme->get_tile_code()!=16 && plateforme->get_tile_code()!=51 && !hurt_fall){ //20
                    puissanceshake = v_Y-25; //8 + v_Y-19
                    shaking  = true;
                    hurt_fall = true;
                    loop = 1;
                    MinusOneLife();
                    HighFall->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/highfall.wav"));
                    HighFall->play();
                }
                QPointF pos2 = plateforme->pos();
                if (plateforme->get_tile_code()==19){
                    QPair<int, int> myPair(indice, 40);
                    bool dedans = false;
                    for (int i = 0; i < plateformeFalltoAnim.size(); i++) {
                            if (plateformeFalltoAnim[i].first == myPair.first) {
                                dedans = true;
                            }
                        }
                    if (dedans == false){
                        plateformeFalltoAnim.push_back(myPair);
                    }
                }
                if (plateforme->get_tile_code()==18){
                    QPair<int, int> myPair(indice, 10);
                    bool dedans = false;
                    for (int i = 0; i < plateformeMoveBouncetoAnim.size(); i++) {
                            if (plateformeMoveBouncetoAnim[i].first == myPair.first) {
                                dedans = true;
                            }
                        }
                    if (dedans == false){
                        plateformeMoveBouncetoAnim.push_back(myPair);
                    }
                    indice18 = indice;
                }
                if (plateforme->get_tile_code()==50){ // collide Pièces
                    piece +=1;
                    plateforme->setPos(-100, plateforme->pos().ry());
                    //set Media ici car si trop de coin ramassé en meme temps ça ne bug pas
                    coinSound->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/coin2.wav"));
                    coinSound->play();
                }
                if (plateforme->get_tile_code()==2 || plateforme->get_tile_code()==4 || plateforme->get_tile_code()==5 || plateforme->get_tile_code()==21 || plateforme->get_tile_code()==29 || plateforme->get_tile_code()==35 || plateforme->get_tile_code()==22 || plateforme->get_tile_code()==30 || plateforme->get_tile_code()==20 || plateforme->get_tile_code()==28 || plateforme->get_tile_code()==34 || plateforme->get_tile_code()==36){ // collide Haut
                    v_Y = 0;
                    gap_Y = pos.ry()+Personnage->boundingRect().height()-pos2.ry();
                    if(pos.ry()>pos2.ry()){
                        gap_Y = pos.ry() - pos2.ry();
                        if (gap_Y!=0){
                            Personnage->setPos(pos.rx(), pos.ry()+gap_Y);
                        }
                    }
                    else if (gap_Y!=0){
                        Personnage->setPos(pos.rx(), pos.ry()-gap_Y);
                    }
                    is_jumping = false;
                    is_colisionning_top = false;
                    is_colisionning_bottom = true;
                }
                if (plateforme->get_tile_code()==3 || plateforme->get_tile_code()==25){ // collide Bas
                    v_Y = 0;
                    gap_Y = pos.ry() - pos2.ry();
                    if (gap_Y!=0){
                        Personnage->setPos(pos.rx(), pos.ry()+gap_Y);
                    }
                    is_jumping = true;
                    is_colisionning_top = true;
                    is_colisionning_bottom = false;
                }
                if (plateforme->get_tile_code()==4 ){ // collide Haut gauche
                    is_colisionning_top = false;
                    is_colisionning_bottom = true;
                }
                if (plateforme->get_tile_code()==5 ){ // collide Haut droit
                    is_colisionning_top = false;
                    is_colisionning_bottom = true;
                }
                if (plateforme->get_tile_code()==6 || plateforme->get_tile_code()==23){ // collide Bas gauche
                    is_jumping = true;
                    is_colisionning_top = true;
                    is_colisionning_bottom = false;
                }
                if (plateforme->get_tile_code()==7 || plateforme->get_tile_code()==24){ // collide Bas droit
                    is_jumping = true;
                    is_colisionning_top = true;
                    is_colisionning_bottom = false;
                }
                if (plateforme->get_tile_code()==8 || plateforme->get_tile_code()==26){ // collide Gauche
                    v_X = 0;
                    gap_X = pos.rx()+Personnage->boundingRect().width() - pos2.rx();
                    if(gap_X > 0){
                        Personnage->setPos(pos.rx()-gap_X, pos.ry());
                    }
                    vitessedroite = 0;
                    is_colisionning_right = true;
                    is_colisionning_left = false;
                }
                if (plateforme->get_tile_code()==9 || plateforme->get_tile_code()==27){ // collide Droite
                    v_X = 0;
                    gap_X = pos.rx() - pos2.rx()-40;
                    if(gap_X < 0){
                        Personnage->setPos(pos.rx()-gap_X, pos.ry());
                    }
                    vitessegauche = 0;
                    is_colisionning_right = false;
                    is_colisionning_left = true;
                }
                if (plateforme->get_tile_code()==14 || plateforme->get_tile_code()==18 || plateforme->get_tile_code()==19 || plateforme->get_tile_code()==31 || plateforme->get_tile_code()==32 || plateforme->get_tile_code()==33){ // collide Plateforme
                    v_Y = 0;
                    if (pos.ry()+Personnage->boundingRect().height()/2 > pos2.ry()){
                        gap_Y = pos.ry() - pos2.ry();
                        if (gap_Y!=0){
                            if (current_lvl == 3){
                                Personnage->setPos(pos.rx(), pos.ry()-gap_Y+Personnage->boundingRect().height()/2);
                            }
                            else{
                                Personnage->setPos(pos.rx(), pos.ry()-gap_Y+Personnage->boundingRect().height()/3);
                            }
                        }
                    }
                    else{
                        gap_Y = pos.ry()+Personnage->boundingRect().height()-pos2.ry();
                        if (gap_Y!=0){
                            Personnage->setPos(pos.rx(), pos.ry()-gap_Y);
                        }
                    }
                    is_jumping = false;
                    is_colisionning_top = false;
                    is_colisionning_bottom = true;
                }
                if (plateforme->get_tile_code()==15){ // collide Box
                    v_Y = 0;
                    gap_Y = pos.ry()+Personnage->boundingRect().height()-pos2.ry();
                    Personnage->setPos(pos.rx(), pos.ry()-gap_Y);
                    is_jumping = false;
                    is_colisionning_top = false;
                    is_colisionning_bottom = true;
                }
                if ((plateforme->get_tile_code()==41 || plateforme->get_tile_code()==42 || plateforme->get_tile_code()==43) && !hurting_attack){ // collide pics
                    hurting_attack = true;
                    this->loop = 2;
                    MinusOneLife();
                    Hit->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/Hit.wav"));
                    Hit->play();
                    if ((Personnage->pos().rx()+10<plateforme->pos().rx()) && (plateforme->get_tile_code() == 42 || plateforme->get_tile_code() == 43)){
                        Personnage->setPos(Personnage->pos().rx() - 30,Personnage->pos().ry());
                    }
                    else if ((Personnage->pos().rx()+10>=plateforme->pos().rx()) && (plateforme->get_tile_code() == 42 || plateforme->get_tile_code() == 43)){
                        Personnage->setPos(Personnage->pos().rx() + 30,Personnage->pos().ry());
                    }
                    else if (plateforme->get_tile_code()==41){
                        Personnage->setPos(Personnage->pos().rx(), Personnage->pos().ry() + 30);
                    }
                }
                if (plateforme->get_tile_code()==16){ // collide jump
                    v_Y = PUISSANCE_SAUT*2;
                    is_jumping = true;
                    is_colisionning_bottom = false;
                    espace_Pressed = true;
                }
            }
            else {
            }
            indice ++;
        }
    boolForPlatMoveAndPerso[1] = boolForPlatMoveAndPerso [0];
    if (indice18>0){
        boolForPlatMoveAndPerso [0] = QPair<bool, int>(true, indice18);
    }
    else{
        boolForPlatMoveAndPerso [0] = QPair<bool, int>(false, indice18);
    }
    //On gère les données renvoyées par les bool --- Explications dans la doc
    if(!is_colisionning_right){
        vitessedroite = 4;
    }
    if(!is_colisionning_left){
        vitessegauche = 4;
    }
    // on met un timeout pour ne pas avoir un bug qui nous ferait rentrer dans les murs si l'utilisateur reste appuyé sur la barre espace, 15*15 = 225 ms, ça ne se ressent pas dans l'experience de jeu
    if (timeout_espace>20){
        espace_Pressed = false;
    }
    timeout_espace++;
}

void MyScene::Slide(){
    //Animate the personnage when sliding
    QTransform transform;
    transform.scale(sens_slide, 1);

    if (loop%6 == 0 && loop<25) {
        is_sliding = true;
        QPixmap pixmap(ImagesSlidePerso[(loop/6) - 1]);
        pixmap = pixmap.transformed(transform);
        Personnage->setPixmap(pixmap);
    }
    else if (loop>24) {
        loop = 1;
    }
    loop ++;
    temps_slide --;
}

void MyScene::ArcAttack(){
    //Animate the personnage with the movement of the arcattack
    QTransform transform;
    QPointF curseur = QCursor::pos(); //position du curseur
    //position de la fenetre pour ensuite calculer pos curseur dans la scene
    QPoint leftBorder = views()[0]->mapToGlobal(QPoint(0, 0));
    int cote = 0;
    if (elementcentered->pos().rx()<640){
        if (curseur.rx()-leftBorder.rx()>Personnage->pos().rx()+Personnage->boundingRect().width()/2){
            cote = 0;
        }
        else {
            cote = 1;
        }
    }
    else if (elementcentered->pos().rx()>4643){
        if (curseur.rx()-leftBorder.rx()<Personnage->pos().rx() - 4003){
            cote = 1;
        }
        else {
            cote = 0;
        }
    }
    else {
        if (curseur.rx()-leftBorder.rx()<640){
            cote = 1;
        }
        else {
            cote = 0;
        }
    }
    if (cote == 0){
        transform.scale(-1, 1);
        if (loop == 30){
            QTransform transform;
            transform.scale(-1, 1);
            QPixmap pix(QString("../qtprojetbase/src/character/character1/ArcAttack/fleche1.png"));
            if (current_lvl == 3){
                pix = ToBlack(pix);
            }
            pix = pix.transformed(transform);
            QPair<QGraphicsPixmapItem*, int> myPair(new QGraphicsPixmapItem(pix), 1);
            fleche.push_back(myPair);
            fleche.last().first->setScale(2);
            fleche.last().first->setZValue(13);
            fleche.last().first->setPos(Personnage->pos().rx()+Personnage->boundingRect().width()-fleche.last().first->boundingRect().width()/2, Personnage->pos().ry() + 30);
            gravitefleche.push_back(0.0);
            rotationfleche.push_back(0.0);
            addItem(fleche.last().first);
        }
    }
    else {
        transform.scale(1, 1);
        if (loop == 30){
            QPixmap pix(QString("../qtprojetbase/src/character/character1/ArcAttack/fleche1.png"));
            if (current_lvl == 3){
                pix = ToBlack(pix);
            }
            QPair<QGraphicsPixmapItem*, int> myPair(new QGraphicsPixmapItem(pix), -1);
            fleche.push_back(myPair);
            fleche.last().first->setScale(2);
            fleche.last().first->setZValue(13);
            fleche.last().first->setPos(Personnage->pos().rx()-fleche.last().first->boundingRect().width()/2, Personnage->pos().ry() + 30);
            gravitefleche.push_back(0.0);
            rotationfleche.push_back(0.0);
            addItem(fleche.last().first);
        }
    }
    if (loop%6 == 0 && loop<55) {
        QPixmap pixmap(ImagesArcPerso[(loop/6) - 1]);
        pixmap = pixmap.transformed(transform);
        Personnage->setPixmap(pixmap);
        if (loop == 30){
            Bow->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/Bow.wav"));
            Bow->play();
        }
    }
    else if (loop>54) {
        loop = 1;
    }
    loop ++;
}

void MyScene::AnimFleche(){
    //Animate each arrow with a rotation and a position
    for (int i = 0; i < fleche.size(); i++){
        gravitefleche[i] += 0.01;
        fleche[i].first->setPos(fleche[i].first->pos().rx() + 8*fleche[i].second, fleche[i].first->pos().ry() + gravitefleche[i]);
        if (fleche[i].second == 1 && rotationfleche[i]<45){
            rotationfleche[i] += 0.11;
            fleche[i].first->setRotation(rotationfleche[i]);
        }
        else if (rotationfleche[i]>-45) {
            rotationfleche[i] -= 0.12;
            fleche[i].first->setRotation(rotationfleche[i]);
        }
        int check = 0; //check si la balle doit etre enlevée ou pas, à ne pas faire les boucles sinon erreur d'index
        for (auto plateforme : plateformes){
            if (fleche[i].first->collidesWithItem(plateforme)){
                if (plateforme->get_tile_code()!=50){
                    check ++;
                }
            }
        }
        for (int j = 0; j < Sorcerer.size(); j++){
            if (fleche[i].first->collidesWithItem(Sorcerer[j]) && check == 0 && !Sorcerer[j]->get_Death()){
                if (Sorcerer[j]->get_Life()-27>0){
                    Sorcerer[j]->set_Life(Sorcerer[j]->get_Life()-27);
                    Sorcerer[j]->set_Hurt(true);
                    Sorcerer[j]->set_Loop(3);
                    if (Personnage->pos().rx()+Personnage->boundingRect().width()/2 > Sorcerer[j]->pos().rx()){
                        Sorcerer[j]->set_Sens_Hurt(-1);
                    }
                    else {
                        Sorcerer[j]->set_Sens_Hurt(1);
                    }
                }
                else {
                    Sorcerer[j]->bar->setZValue(-2);
                    Sorcerer[j]->healthdeco->setZValue(-2);
                    Sorcerer[j]->set_Death(true);
                    Sorcerer[j]->set_Loop(4);
                }
                Hit->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/Hit.wav"));
                Hit->play();
                check ++;
            }
        }
        for (int j = 0; j < Wolves.size(); j++){
            if (fleche[i].first->collidesWithItem(Wolves[j]) && check == 0 && !Wolves[j]->get_Death()){
                if (Wolves[j]->get_Life()-18>0){
                    Wolves[j]->set_Life(Wolves[j]->get_Life()-18);
                    Wolves[j]->set_Hurt(true);
                    Wolves[j]->set_Loop(3);
                    if (Personnage->pos().rx()+Personnage->boundingRect().width()/2 > Wolves[j]->pos().rx()){
                        Wolves[j]->set_Sens_Hurt(-1);
                    }
                    else {
                        Wolves[j]->set_Sens_Hurt(1);
                    }
                }
                else {
                    Wolves[j]->bar->setZValue(-2);
                    Wolves[j]->healthdeco->setZValue(-2);
                    Wolves[j]->set_Death(true);
                    Wolves[j]->set_Loop(4);
                }
                Hit->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/Hit.wav"));
                Hit->play();
                check ++;
            }
        }
        for (int j = 0; j < NightBorne.size(); j++){
            if (fleche[i].first->collidesWithItem(NightBorne[j]) && check == 0 && !NightBorne[j]->get_Death()){
                if (NightBorne[j]->get_Life()-15>0){
                    NightBorne[j]->set_Life(NightBorne[j]->get_Life()-15);
                    NightBorne[j]->set_Hurt(true);
                    NightBorne[j]->set_Loop(3);
                    if (Personnage->pos().rx()+Personnage->boundingRect().width()/2 > NightBorne[j]->pos().rx()){
                        NightBorne[j]->set_Sens_Hurt(-1);
                    }
                    else {
                        NightBorne[j]->set_Sens_Hurt(1);
                    }
                }
                else {
                    NightBorne[j]->bar->setZValue(-2);
                    NightBorne[j]->healthdeco->setZValue(-2);
                    NightBorne[j]->set_Death(true);
                    NightBorne[j]->set_Loop(4);
                }
                Hit->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/Hit.wav"));
                Hit->play();
                check ++;
            }
        }
        if (abs(fleche[i].first->pos().rx()-Personnage->pos().rx())>1000){
            check ++;
        }
        if (check != 0){
            gravitefleche.removeAt(i);
            rotationfleche.removeAt(i);
            removeItem(fleche[i].first);
            fleche.removeAt(i);
        }
    }
}


void MyScene::ShakeView(){
    //Shake the view if the Personnage fall from to high
    qreal originalX = elementcentered->pos().rx();
    qreal originalY = elementcentered->pos().ry();
    int maxDisplacement = ceil(30.0* ((puissanceshake)/10.0));
    qreal dx = 0;
    qreal dy = (qreal)(rand() % (maxDisplacement * 2) - maxDisplacement) / 10;
    elementcentered->setPos(originalX + dx, originalY + dy);
    elapsedMs ++;
}

//On gère les event clavier
void MyScene::keyPressEvent(QKeyEvent* event){
    //Key events
    if(event->key() == Qt::Key_Q) { // appui sur la touche Q du clavier
        v_X += -vitessegauche; //-8
        is_backing = true;
        is_colisionning_right = false;
        if(!event->isAutoRepeat()){
            nbkeypress++;
        }
        if (is_colisionning_left){
            is_backing = false;
        }
        if (current_lvl == 0 && isInTuto){
            Q->keyPressed();
            secondQ->keyPressed();
        }
    }
    if(event->key() == Qt::Key_D) { // appui sur la touche D du clavier
        v_X += vitessedroite; //8
        is_colisionning_left = false;
        is_running = true;
        if(!event->isAutoRepeat()){
            nbkeypress++;
        }
        if (is_colisionning_right){
            is_running = false;
        }
        if (current_lvl == 0 && isInTuto){
            D->keyPressed();
            secondD->keyPressed();
        }
    }
    if(event->key() == Qt::Key_Space && espace_Pressed == false){
        if (is_colisionning_bottom){
            jumpParticle();
            timeout_espace = 1;
            v_Y = PUISSANCE_SAUT;
            is_jumping = true;
            is_colisionning_bottom = false;
            espace_Pressed = true;
            if (plateformeMoveBouncetoAnim.size() != 0){
                for (int i = 0; i<plateformeMoveBouncetoAnim.size(); i++){
                    plateformeMoveBouncetoAnim.removeAt(i);
                }
            }
            plateformeMoveBouncetoAnim.clear();
        }
        if (current_lvl == 0  && isInTuto){
            SPACE->keyPressed();
        }
    }
    if(event->key() == Qt::Key_E && can_open_chest){
        e_press_for_chest = true;
    }
    if(event->key() == Qt::Key_E){
        if (current_lvl == 0  && isInTuto){
            E->keyPressed();
            secondE->keyPressed();
        }
        can_anim_fin = true;
    }
    if(event->key() == Qt::Key_R) { // appui sur la touche R du clavier
        Personnage->setPos(RespawnPoint.rx(), RespawnPoint.ry()-150);
        is_colisionning_left = false;
        is_colisionning_right = false;
        is_colisionning_top = false;
        is_colisionning_bottom = false;
        //
        is_falling = true;
        is_jumping = true;
        //
        posPlatMove = 0;
        sensPlatMove = -1;
        if (current_lvl == 0  && isInTuto){
            R->keyPressed();
        }

        for (unsigned int i = 24; i < Background.size(); i++) {
            Background[i]->setPos(PosArbreBack[i-24].rx(), PosArbreBack[i-24].ry());//recuperer les coordonnées à l'init puis réafecter
        }
        for (int i = 0; i  < plateformeMoveBouncetoAnim.size(); i++){
            plateformeMoveBouncetoAnim.removeAt(i);
        }
        for (int i = 0; i  < plateformeMovetoAnim.size(); i++){
            plateformes[plateformeMovetoAnim[i]]->setPos(plateformes[plateformeMovetoAnim[i]]->get_OriginalX(), plateformes[plateformeMovetoAnim[i]]->get_OriginalY());
        }
        plateformeMoveBouncetoAnim.clear();
        opacite_Bg = 0;
        v_Y = 0;
    }
    if(event->key() == Qt::Key_T) {
        if (!isInMenu){
            if (!pauseGame){
                timer->stop();
                GameIsPaused();
            }
        }
    }
    if (event->key() == Qt::Key_Shift && is_running && !is_sliding){
        sens_slide = -1;
        Slide();
        puissance_slide = 2;
        loop = 1;
        is_sliding = true;
        can_hurt_slide = true;
        SlideSound->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/grassslide.wav"));
        SlideSound->play();
    }
    if (event->key() == Qt::Key_Shift && is_backing && !is_sliding){
        sens_slide = 1;
        Slide();
        loop = 1;
        puissance_slide = 2;
        is_sliding = true;
        can_hurt_slide = true;
        SlideSound->setMedia(QUrl("../qtprojetbase/src/Sound/Effect/grassslide.wav"));
        SlideSound->play();
    }
    if (event->key() == Qt::Key_Shift){
        if (current_lvl == 0  && isInTuto){
            SHIFT->keyPressed();
        }
    }
}

//On gère la fin des event clavier
void MyScene::keyReleaseEvent(QKeyEvent* event){
    //Key events
    if(event->key() == Qt::Key_Q) { // On relache la touche Q du clavier
        v_X += vitessegauche; //8
        is_backing = false;
        if (!event->isAutoRepeat()){
            nbkeypress--;
        }
        if (current_lvl == 0 && isInTuto){
            Q->keyReleased();
            secondQ->keyReleased();
        }
    }
    else if(event->key() == Qt::Key_D) { // On relache la touche D du clavier
        v_X += -vitessedroite; //-8
        is_running = false;
        if (!event->isAutoRepeat()){
            nbkeypress--;
        }
        if (current_lvl == 0  && isInTuto){
            D->keyReleased();
            secondD->keyReleased();
        }
    }
    if(event->key() == Qt::Key_Space){
        is_falling = false;
        if (current_lvl == 0 && isInTuto){
            SPACE->keyReleased();
        }
    }
    if(event->key() == Qt::Key_R){
        if (current_lvl == 0 && isInTuto){
            R->keyReleased();
        }
    }
    if(event->key() == Qt::Key_E){
        e_press_for_chest = false;
        if (current_lvl == 0 && isInTuto){
            E->keyReleased();
            secondE->keyReleased();
        }
        can_anim_fin = false;
    }
    if (event->key() == Qt::Key_Shift && is_sliding){

    }
    if (event->key() == Qt::Key_Shift){
        if (current_lvl == 0 && isInTuto){
            SHIFT->keyReleased();
        }
    }

}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    //Mouse events
    if (event->button() == Qt::RightButton){
        is_arcing = true;
    }
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    //Mouse events
    if (event->button() == Qt::RightButton){
        is_arcing = false;
    }
}

//Animation des personnages de la scene
void MyScene::Animation(){
    //Animation of the coin, the bird and the Personnage
    for (auto plateforme : plateformes)
    {
        if (plateforme->get_tile_code()==50){
            QPointF pos_Coin = plateforme->pos();
            if(this->loop_Coin<81 && this->loop_Coin%8==0){ // 41   4
                QPixmap pix(QString("../qtprojetbase/src/environement/decor/") + QString::QString::number(loop_Coin/8) + QString(".png"));
                if (current_lvl == 3){
                    pix = ToBlack(pix);
                }
                plateforme->setScale(3);
                plateforme->setPixmap(pix);
                //enlever le "coin" pour prendre les images non pixelisées
            }
            else if (this->loop_Coin%8==0){
                QPixmap pix(QString("../qtprojetbase/src/environement/decor/") + QString::QString::number(1) + QString(".png"));
                if (current_lvl == 3){
                    pix = ToBlack(pix);
                }
                loop_Coin = 8;
                plateforme->setScale(3);
                plateforme->setPixmap(pix);
            }
            plateforme->setPos(pos_Coin.rx(), pos_Coin.ry() + 0.5575*sin(angle)); //1.15
        }
    }
    angle += PI/60; //30
    loop_Coin++;

    //compagnion
    if(pose){
        if (picorer == 400 && boucle_picorer<111 && boucle_picorer%10==0){
            QPixmap pix(QString("../qtprojetbase/src/environement/companion/idle/picore") + QString::QString::number(boucle_picorer/10) + QString(".png"));
            if (current_lvl == 3){
                pix = ToBlack(pix);
            }
            Compagnion->setPixmap(pix);
        }
        else if (boucle_picorer == 1 && picorer == 400){
            QPixmap pix(QString("../qtprojetbase/src/environement/companion/idle/picore") + QString::QString::number(1) + QString(".png"));
            if (current_lvl == 3){
                pix = ToBlack(pix);
            }
            Compagnion->setPixmap(pix);
        }
        else if (picorer == 400 && boucle_picorer>111){
            boucle_picorer = 1;
            picorer=0;
        }
        else if (this->anim_compagnon<21 && this->anim_compagnon%20== 0){
            QPixmap pix(QString("../qtprojetbase/src/environement/companion/idle/idle") + QString::QString::number(1) + QString(".png"));
            if (current_lvl == 3){
                pix = ToBlack(pix);
            }
            Compagnion->setPixmap(pix);
        }
        else if(this->anim_compagnon%20== 0){
            QPixmap pix(QString("../qtprojetbase/src/environement/companion/idle/idle") + QString::QString::number(2) + QString(".png"));
            if (current_lvl == 3){
                pix = ToBlack(pix);
            }
            Compagnion->setPixmap(pix);
            anim_compagnon = 1;
        }
        this->boucle_picorer++;
        this->anim_compagnon++;
    }
    else if(compagnon_run){
        if (this->anim_compagnon<32 && this->anim_compagnon%4== 0){
            QPixmap pix(QString("../qtprojetbase/src/environement/companion/fly_run/fly") + QString::QString::number(anim_compagnon/4) + QString(".png"));
            if (current_lvl == 3){
                pix = ToBlack(pix);
            }
            Compagnion->setPixmap(pix);
        }
        else if(this->anim_compagnon%4== 0){
            QPixmap pix(QString("../qtprojetbase/src/environement/companion/fly_run/fly") + QString::QString::number(anim_compagnon/4) + QString(".png"));
            if (current_lvl == 3){
                pix = ToBlack(pix);
            }
            Compagnion->setPixmap(pix);
            anim_compagnon = 1;
        }
        this->anim_compagnon++;
    }
    else if (compagnon_back){
        if (this->anim_compagnon<32 && this->anim_compagnon%4== 0){
            QPixmap pix(QString("../qtprojetbase/src/environement/companion/fly_back/fly") + QString::QString::number(anim_compagnon/4) + QString(".png"));
            if (current_lvl == 3){
                pix = ToBlack(pix);
            }
            Compagnion->setPixmap(pix);
        }
        else if(this->anim_compagnon%4== 0){
            QPixmap pix(QString("../qtprojetbase/src/environement/companion/fly_back/fly") + QString::QString::number(anim_compagnon/4) + QString(".png"));
            if (current_lvl == 3){
                pix = ToBlack(pix);
            }
            Compagnion->setPixmap(pix);
            anim_compagnon = 1;
        }
        this->anim_compagnon++;
    }

    if (!is_sliding && !is_arcing){
    // Personnage
    if (hurting_attack){
        if (this->loop<15 && this->loop%2==0){ // 58    3
            QTransform transform;
            transform.scale(-1, 1);
            QPixmap pix(QString("../qtprojetbase/src/character/character1/HurtAttack/hurt") + QString::QString::number(loop/2) + QString(".png"));
            QPixmap scaledPixmap = pix.scaled(pix.width() * 2, pix.height() * 2);
            scaledPixmap = scaledPixmap.transformed(transform);
            Personnage->setPixmap(scaledPixmap);
        }
        if (loop<15){
            this->loop++;
        }
        else {
            hurting_attack = false;
        }
    }
    else if(hurt_fall){
        if (this->loop<8){
            Personnage->setPixmap(ImagesHurtPerso[loop -1]);
        }
        else {
            Personnage->setPixmap(ImagesHurtPerso[0]);
            hurt_fall = false;
        }
        this->loop ++;
    }
    else if(is_jumping){
        if (v_X<0){
            if (this->loop<114 && this->loop%6==0){
                Personnage->setPixmap(ImagesJumpLeftPerso[loop/6 -1]);
            }
            else if (this->loop%6==0){
                Personnage->setPixmap(ImagesJumpLeftPerso[0]);
                loop = 6;
            }
            this->loop ++;
        }else{
            if (this->loop<114 && this->loop%6==0){
                Personnage->setPixmap(ImagesJumpRightPerso[loop/6 -1]);
            }
            else if (this->loop%6==0){
                Personnage->setPixmap(ImagesJumpRightPerso[0]);
                loop = 6;
            }
            this->loop ++;
        }
    }
    else if(is_running){
        if (this->loop<49 && this->loop%2== 0){
            Personnage->setPixmap(ImagesRunPerso[loop/2 -1]);
        }
        else if (this->loop%2==0){
            Personnage->setPixmap(ImagesRunPerso[0]);
            loop = 2;
        }
        this->loop ++;
    }
    else if(is_backing){
        if (this->loop<50 && this->loop%2== 0){
            Personnage->setPixmap(ImagesBackPerso[loop/2 -1]);
        }
        else if (this->loop%2==0){
            Personnage->setPixmap(ImagesBackPerso[0]);
            loop = 2;
        }
        this->loop ++;
    }
    else{
        if (this->loop<108 && this->loop%6==0){
            Personnage->setPixmap(ImagesIdlePerso[loop/6 -1]);
        }
        else if (this->loop%6==0){
            Personnage->setPixmap(ImagesIdlePerso[0]);
            loop = 6;
        }
        this->loop ++;
    }
    }
}

void MyScene::drawBackground(QPainter *painter, const QRectF &rect) {
    //Draw the background of the scene
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}
MyScene::~MyScene() {
    //delete the scene
    delete timer;
    delete Personnage;
    delete Compagnion;
    delete elementcentered;
    delete rect_chest;
    ImagesRunPerso.clear();
    ImagesRunPerso.squeeze();
    ImagesBackPerso.clear();
    ImagesBackPerso.squeeze();
    ImagesJumpRightPerso.clear();
    ImagesJumpRightPerso.squeeze();
    ImagesJumpLeftPerso.clear();
    ImagesJumpLeftPerso.squeeze();

    ImagesIdlePerso.clear();
    ImagesIdlePerso.squeeze();
    ImagesHurtPerso.clear();
    ImagesHurtPerso.squeeze();
    plateformes.clear();
    plateformes.squeeze();
    shadow.clear();
    shadow.squeeze();
    jumpEffect.clear();
    jumpEffect.squeeze();

    Background.clear();
    Background.squeeze();
    PosArbreBack.clear();
    PosArbreBack.squeeze();
    plateformeFalltoAnim.clear();
    plateformeFalltoAnim.squeeze();
    plateformeMoveBouncetoAnim.clear();
    plateformeMoveBouncetoAnim.squeeze();
    plateformeMovetoAnim.clear();
    plateformeMovetoAnim.squeeze();
    delete[] *tabComp;
    delete[] *tabElementcentered;

}
