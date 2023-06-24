#ifndef HEALTH_H
#define HEALTH_H
#include <QGraphicsTextItem>
#include <QGraphicsScene>
class Health : public QGraphicsTextItem
{
public:
    Health(QGraphicsItem * parent = 0);
    void decrease();
    int getHealth();
private:
    int health;
    bool gameover();

};


#endif // HEALTH_H
