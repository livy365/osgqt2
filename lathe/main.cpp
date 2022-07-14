#include "lathe.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
lathe *w1;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lathe w;
    w1 = &w;
    w.show();
    return a.exec();
}
