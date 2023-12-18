#include "health.h"

#include <QGraphicsItem>
#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent) {
    health = 3;

    // draw the text for score
    setPlainText(QString("Health: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 16));
}

void Health::decrease() {
    health--;
    setPlainText(QString("Health: ") + QString::number(health));
}

int Health::getHealth() {
    return health;
}
