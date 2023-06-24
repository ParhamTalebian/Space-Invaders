#include "game.h"
#include "button.h"
#include <QApplication>
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include "enemy.h"
#include <QAudioOutput>

Game::Game(QWidget *parent)
{
    //create secene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);// make the secen 800 * 600 instead of infinity by infinity
    setBackgroundBrush(QBrush(QImage(":/Images/Background.png")));

    //make the newly created scene the scene to visualize
    //it ccan be used to visualize scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);


    //create an item to put into the scene
    Player * player = new Player();
    player ->setPos(400,500); // to always generate in the middle
    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add to the senec
    scene->addItem(player);

    // add view
    QGraphicsView * view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    view->setFixedSize(800, 600);
    scene->setSceneRect(0, 0, 800, 600);
    QImage backgroundImage(":/Images/Background.png");
    QImage scaledImage = backgroundImage.scaled(view->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    view->setBackgroundBrush(QBrush(scaledImage));



    player->setPos(view->width()/2, view->height() - player->pixmap().height());


    //spawn enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    timer->start(2000);

    //Create score
    score = new Score();
    scene->addItem(score);

    health = new Health();
    health->setPos(health->x(), health->y() + 25);
    scene->addItem(health);

    //play background
    QMediaPlayer *  music = new QMediaPlayer();

    QAudioOutput* audioOutput = new QAudioOutput;
    music->setAudioOutput(audioOutput);

    music->setSource(QUrl("qrc:/sounds/GBC.mp3"));

    music->play();


    qDebug() << "Background music state:" << music->mediaStatus();

}

void Game::displayMainmenu()
{
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Space Invaders"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(Qt::yellow);
    int xTitlePos = this->width()/2 - titleText->boundingRect().width()/2;
    int yTitlePos = 150;
    titleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(titleText);

    // create play button
    Button *playButton = new Button(QString("Play"));
    int xPlayPos = this->width()/2 - playButton->boundingRect().width()/2;
    int yPlayPos = 275;
    playButton->setPos(xPlayPos, yPlayPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    // create settings button
    Button *settingsButton = new Button(QString("Settings"));
    int xSettingsPos = this->width()/2 - settingsButton->boundingRect().width()/2;
    int ySettingsPos = 350;
    settingsButton->setPos(xSettingsPos, ySettingsPos);
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(displaySettingsMenu()));
    scene->addItem(settingsButton);

    // create quit button
    Button *quitButton = new Button(QString("Quit"));
    int xQuitPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int yQuitPos = 425;
    quitButton->setPos(xQuitPos, yQuitPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::displayGameover()
{
    //create gameover text

    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Game Over"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(Qt::yellow);
    int xTitlePos = this->width()/2 - titleText->boundingRect().width()/2;
    int yTitlePos = 150;
    titleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(titleText);

    // create "Retry" button
    Button *retryButton = new Button(QString("Retry"));
    int xRetryPos = this->width()/2 - retryButton->boundingRect().width()/2;
    int yRetryPos = 275;
    retryButton->setPos(xRetryPos, yRetryPos);
    connect(retryButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(retryButton);

    Button *settingsButton = new Button(QString("Settings"));
    int xSettingsPos = this->width()/2 - settingsButton->boundingRect().width()/2;
    int ySettingsPos = 350;
    settingsButton->setPos(xSettingsPos, ySettingsPos);
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(displaySettingsMenu()));
    scene->addItem(settingsButton);

    // create quit button
    Button *quitButton = new Button(QString("Quit"));
    int xQuitPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int yQuitPos = 425;
    quitButton->setPos(xQuitPos, yQuitPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);

}

void Game::displaySettingsMenu()
{

    // clean up the screen
    scene->clear();

    // create "Settings" text
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Settings"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    int xTitlePos = this->width()/2 - titleText->boundingRect().width()/2;
    int yTitlePos = 150;
    titleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(titleText);

    // TO DO: List to select different resolution versions (480p, 720p, 1080p)

    // TO DO: Re-bind keys

    // TO DO: Replace "quit" button with a "back" button

    // create quit button
    Button *quitButton = new Button(QString("Quit"));
    int xQuitPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int yQuitPos = 425;
    quitButton->setPos(xQuitPos, yQuitPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);

}
