#include "qcutscreenview.h"
#include <qcutscreenscene.h>
#include <qcutscreenitem.h>

QCutScreenView::QCutScreenView(QCutScreenScene *scene,int width,int height,QWidget *parent)
            :QGraphicsView((QGraphicsScene*)scene, parent)
            ,m_scene(scene)
            ,m_width(width)
            ,m_height(height)
{
    m_qcsiMgr = new QCSIManager(m_scene);
    setMinimumSize(m_width,m_height);
    setBkColor();
}

void QCutScreenView::setBkColor()
{
    QPalette palette;
    QColor color;
    color.setRgb(97,111,118);
    color.setAlphaF(0.3);
    palette.setBrush(backgroundRole(), color);
    setPalette(palette);
    setStyleSheet("border:0px");
}

void QCutScreenView::addItem(int xStart, int yStart, int width, int height, int partId)
{
    assert(m_qcsiMgr);
    QCutScreenItem::QCSIParam param;
    param.width  = width;
    param.height = height;
    param.text   = QString::number(partId);
    param.id     = partId;

    QCutScreenItem * item = new QCutScreenItem(param);
    item->setPos(xStart,yStart);
    m_scene->addItem(item);
    m_qcsiMgr->addItem(partId,item);
}

void QCutScreenView::createCutScreen(int type)
{
     if(m_qcsiMgr){
         m_qcsiMgr->removeAllItems();
     }

     switch(type){
      case 1:
         addItem(0,0,m_width,m_height,1);
         break;
      case 2:
         addItem(0,0,m_width/2,m_height,1);
         addItem(m_width/2,0,m_width/2,m_height,2);
        break;
     case 3:
         addItem(0,0,m_width,m_height/2,1);
         addItem(0,m_height/2,m_width,m_height/2,2);
         break;
     case 4:
         addItem(0,0,m_width/3,m_height,1);
         addItem(m_width/3,0,m_width/3,m_height,2);
         addItem(2*m_width/3,0,m_width/3,m_height,3);
        break;
     case 5:
         addItem(0,0,m_width/2,m_height,1);
         addItem(m_width/2,0,m_width/2,m_height/2,2);
         addItem(m_width/2,m_height/2,m_width/2,m_height/2,3);
         break;
     case 6:
         addItem(0,0,m_width/2,m_height/2,1);
         addItem(0,m_height/2,m_width/2,m_height/2,2);
         addItem(m_width/2,0,m_width/2,m_height,3);
         break;
     case 7:
         addItem(0,0,m_width/2,m_height/2,1);
         addItem(m_width/2,0,m_width/2,m_height/2,2);
         addItem(0,m_height/2,m_width/2,m_height/2,3);
         addItem(m_width/2,m_height/2,m_width/2,m_height/2,4);
         break;
     case 8:
         addItem(0,0,m_width/4,m_height/2,1);
         addItem(0,m_height/2,m_width/4,m_height/2,2);
         addItem(m_width/4,0,3*m_width/4,m_height,3);
      break;
     case 9:
         addItem(0,0,3*m_width/4,m_height,1);
         addItem(3*m_width/4,0,m_width/4,m_height/2,2);
         addItem(3*m_width/4,m_height/2,m_width/4,m_height/2,3);
      break;
     case 10:
         addItem(0,0,m_width/4,m_height,1);
         addItem(m_width/4,0,m_width/4,m_height,2);
         addItem(m_width/2,0,m_width/4,m_height,3);
         addItem(3*m_width/4,0,m_width/4,m_height,4);
      break;
     case 11:
         addItem(0,0,m_width/4,m_height/2,1);
         addItem(m_width/4,0,m_width/4,m_height/2,2);
         addItem(0,m_height/2,m_width/4,m_height/2,3);
         addItem(m_width/4,m_height/2,m_width/4,m_height/2,4);
         addItem(m_width/2,0,m_width/2,m_height,5);
      break;
      case 12:
         addItem(0,0,m_width/2,m_height,1);
         addItem(m_width/2,0,m_width/4,m_height/2,2);
         addItem(3*m_width/4,0,m_width/4,m_height/2,3);
         addItem(m_width/2,m_height/2,m_width/4,m_height/2,4);
         addItem(3*m_width/4,m_height/2,m_width/4,m_height/2,5);
      break;
      case 13:
         addItem(0,0,m_width,m_height/2,1);
         addItem(0,m_height/2,m_width/4,m_height/2,2);
         addItem(m_width/4,m_height/2,m_width/4,m_height/2,3);
         addItem(m_width/2,m_height/2,m_width/4,m_height/2,4);
         addItem(3*m_width/4,m_height/2,m_width/4,m_height/2,5);
      break;
     case 14:
          addItem(0,0,m_width/4,m_height/2,1);
          addItem(m_width/4,0,m_width/4,m_height/2,2);
          addItem(m_width/2,0,m_width/4,m_height/2,3);
          addItem(3*m_width/4,0,m_width/4,m_height/2,4);
          addItem(0,m_height/2,m_width,m_height/2,5);
       break;
      case 15:
          addItem(0,0,m_width/4,m_height/2,1);
          addItem(m_width/4,0,m_width/4,m_height/2,2);
          addItem(m_width/2,0,m_width/4,m_height/2,3);
          addItem(3*m_width/4,0,m_width/4,m_height,4);
          addItem(0,m_height/2,m_width/4,m_height/2,5);
          addItem(m_width/4,m_height/2,m_width/4,m_height/2,6);
          addItem(m_width/2,m_height/2,m_width/4,m_height/2,7);
        break;
     case 16:
         addItem(0,0,m_width/4,m_height,1);
         addItem(m_width/4,0,m_width/4,m_height/2,2);
         addItem(m_width/2,0,m_width/4,m_height/2,3);
         addItem(3*m_width/4,0,m_width/4,m_height/2,4);
         addItem(m_width/4,m_height/2,m_width/4,m_height/2,5);
         addItem(m_width/2,m_height/2,m_width/4,m_height/2,6);
         addItem(3*m_width/4,m_height/2,m_width/4,m_height/2,7);
       break;
      case 17:
         addItem(0,0,m_width/4,m_height/2,1);
         addItem(m_width/4,0,m_width/4,m_height/2,2);
         addItem(m_width/2,0,m_width/4,m_height/2,3);
         addItem(3*m_width/4,0,m_width/4,m_height/2,4);
         addItem(0,m_height/2,m_width/4,m_height/2,5);
         addItem(m_width/4,m_height/2,m_width/4,m_height/2,6);
         addItem(m_width/2,m_height/2,m_width/4,m_height/2,7);
         addItem(3*m_width/4,m_height/2,m_width/4,m_height/2,8);
       break;
     }
}

void QCutScreenView::updateCutScreen()
{
    if(m_qcsiMgr){
        m_qcsiMgr->updateAllItems();
    }
}
