#include "form_ui/mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    // Load the application style
//    QFile  styleFile(":/stylesheet/style/style.qss");
//    styleFile.open(QFile::ReadOnly);

//    // Apply the loaded stylesheet
//    QString  style(styleFile.readAll());
//    a.setStyleSheet(style);

    MainWindow w;
    w.showFullScreen();

    return a.exec();
}
