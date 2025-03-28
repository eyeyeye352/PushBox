#include "gamemap.h"

GameMap::GameMap(QObject *parent)
    : QObject{parent}
{
    mapPos = QPoint(0,0);
    ElementSize = 30;
}



void GameMap::loadMap(bool changefile = false){

    //载入前先重置一些属性。
    map.clear();
    lastPoint = 0;
    mapWidth = mapHeight = 0;

    if(changefile){
        filename = QFileDialog::getOpenFileName(nullptr,"载入地图","../examples","(*.txt)");
    }

    QFile * file = new QFile(filename,this);

    if(!file->open(QIODevice::ReadOnly)){
        QMessageBox::critical(nullptr,"载入失败","地图文件格式错误，或者你没有选择文件！");
        return;
    }

    QString wholetext = file->readAll();
    wholetext.replace("\r\n","\n");
    QStringList lines = wholetext.split('\n');

    for (int row = 0; row < lines.size(); ++row) {
        QStringList elements = lines[row].split(',');

        for (int col = 0; col < elements.size(); ++col) {

            QPoint index(col,row);
            map[index] = elements[col].toInt();

            if(map[index] == MapElement::POINT){
                ++lastPoint;
            }
        }
    }

    mapHeight = lines.size();
    mapWidth = lines[0].split(',').size();
}




void GameMap::paintMap(QPainter* painter){

    if(mapHeight <= 0 || mapWidth <= 0) return;

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

            QRect rect(mapPos.x() + x*ElementSize,
                       mapPos.y() + y*ElementSize,
                       ElementSize,ElementSize);
            painter->drawImage(rect,img);
        }
    }

}



bool GameMap::trymoveBox(QPoint boxPos,Direction dir){

    QPoint boxNewPos;

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

    if(isRoad(boxNewPos) || map[boxNewPos] == MapElement::PLAYER){

        std::swap(map[boxPos],map[boxNewPos]);
        return true;

    }else if(isPoint(boxNewPos)){

        map[boxPos] = MapElement::ROAD;
        map[boxNewPos] = MapElement::IN_POINT;
        --lastPoint;

        isGameComplete();

        return true;

    }else{
        return false;
    }
}


bool GameMap::isRoad(QPoint pos){ return map[pos] == MapElement::ROAD; }
bool GameMap::isPoint(QPoint pos){ return map[pos] == MapElement::POINT; }
bool GameMap::isBox(QPoint pos){ return map[pos] == MapElement::BOX; }



bool GameMap::canDirectlyMove(QPoint pos){
    return isRoad(pos) || isPoint(pos) || (map[pos] == MapElement::PLAYER);
};

void GameMap::isGameComplete(){
    if(lastPoint == 0){
        emit noLastPoint();
    }
}



