#include "qcutscreenitem.h"
#include <qcutscreenscene.h>
#include <QPoint>
#include <QCursor>
#include <QPainter>
#include <QPen>

QCSIManager::QCSIManager(QGraphicsScene *scene)
            :m_scene(scene)
{

}

void QCSIManager::addItem(int id, QCutScreenItem *item)
{
    m_QCSItems.insert(id,item);
}

void QCSIManager::removeItem(int id)
{
    auto it = m_QCSItems.find(id);
    if(it != m_QCSItems.end()){
        auto item = it.value();
        m_QCSItems.remove(id);
        m_scene->removeItem(dynamic_cast<QGraphicsItem*>(item));
        item->deleteLater();
    }
}

void QCSIManager::removeAllItems()
{
    auto it = m_QCSItems.begin();
    for(;it != m_QCSItems.end();it++)
    {
        auto item = it.value();
        m_scene->removeItem(dynamic_cast<QGraphicsItem*>(item));
        item->deleteLater();
    }
    m_QCSItems.clear();
}

void QCSIManager::updateAllItems()
{
    auto it = m_QCSItems.begin();
    for(;it != m_QCSItems.end();it++)
    {
        auto cur = it.value();
        cur->setItemSelected(true);
        cur->update();
    }
}

bool QCSIManager::getSelectedRect(QRect &rect)
{
    auto it = m_QCSItems.begin();
    for(;it != m_QCSItems.end();it++)
    {
        auto cur = it.value();
        if(cur->isContainCursor()){
            rect = cur->getRect();
            return true;
        }
    }
    return false;
}

QCutScreenItem::QCutScreenItem(QCSIParam param,QGraphicsItem *parent)
         :QGraphicsObject(parent)
         ,m_width(param.width)
         ,m_height(param.height)
         ,m_text(param.text)
         ,m_bSel(false)
{

}

QRect QCutScreenItem::getRect()
{
     return QRect(pos().x(),pos().y(),m_width,m_height);
}

QRectF QCutScreenItem::boundingRect() const
{
    return QRectF(0,0,m_width,m_height);
}

void QCutScreenItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF rcText(0, 0, m_width, m_height);

    QPen pen;
    pen.setWidth(4);
    pen.setColor((isContainCursor()&&m_bSel)?QColor("#00ff00"):QColor("#00ffff"));
    pen.setStyle(Qt::SolidLine);

    QFont font;
    font.setPointSize(96);
    font.setFamily("Microsoft YaHei");
    font.setLetterSpacing(QFont::AbsoluteSpacing,0);

    painter->setPen(pen);
    painter->setFont(font);
    painter->setRenderHints(QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    painter->drawRect(rcText);
    painter->drawText(rcText,Qt::AlignVCenter | Qt::AlignCenter,m_text);
}

bool QCutScreenItem::isContainCursor()
{
    QRect rect(pos().x(),pos().y(),m_width,m_height);
    return rect.contains(QCursor::pos());
}

