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

    void completeGame();


    //地图与玩家对象
    GameMap* map;
    Player* p1;

public slots:
    void onGameComplete();


private:
    //绘图用
    QPainter* painter;

};
#endif // GAMESYS_H
