#include "MainScene.h"
#include <QtWidgets/QApplication>
#include "windows.h"
#pragma comment(lib,"User32.lib")

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    qreal  cx = GetSystemMetrics(SM_CXSCREEN);
    qreal scale = cx / 1920;
    qputenv("QT_SCALE_FACTOR", QString::number(scale).toLatin1());
    //控制缩放，使得其在Windows缩放下能正常运行。1080p以及以上屏幕应该不会有问题(本人2k屏下调节分辨率模拟1080p没有bug)
    QApplication a(argc, argv);
    MainScene w(nullptr);
    w.show();
    return a.exec();
}