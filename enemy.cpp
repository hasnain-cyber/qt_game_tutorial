#include "enemy.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <stdlib.h>
#include <game.h>

extern Game *game;

Enemy::Enemy(QGraphicsItem* parent): QGraphicsPixmapItem(parent) {
    int random_number = rand() % 700;
    setPos(random_number, 0);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);

    QPixmap tempPixMap = QPixmap(":/images/enemy.png");
    setPixmap(tempPixMap.scaled(tempPixMap.size() * 0.1));
    setTransformOriginPoint(pixmap().width() / 2, pixmap().height() / 2);
    setRotation(180);
}

void Enemy::move()
{
    setPos(x(), y() + 5);

    if (pos().y() > scene()->height()) {
        // decrease the score
        game->health->decrease();

        // destroy enemy
        scene()->removeItem(this);
        delete this;
    }
}
