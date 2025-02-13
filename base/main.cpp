#include "test.h"

#include "page_board.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    SingletonInitBase::InitMap();


    BoardWidget w;
    w.show();
    return a.exec();
}
