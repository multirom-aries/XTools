#include "xtool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XTool w;
    w.show();

    return a.exec();
}
