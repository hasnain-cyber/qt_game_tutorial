#include "game.h"

#include <QWidget>
#include <score.h>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QBrush>
#include <QImage>

Game::Game(QWidget *parent) {
    scene = new QGraphicsScene();

    player = new Player();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);

    scene->setSceneRect(0, 0, 800, 600);
    scene->setBackgroundBrush(QBrush(QImage(":/images/bg.png")));

    player->setPos(width()/2, height() - player->pixmap().height());

    // spawn enemies
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    timer->start(2000);

    // create the score
    score = new Score();
    scene->addItem(score);

    // create health
    health = new Health();
    health->setPos(health->x(), health->y() + 25);
    scene->addItem(health);

    // play bg music
    QMediaPlayer *music = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput();
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl("qrc:/sounds/game_bg.mp3"));
    audioOutput->setVolume(50);
    music->play();
}
