#ifndef QTRAYICON_H
#define QTRAYICON_H
#include <QSystemTrayIcon>

class QMenu;
class QWidget;
class QPushButton;
class QButtonGroup;
class QToolButton;
class QWidgetAction;
class QTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit QTrayIcon(QObject *parent = 0);
    bool eventFilter(QObject *obj, QEvent *event);
    WId getWid();

signals:
    void sigCutScreen(int typeId);
    void sigQuit();

protected:
    void initConnection();
    void initTrayIcon();
    void initTopMenu();
    void initMsgMenu();
    void initBtnsMenu();
    void initBottomMenu();
    void addMenus();

private:
    QMenu* m_trayMenu;
    QPushButton* m_pUpdateBtn;
    QPushButton* m_pAboutBtn;
    QPushButton* m_pExitBtn;
    QWidget* m_topWidget;
    QWidgetAction* m_topWidgetAction;
    QWidgetAction* m_msgWidgetAction;
    QWidgetAction* m_btnsWidgetAction;
    QWidgetAction* m_bottomWidgetAction;
    QButtonGroup*  m_btnGroup;
};

#endif // QTRAYICON_H
