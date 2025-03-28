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
public:
    explicit GameMap(QObject *parent = nullptr);

    //加载地图,bool参数决定重置地图或更换地图
    void loadMap(bool changefile);

    //绘制地图 (三参数版决定绘制位置和大小)。
    void paintMap(QPainter*);

    //判断目标位置是路/point
    bool isRoad(QPoint pos);
    bool isPoint(QPoint pos);
    bool isBox(QPoint pos);

    //判断人物是否可以直接移动
    bool canDirectlyMove(QPoint pos);

    //player碰撞箱子后移动箱子
    bool trymoveBox(QPoint boxPos,Direction dir);

    //发送noLastPoint信号用
    void isGameComplete();


    //地图
    QHash<QPoint,int> map;
    QString filename;

    //宽高
    int mapWidth;
    int mapHeight;

    //剩余point数量
    int lastPoint;

    //地图的位置和元素大小
    QPoint mapPos;
    int ElementSize;


signals:
    void noLastPoint();

private:

};

#endif // GAMEMAP_H
