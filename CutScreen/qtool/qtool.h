#ifndef QTOOL_H
#define QTOOL_H
#include <QObject>

class QTool
{
public:
    static QTool instance(){
        static QTool m;
        return m;
    }

   void CreateStartupMenuLink(bool IsAutoRun,const QString& appName);

protected:
   QTool(){};
};

#endif // QTOOL_H
