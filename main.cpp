#include "gamesys.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gamesys w;
    w.show();
    return a.exec();
}
