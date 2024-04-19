#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow{};
    mainWindow.resize(900,600);
    mainWindow.setWindowTitle("OpenGL test");
    mainWindow.show();
    return a.exec();
}
