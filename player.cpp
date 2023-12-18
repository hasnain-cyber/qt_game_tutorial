#include "player.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <bullet.h>
#include <enemy.h>
#include <QDebug>
#include <QAudioOutput>

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent) {
    bulletSound = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput();
    bulletSound->setAudioOutput(audioOutput);
    bulletSound->setSource(QUrl("qrc:/sounds/laser_gun_sound_effect.mp3"));
    audioOutput->setVolume(50);

    QPixmap tempPixMap = QPixmap(":/images/player.png");
    setPixmap(tempPixMap.scaled(tempPixMap.size() * 0.1));
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        if (x() > 0) setPos(x() - 10, y());
    } else if (event->key() == Qt::Key_Right) {
        if (x() + pixmap().width() < scene()->width()) setPos(x() + 10, y());
    } else if (event->key() == Qt::Key_Space) {
        Bullet *bullet = new Bullet();
        bullet->setPos(x(), y());
        scene()->addItem(bullet);

        if (bulletSound->playbackState() == QMediaPlayer::PlayingState) {
            bulletSound->setPosition(0);
        } else {
            bulletSound->play();
        }
    }
}

void Player::spawn()
{
    // create an enemy
    Enemy *enemy = new Enemy();
    scene()->addItem(enemy);
}
