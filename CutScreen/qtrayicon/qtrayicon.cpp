#include "qtrayicon.h"
#include <QMenu>
#include <QLabel>
#include <QDebug>
#include <QToolButton>
#include <QWidgetAction>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QEvent>
#include <QPainter>
#include <QFile>

static const int btnSize = 18;

QTrayIcon::QTrayIcon(QObject *parent)
        :QSystemTrayIcon(parent)
{
    initTrayIcon();
    initTopMenu();
    initMsgMenu();
    initBtnsMenu();
    initBottomMenu();
    addMenus();
    initConnection();
}

WId QTrayIcon::getWid()
{
    if(m_trayMenu){
        return m_trayMenu->winId();
    }
   return 0;
}

bool QTrayIcon::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == m_topWidget && event->type() == QEvent::Paint)
    {
       QPainter painter(m_topWidget);
       painter.setPen(Qt::NoPen);
       painter.setBrush(QColor(42,120,192));
       painter.drawRect(m_topWidget->rect());
    }
    return QSystemTrayIcon::eventFilter(obj,event);
}

void QTrayIcon::initConnection()
{
    connect(m_btnGroup,&QButtonGroup::idClicked,this,[&](int id){
        emit sigCutScreen(id);
    });

    connect(m_pExitBtn,&QPushButton::clicked,this,[=](){
        emit sigQuit();
    });
}

void QTrayIcon::initTrayIcon()
{
    m_trayMenu = new QMenu();
    this->setContextMenu(m_trayMenu);
    this->setIcon(QIcon(":/images/app.png"));
    this->setToolTip("Cut Screen++");
}

void QTrayIcon::initTopMenu()
{
    m_topWidget = new QWidget();
    m_topWidgetAction = new QWidgetAction(m_trayMenu);

    QLabel* pTopLabelIcon = new QLabel();
    pTopLabelIcon->setPixmap(QPixmap(":/images/topicon.png"));
    pTopLabelIcon->setFixedSize(30,30);

    QLabel* pTopLabel = new QLabel("Cut Screen+");
    pTopLabel->setObjectName(QString("WhiteLabel"));

    QHBoxLayout* pTopLayout = new QHBoxLayout();
    pTopLayout->addWidget(pTopLabelIcon);
    pTopLayout->addWidget(pTopLabel,1,Qt::AlignHCenter | Qt::AlignVCenter);
    pTopLayout->setContentsMargins(0,0,0,0);

    m_topWidget->setLayout(pTopLayout);
    m_topWidget->setMinimumHeight(70);
    m_topWidget->installEventFilter(this);
    m_topWidgetAction->setDefaultWidget(m_topWidget);
}

void QTrayIcon::initMsgMenu()
{
    QWidget* msgWidget = new QWidget();
    m_msgWidgetAction  = new QWidgetAction(m_trayMenu);

    QLabel* pMsgIcon = new QLabel();
    pMsgIcon->setPixmap(QPixmap(":/images/qq.png"));
    pMsgIcon->setFixedSize(50,50);

    QLabel* pMsgLabel = new QLabel("QQ:1823323995\nTel:186 6646 2895");
    pMsgLabel->setFont(QFont("Times", 10));
    pMsgLabel->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* pMsgLayout = new QHBoxLayout();
    pMsgLayout->addWidget(pMsgIcon);
    pMsgLayout->addWidget(pMsgLabel);
    pMsgLayout->setContentsMargins(0,0,0,0);

    msgWidget->setLayout(pMsgLayout);
    msgWidget->setMinimumHeight(70);
    m_msgWidgetAction->setDefaultWidget(msgWidget);
}

void QTrayIcon::initBtnsMenu()
{
   QWidget* btnsWidget = new QWidget();
   m_btnsWidgetAction  = new QWidgetAction(m_trayMenu);
   m_btnGroup = new QButtonGroup(this);

   QVBoxLayout *mainLout = new QVBoxLayout();
   QHBoxLayout *toplayout = new QHBoxLayout();
   QHBoxLayout *centerlayout = new QHBoxLayout();
   QHBoxLayout *bottomlayout = new QHBoxLayout();

   for(int i =0 ; i < btnSize ; i++)
   {
     QToolButton *m_btnCutScreen = new QToolButton();
     m_btnCutScreen->setIcon(QIcon(QString(":/images/%0.bmp").arg(i)));
     m_btnCutScreen->setIconSize(QSize(13,13));
     m_btnCutScreen->setAutoRaise(true);
     m_btnCutScreen->setCheckable(true);

     m_btnGroup->addButton(m_btnCutScreen,i);

     if(i<6)
         toplayout->addWidget(m_btnCutScreen);
     else if(i>=6 && i <12)
         centerlayout->addWidget(m_btnCutScreen);
     else
         bottomlayout->addWidget(m_btnCutScreen);
   }
   mainLout->addLayout(toplayout);
   mainLout->addLayout(centerlayout);
   mainLout->addLayout(bottomlayout);

   btnsWidget->setLayout(mainLout);
   m_btnsWidgetAction->setDefaultWidget(btnsWidget);
}

void QTrayIcon::initBottomMenu()
{
    QWidget* bottomWidget = new QWidget();
    m_bottomWidgetAction = new QWidgetAction(m_trayMenu);

    m_pUpdateBtn = new QPushButton(QIcon(":/images/update.png"), tr("Update"));
    m_pUpdateBtn->setObjectName(QString("TrayButton"));
    m_pUpdateBtn->setFixedSize(60, 25);

    m_pAboutBtn = new QPushButton(QIcon(":/images/about.png"), tr("About"));
    m_pAboutBtn->setObjectName(QString("TrayButton"));
    m_pAboutBtn->setFixedSize(60, 25);

    m_pExitBtn = new QPushButton(QIcon(":/images/quit.png"), tr("Exit"));
    m_pExitBtn->setObjectName(QString("TrayButton"));
    m_pExitBtn->setFixedSize(60, 25);

    QHBoxLayout* m_bottomLayout = new QHBoxLayout();
    m_bottomLayout->addWidget(m_pUpdateBtn, 0, Qt::AlignCenter);
    m_bottomLayout->addWidget(m_pAboutBtn, 0, Qt::AlignCenter);
    m_bottomLayout->addWidget(m_pExitBtn, 0, Qt::AlignCenter);

    m_bottomLayout->setSpacing(5);
    m_bottomLayout->setContentsMargins(5,5,5,5);

    bottomWidget->setLayout(m_bottomLayout);
    m_bottomWidgetAction->setDefaultWidget(bottomWidget);
}

void QTrayIcon::addMenus()
{
    m_trayMenu->addAction(m_topWidgetAction);
    m_trayMenu->addAction(m_msgWidgetAction);
    m_trayMenu->addSeparator();
    m_trayMenu->addAction(m_btnsWidgetAction);
    m_trayMenu->addAction(m_bottomWidgetAction);
}
