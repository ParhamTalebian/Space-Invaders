#include "health.h"
#include <QGraphicsScene>
#include <QFont>
#include "game.h"
extern Game *game;
Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    health = 3;

    setPlainText("Health: " + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 16));
}

void Health::decrease()
{
    health--;
    if(gameover())
    {
        game->displayGameover();
    }
    else
    {
        setPlainText("Health: " + QString::number(health));
    }

}

int Health::getHealth()
{
    return health;
}

bool Health::gameover()
{
    return health < 1;
}
