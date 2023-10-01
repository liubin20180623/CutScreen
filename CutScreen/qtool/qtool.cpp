#include "qtool.h"
#include <QObject>
#include <QDir>
#include <QApplication>
#include <QStandardPaths>

void QTool::CreateStartupMenuLink(bool IsAutoRun,const QString& appName)
{
    QString strAppPath =  QCoreApplication::applicationDirPath() + QString("/%0.exe").arg(appName);

    QFile fApp(strAppPath);

    QString strMenuLink = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) + "/";
    strMenuLink += "Startup/";

    QDir pathDir;
    pathDir.mkpath(strMenuLink);
    strMenuLink += QString("%0.lnk").arg(appName);

    QFileInfo  dir(strMenuLink);
    if (dir.isFile()){
       QFile::remove(strMenuLink);
    }

    //生成开机启动快捷方式
    if(IsAutoRun){
        fApp.link(strMenuLink);
    }
}
