#ifndef QCUTSCREENOPTION_H
#define QCUTSCREENOPTION_H
#include <qconfig.h>
#include <QSettings>
#include <QDebug>

class QCutScreenOption
{
public:
    QCutScreenOption()
        :type(0)
        ,autoRun(0){
    }

public:
    int type;
    int autoRun;

};

static QCutScreenOption *g_cutscreen_options = 0;

static void QCutScreenOptionParser(QSettings *setting)
{
    if(g_cutscreen_options==0)
    {
        g_cutscreen_options = new QCutScreenOption;
    }
    setting->beginGroup("Config");
    g_cutscreen_options->type = setting->value("Type", 0).toInt();
    g_cutscreen_options->autoRun = setting->value("AutoRun", 0).toInt();
    setting->endGroup();
}

REGISTER_CONFIG_PARSER(QCutScreenOptionParser);

#endif // QCUTSCREENOPTION_H
