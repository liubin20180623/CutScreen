#include "qconfig.h"
#include <QFile>
#include <QSettings>
#include <QFileSystemWatcher>
#include <QDebug>

static LPFNPARSECONFIG * g_configParser = NULL;
static int g_parserCapacity = 0;
static int g_parserSize = 0;
#define PARSER_INIT_SIZE 8
#define PARSER_INCREMENT 4

void registerConfigParser(LPFNPARSECONFIG lpfn)
{
    if(g_configParser == NULL)
    {
        g_configParser = (LPFNPARSECONFIG*)calloc(PARSER_INIT_SIZE, sizeof(LPFNPARSECONFIG));
        g_parserCapacity = PARSER_INIT_SIZE;
        g_parserSize = 0;
    }

    if(g_parserSize == g_parserCapacity)
    {
        g_parserCapacity += PARSER_INCREMENT;
        g_configParser = (LPFNPARSECONFIG*)realloc(g_configParser, sizeof(LPFNPARSECONFIG)*g_parserCapacity);
    }

    g_configParser[g_parserSize++] = lpfn;
}

QConfig::QConfig()
{
    m_fileWatcher = new QFileSystemWatcher(this);
    connect(m_fileWatcher,&QFileSystemWatcher::fileChanged,
            this,&QConfig::onConfigFileChanged);
}

QConfig &QConfig::instance()
{
    static QConfig config;
    return config;
}

void QConfig::loadConfig(const char *config)
{
    if(!config || !QFile::exists(config))
    {
        config = "Config.ini";
        if(!QFile::exists(config))
        {
            return ;
        }
    }

    m_fileWatcher->addPath(config);
    onConfigFileChanged(config);
}

void QConfig::onConfigFileChanged(const QString &path)
{
    QSettings conf(path, QSettings::IniFormat);
    parseModuleConfig(&conf);
}

void QConfig::parseModuleConfig(QSettings *settings)
{
    for(int i = 0; i < g_parserSize; i++)
    {
        if(g_configParser[i])
        {
            g_configParser[i](settings);
        }
    }
}

