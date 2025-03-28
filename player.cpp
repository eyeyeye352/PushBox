#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{
    img.load(":/img/img/player_front.png");
}

//关联地图
void Player::connectMap(GameMap* map){

    involveMap = map;

    //获取位置，人物大小信息
    playerPos = involveMap->playerPos;
    playerSize = involveMap->elementSize;
}



void Player::paintPlayer(QPainter* painter){

    if(involveMap->mapHeight <= 0 || involveMap->mapWidth <= 0) return;

    QRect rect(involveMap->mapPos.x() + playerPos.x()*playerSize,
               involveMap->mapPos.y() + playerPos.y()*playerSize,
               playerSize,playerSize);
    painter->drawImage(rect,img);

}


void Player::move(Direction dir){

    QPoint playerNewPos;
    switch (dir) {
    case Direction::UP:
        playerNewPos = playerPos + QPoint(0,-1);
        img.load(":/img/img/player_back.png");
        break;
    case Direction::LEFT:
        playerNewPos = playerPos + QPoint(-1,0);
        img.load(":/img/img/player_left.png");
        break;
    case Direction::RIGHT:
        playerNewPos = playerPos + QPoint(1,0);
        img.load(":/img/img/player_right.png");
        break;
    case Direction::DOWN:
        playerNewPos = playerPos + QPoint(0,1);
        img.load(":/img/img/player_front.png");
        break;
    }

    if(involveMap->canDirectlyMove(playerNewPos)){

        playerPos = playerNewPos;

    }else if(involveMap->isBox(playerNewPos)){

        if(involveMap->trymoveBox(playerNewPos,dir)){
            playerPos = playerNewPos;
        }
    }
};
