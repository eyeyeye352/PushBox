#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPoint>
#include <QPainter>
#include <QImage>
#include <QPointer>

#include "gamemap.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    //关联地图获取坐标
    void connectMap(GameMap*);

    //话玩家
    void paintPlayer(QPainter*);

    //移动
    void move(Direction);


signals:
private:

    QPointer<GameMap> involveMap;

    //人物在地图中的坐标，由关联地图取得。
    QPoint playerPos;
    int playerSize;

    //玩家图像
    QImage img;
};

#endif // PLAYER_H
