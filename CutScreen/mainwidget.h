#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QVector>

class QTrayIcon;
class QCutScreenScene;
class QCutScreenView;
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

protected:
    void initAll();
    void initSysTrayIcon();
    void initConnection();
    void restoreWnd();

protected slots:
    void slotCreateCutScreen(int typeId);
    void updateCutScreen();
    void moveCutScreen(WId hwnd);

private:
    int m_width;
    int m_height;
    int m_typeId = 0;
    QVector<WId> m_Wnds;
    QTrayIcon* m_pTrayIcon = Q_NULLPTR;
    QCutScreenScene* scene = Q_NULLPTR;
    QCutScreenView* view   = Q_NULLPTR;
};

#endif // MAINWIDGET_H
