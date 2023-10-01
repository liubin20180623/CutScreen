#ifndef QCONFIG_H
#define QCONFIG_H
#include <QObject>

class QSettings;
class QFileSystemWatcher;

typedef void (*LPFNPARSECONFIG)(QSettings * conf);
void registerConfigParser(LPFNPARSECONFIG lpfn);
class ConfigParserRegisterHelper
{
public:
    ConfigParserRegisterHelper(LPFNPARSECONFIG lpfn)
    {
        registerConfigParser(lpfn);
    }
};
#define REGISTER_CONFIG_PARSER(fn) \
static ConfigParserRegisterHelper g_parserRegister(fn)

class QConfig : public QObject
{
   Q_OBJECT
public:
    static QConfig &instance();
    void loadConfig(const char *config);

protected slots:
    void onConfigFileChanged(const QString &path);

private:
    void parseModuleConfig(QSettings *settings);

protected:
    QConfig();

private:
    QFileSystemWatcher *m_fileWatcher;

};

#endif // QCONFIG_H
