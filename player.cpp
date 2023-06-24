#include "player.h"
#include "bullet.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include<QDebug>
#include<QTimer>
#include "enemy.h"
#include <QAudioOutput>
Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{



    bulletSound = new QMediaPlayer();

    QAudioOutput* audioOutput = new QAudioOutput;
    bulletSound->setAudioOutput(audioOutput);

    bulletSound->setSource(QUrl("qrc:/sounds/shoot.wav"));

    //
    //bulletSound->play();
    //setGRaphics


    QPixmap originalPixmap(":/Images/spaceShip.png");  // Replace with the path to your image

    // Resize the pixmap without maintaining the aspect ratio
    QPixmap resizedPixmap = originalPixmap.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // Set the resized pixmap as the image for QGraphicsPixmapItem
    setPixmap(resizedPixmap);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        if(pos().x() > 0)
        setPos(x() - 10, y());
    }
    else if( event->key() == Qt::Key_Right)
    {
        if(pos().x() + 100 < 800)
        setPos(x() + 10, y());
    }
    else if( event->key() == Qt::Key_Up)
    {
        if(pos().y() > 0)
        setPos(x(), y() - 10);
    }
    else if( event->key() == Qt::Key_Down)
    {
        if(pos().y() + 100 < 600)
        setPos(x(), y() + 10);
    }
    else if(event->key() == Qt::Key_Space)
    {
        Bullet *bullet = new Bullet();
        bullet->setPos(x(), y());
        scene()->addItem(bullet);
        bulletSound->play();
        //play bullet sound
        if(bulletSound->mediaStatus() == QMediaPlayer::PlayingState)
        {
        bulletSound->setPosition(0);
        }
        else if(bulletSound->mediaStatus() == QMediaPlayer::StoppedState)
        {
            bulletSound->play();
        }
        qDebug() << "Bullet sound media state:" << bulletSound->mediaStatus();




    }
}

void Player::spawn()
{
    Enemy *enemy = new Enemy();
    scene()->addItem(enemy);

}
