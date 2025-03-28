#include "gamemap.h"

GameMap::GameMap(QObject *parent)
    : QObject{parent}
{}



void GameMap::loadMap(bool changefile = false){

    //载入前重置属性。
    map.clear();
    lastPoint = 0;
    mapWidth = mapHeight = 0;

    if(changefile){
        filename = QFileDialog::getOpenFileName(nullptr,"载入地图","../examples","(*.txt)");
    }

    QFile * file = new QFile(filename,this);

    if(!file->open(QIODevice::ReadOnly)){
        emit loadMapErr();
        return;
    }

    /*文件字符串处理：
     *
     * windows系统下换行符为\r\n，将其统一替换为\n。
     * split('\n')分割每个row，遍历每个row在以','分隔
     * key（QPoint）为（x，y），value为int，对应枚举MapElement。
     *
     * extra：
     * 在载入地图期间记录总POINT数量与玩家位置。
     */
    QString wholetext = file->readAll();
    wholetext.replace("\r\n","\n");
    QStringList lines = wholetext.split('\n');

    for (int row = 0; row < lines.size(); ++row) {
        QStringList elements = lines[row].split(',');

        for (int col = 0; col < elements.size(); ++col) {

            QPoint index(col,row);
            map[index] = elements[col].toInt();

            if(map[index] == MapElement::POINT)  ++lastPoint;
            else if(map[index] == MapElement::PLAYER) playerPos = QPoint(col,row);
        }
    }

    //设置宽高
    mapHeight = lines.size();
    mapWidth = lines[0].split(',').size();
}




void GameMap::paintMap(QPainter* painter){

    //文件加载错误时直接结束。
    if(mapHeight <= 0 || mapWidth <= 0) return;


    /*根据（x，y）遍历地图map，根据map[(x,y)]对应枚举画出对应的图片。
     * （ROAD和PLAYER均表现为ROAD）
     * 地图物件绘图位置 = {地图位置x + 物件大小*行数，地图位置y + 物件大小*列数，物件大小，物件大小}
     *
     */
    for (int x = 0; x < mapWidth; ++x) {
        for (int y = 0; y < mapHeight; ++y) {

            QImage img;
            switch(map[QPoint(x,y)]){

            case MapElement::ROAD:
            case MapElement::PLAYER:
                img.load(":/img/img/road.png");
                break;

            case MapElement::WALL:
                img.load(":/img/img/wall.png");
                break;

            case MapElement::BOX:
                img.load(":/img/img/box_on_road.png");
                break;

            case MapElement::POINT:
                img.load(":/img/img/Point.png");
                break;

            case MapElement::IN_POINT:
                img.load(":/img/img/in_point.png");
                break;
            }

            QRect rect(mapPos.x() + x*elementSize,
                       mapPos.y() + y*elementSize,
                       elementSize,elementSize);
            painter->drawImage(rect,img);
        }
    }

}


//尝试移动箱子，移动不成功将返回false
bool GameMap::trymoveBox(QPoint boxPos,Direction dir){

    QPoint boxNewPos;

    //记录箱子即将移动的下一个位置。
    switch (dir) {
    case Direction::UP:
        boxNewPos = boxPos + QPoint(0,-1);
        break;
    case Direction::LEFT:
        boxNewPos = boxPos + QPoint(-1,0);
        break;
    case Direction::RIGHT:
        boxNewPos = boxPos + QPoint(1,0);
        break;
    case Direction::DOWN:
        boxNewPos = boxPos + QPoint(0,1);
        break;
    }

    //若为ROAD或PLAYER，则可以直接移动（交换两个位置的地图元素）
    if(map[boxNewPos] == MapElement::ROAD || map[boxNewPos] == MapElement::PLAYER){

        std::swap(map[boxPos],map[boxNewPos]);
        return true;

    }
    //若为POINT，则设置为INPOINT，BOX原位置设为ROAD，使剩余POINT数-1.
    //同时尝试判断是否完成游戏。
    else if(map[boxNewPos] == MapElement::POINT){

        map[boxPos] = MapElement::ROAD;
        map[boxNewPos] = MapElement::IN_POINT;
        --lastPoint;

        if(lastPoint == 0)  emit noLastPoint();
        return true;

    }else{
        return false;
    }
}


bool GameMap::isBox(QPoint pos){ return map[pos] == MapElement::BOX; }

void GameMap::setMapPos(QPoint pos){ this->mapPos = pos;}
void GameMap::setElementSize(int size){ this->elementSize = size;}


bool GameMap::canDirectlyMove(QPoint pos){
    return (map[pos] == MapElement::ROAD) || (map[pos] == MapElement::POINT) || (map[pos] == MapElement::PLAYER);
}



