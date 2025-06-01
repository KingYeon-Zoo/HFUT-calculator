#include <QApplication>
#include <QStyleFactory>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 设置应用程序信息
    app.setApplicationName("HFUT Calculator");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("HFUT");
    app.setApplicationDisplayName("HFUT 计算器");
    
    // 设置应用程序样式
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // 创建主窗口
    MainWindow window;
    window.show();
    
    return app.exec();
} 