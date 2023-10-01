#ifndef QCUTSCREENITEM_H
#define QCUTSCREENITEM_H
#include <QGraphicsObject>

class QCutScreenItem;
class QCSIManager : public QObject
{
   Q_OBJECT
public:
   explicit QCSIManager(QGraphicsScene *scene);

   void addItem(int id, QCutScreenItem *item);
   void removeItem(int id);
   void removeAllItems();
   void updateAllItems();
   bool getSelectedRect(QRect& rect);

   QMap<int, QCutScreenItem*> m_QCSItems;

private:
    QGraphicsScene *m_scene;
};

class QCutScreenItem : public QGraphicsObject
{
    Q_OBJECT
public:
    struct QCSIParam{
        int id;
        int width;
        int height;
        QString text;
    };

    explicit QCutScreenItem(QCSIParam param,QGraphicsItem *parent = 0);
    QRect getRect();
    bool isContainCursor();
    void setItemSelected(bool bSel){m_bSel = bSel;}

 protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    bool m_bSel;
    int m_width;
    int m_height;
    QString m_text;
};

#endif // QCUTSCREENITEM_H
