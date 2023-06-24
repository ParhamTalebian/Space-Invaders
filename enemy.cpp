#include "enemy.h"
#include <QList>
#include <stdlib.h>

#include "game.h"
extern Game *game;
Enemy::Enemy (QGraphicsItem *parent ) : QObject(), QGraphicsPixmapItem()
{
    int random_number = rand() % 700;
    setPos(random_number, 0);
    //draw the rect
    setPixmap(QPixmap(":/Images/Invaders.png"));
    QPixmap originalPixmap(":/Images/Invaders.png");  // Replace with the path to your image

    // Resize the pixmap without maintaining the aspect ratio
    QPixmap resizedPixmap = originalPixmap.scaled(50, 50,Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

    // Set the resized pixmap as the image for QGraphicsPixmapItem
    setPixmap(resizedPixmap);

    //connect
    QTimer * timer = new QTimer(this );
    connect(timer,SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

void Enemy::move()
{
    setPos(x(), y() + 5);
    if(pos().y() > 600)
    {
        //decrease health
        game->health->decrease();
        scene()->removeItem(this);
        delete this;


    }
}
