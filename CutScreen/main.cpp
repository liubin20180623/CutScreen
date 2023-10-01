//----------------------------------------------------------------------------------------------------
// Name    : CutScreen++
// Version : V1.00 (09.27.2023)
// author  : liu.bin(1823323995@qq.com)
//----------------------------------------------------------------------------------------------------

#include <QApplication>
#include <QFile>
#include <mainwidget.h>
#include <qconfig.h>
#include <qcutscreenoption.h>
#include <qtool.h>
#include <qcutscreenoption.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QConfig & config = QConfig::instance();
    config.loadConfig("Config.ini");

    QTool::instance().CreateStartupMenuLink(g_cutscreen_options->autoRun,"CutScreen");

    QFile file(":/css/blue.css");
    file.open(QFile::ReadOnly);
    QString css = file.readAll();
    qApp->setStyleSheet(css);

    MainWidget w;
    w.hide();

    return a.exec();
}
