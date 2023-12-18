#include "bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QList>
#include <enemy.h>
#include <game.h>

extern Game* game;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    // draw graphics
    QPixmap tempPixMap = QPixmap(":/images/bullet.png");
    setPixmap(tempPixMap.scaled(tempPixMap.size() * 0.1));

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

void Bullet::move()
{
    // if bullet collides with enemy, destroy both
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(int i = 0; i < colliding_items.size(); i++) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
            // increase the score
            game->score->increase();

            // remove from scene, and delete from memory
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            delete colliding_items[i];
            delete this;
            return;
        }
    }

    setPos(x(), y() - 10);
    if (pos().y() + pixmap().height() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}
