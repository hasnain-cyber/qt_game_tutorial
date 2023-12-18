#include "score.h"

#include <QGraphicsItem>
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent) {
    // init score to 0;
    score = 0;

    // draw the text for score
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times", 16));
}

void Score::increase() {
    score++;
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::getScore() {
    return score;
}
