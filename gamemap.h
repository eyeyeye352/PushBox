#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QObject>
#include <QHash>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>
#include <QPainter>
#include "enums.h"

class GameMap : public QObject
{
    Q_OBJECT

    friend class Player;

public:
    explicit GameMap(QObject *parent = nullptr);

    //加载地图,bool参数决定重置地图或更换地图
    void loadMap(bool changefile);

    //绘制地图 (三参数版决定绘制位置和大小)。
    void paintMap(QPainter*);

    //设置地图位置，元素大小
    void setMapPos(QPoint);
    void setElementSize(int);

    //玩家移动碰撞时判断需要
    bool isBox(QPoint pos);

    //判断人物是否可以直接移动
    bool canDirectlyMove(QPoint pos);

    //player碰撞箱子后移动箱子,bool返回箱子是否移动，同时判断游戏是否完成。
    bool trymoveBox(QPoint boxPos,Direction dir);




signals:
    void noLastPoint();
    void loadMapErr();

private:

    //相对窗口的偏移像素量
    QPoint mapPos;

    //玩家相对地图的x,y坐标
    QPoint playerPos;
    int elementSize;

    //剩余point数量
    int lastPoint;

    //地图
    QHash<QPoint,int> map;
    QString filename;

    //地图宽高
    int mapWidth;
    int mapHeight;

};

#endif // GAMEMAP_H
