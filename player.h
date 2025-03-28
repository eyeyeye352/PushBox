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

    //在地图上的坐标
    QPoint playerPos;

    //玩家图像
    QImage img;

signals:
private:
    QPointer<GameMap> involveMap;

    //绘制位置与大小，由关联地图取得。
    QPoint paintPos;
    int playerSize;
};

#endif // PLAYER_H
