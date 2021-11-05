#include <QtWidgets/QApplication>
#include <iostream>
#include "Test.h"
#include "Repository.h"
#include "Service.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "CarUi.h"
#include "MyTableModel.h"
#include "qtableview.h"
int main(int argc, char *argv[])
{
    {
        Test t;
        t.testAll();        
    }
    QApplication a(argc, argv);


    FileRepo repo("Cars.txt");
    Service srv(repo);
    CarUi ui(srv);
     ui.show();
    return a.exec();
}
