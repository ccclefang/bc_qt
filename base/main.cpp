#include "test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SingletonInitBase::InitMap();


    base w;
    w.show();
    return a.exec();
}
