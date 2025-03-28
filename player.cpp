#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{
    img.load(":/img/img/player_front.png");
}

void Player::connectMap(GameMap* map){
    involveMap = map;

    for (int x = 0; x < map->mapWidth; ++x) {
        for (int y = 0; y < map->mapHeight; ++y) {
            if(map->map[QPoint(x,y)] == MapElement::PLAYER){
                playerPos = QPoint(x,y);
            }
        }
    }

    paintPos = involveMap->mapPos;
    playerSize = involveMap->ElementSize;
}



void Player::paintPlayer(QPainter* painter){

    if(involveMap->mapHeight <= 0 || involveMap->mapWidth <= 0) return;

    QRect rect(paintPos.x() + playerPos.x()*playerSize,
               paintPos.y() + playerPos.y()*playerSize,
               playerSize,playerSize);
    painter->drawImage(rect,img);

}


void Player::move(Direction dir){

    QPoint playerNewPos;
    switch (dir) {
    case Direction::UP:
        playerNewPos = playerPos + QPoint(0,-1);
        break;
    case Direction::LEFT:
        playerNewPos = playerPos + QPoint(-1,0);
        break;
    case Direction::RIGHT:
        playerNewPos = playerPos + QPoint(1,0);
        break;
    case Direction::DOWN:
        playerNewPos = playerPos + QPoint(0,1);
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
