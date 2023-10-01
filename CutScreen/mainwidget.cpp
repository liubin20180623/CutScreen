#include "mainwidget.h"
#include "windows.h"
#include <QApplication>
#include <QTimer>
#include <qtrayicon.h>
#include <qcutscreenitem.h>
#include <qcutscreenview.h>
#include <qcutscreenscene.h>
#include <GridWndHook.h>

MainWidget::MainWidget(QWidget *parent)
        :QWidget(parent)
{
    initAll();
    InstallHook((HWND)this->winId());
}

MainWidget::~MainWidget()
{
    UnInstallHook();
    restoreWnd();
}

void MainWidget::initAll()
{
    RECT rcWork;
    SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcWork, NULL);
    m_width  = rcWork.right - rcWork.left;
    m_height = rcWork.bottom - rcWork.top;

    setGeometry(0, 0, m_width, m_height);
    setAttribute(Qt::WA_TransparentForMouseEvents,true); // 一定要先设置鼠标穿透,否则无法穿透
    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowModality(Qt::NonModal);

    if(!view){
        scene = new QCutScreenScene(0,0,m_width,m_height);
        view = new QCutScreenView(scene,m_width,m_height,this);
    }

    initSysTrayIcon();
    initConnection();
}

void MainWidget::initSysTrayIcon()
{
    m_pTrayIcon = new QTrayIcon(this);
    m_pTrayIcon->show();
}

void MainWidget::initConnection()
{
    connect(m_pTrayIcon,&QTrayIcon::sigCutScreen,this,&MainWidget::slotCreateCutScreen);
    connect(m_pTrayIcon,&QTrayIcon::sigQuit,this,[=](){qApp->exit();});
}

void MainWidget::restoreWnd()
{
    for(int i =0; i < m_Wnds.size();i++)
    {
       WId wnd = m_Wnds[i];
       DWORD dwStyle = GetWindowLong((HWND)wnd, GWL_STYLE);
       SetWindowLong((HWND)wnd, GWL_STYLE, dwStyle | WS_SIZEBOX);
    }
}

void MainWidget::updateCutScreen()
{
    if(view){
        view->updateCutScreen();
        this->setVisible(true);
    }
}

void MainWidget::moveCutScreen(WId hwnd)
{
    QRect rect;
    if(view->m_qcsiMgr->getSelectedRect(rect)){
        DWORD  dwStyle = GetWindowLong((HWND)hwnd, GWL_STYLE);
        dwStyle  &= ~(WS_SIZEBOX | WS_MINIMIZEBOX);
        SetWindowLong((HWND)hwnd, GWL_STYLE, dwStyle);

       ::SetWindowPos((HWND)hwnd,HWND_NOTOPMOST,rect.left(),rect.top(),rect.width(),rect.height(),SWP_SHOWWINDOW);

        dwStyle = GetWindowLong((HWND)hwnd, GWL_STYLE);
        SetWindowLong((HWND)hwnd, GWL_STYLE, dwStyle | WS_MINIMIZEBOX);
    }
    this->hide();
}

bool MainWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if(eventType == "windows_generic_MSG")
    {
        MSG* pMsg = static_cast<MSG*>(message);
        if(pMsg && pMsg->message == WM_WND_HOOK && m_typeId>0)
        {
            if(m_pTrayIcon->getWid() != (WId)pMsg->lParam &&
                    this->winId() != (WId)pMsg->lParam)
            {
                if(!m_Wnds.contains(pMsg->lParam)){
                    m_Wnds.push_back(pMsg->lParam);
                }

                if(pMsg->wParam == USER_MOVE_WINDOWS){
                    updateCutScreen();
                }
                if(pMsg->wParam == USER_MOUSE_LBUTTON_UP){
                    moveCutScreen(pMsg->lParam);
                }
            }
        }

    }
    return QWidget::nativeEvent(eventType,message,result);
}

void MainWidget::slotCreateCutScreen(int typeId)
{
    m_typeId = typeId;
    if(view && m_typeId>0)
    {
       setVisible(true);
       view->createCutScreen(typeId);
       QTimer::singleShot(1000, this, [this]() {  setVisible(false); });
    }else{
        restoreWnd();
    }
}
