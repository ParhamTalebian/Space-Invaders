#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <Qdebug>
#include <QList>
#include "enemy.h"
#include "game.h"

extern Game * game; //there is an external global object

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    //draw graphics

    QPixmap originalPixmap(":/Images/bullet.png");  // Replace with the path to your image

    // Resize the pixmap without maintaining the aspect ratio
    QPixmap resizedPixmap = originalPixmap.scaled(10, 20,Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

    // Set the resized pixmap as the image for QGraphicsPixmapItem
    setPixmap(resizedPixmap);

    //connect to timer to the move slot
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

void Bullet::move()
{
    // check for collision with enemies
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n ; ++i)
    {
        if(typeid(*(colliding_items[i])) == typeid(Enemy))
        {
            //increase score
            game->score->increase();

            //remove the enemy and bullet on the scene still on the heap
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            delete colliding_items[i];
            delete this;
            return;
        }

    }


    // move the bullet  upwards
    setPos(x(), y() - 10);
    //Remove the bullet if it goes out of the window
    if(pos().y() + pixmap().height() < 0)
    {
        scene()->removeItem(this);
        delete this;

    }
}
