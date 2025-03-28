#ifndef GAMESYS_H
#define GAMESYS_H

#include <QWidget>
#include <QMessageBox>
#include <QPainter>
#include <QKeyEvent>
#include <QIcon>
#include <QFontDialog>
#include <QLabel>

#include "player.h"
#include "gamemap.h"
#include "enums.h"



/*系统：
 *
 * 键盘事件移动玩家位置
 * 绘图事件更新画面
 * 储存一份地图,一份玩家
 */


/*
 *
 * 调整了系统类的结构：
 * 新增了更多的信号和槽机制，更加符合qt风格。
 */

class Gamesys : public QWidget
{
    Q_OBJECT

public:
    Gamesys(QWidget *parent = nullptr);
    ~Gamesys();

    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

    void showHelpWidget();

    //bool决定重置或更换地图
    void resetGame(bool changemap);



public slots:

    //游戏胜利弹窗
    void onGameComplete();

    //地图载入失败弹窗
    void onLoadMapFail();


private:
    //绘图用
    QPainter* painter;

    //地图与玩家对象
    GameMap* map;
    Player* p1;

    //优化用
    bool backgroundHasPainted;

};
#endif // GAMESYS_H
