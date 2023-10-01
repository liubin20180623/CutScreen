#ifndef QCUTSCREENVIEW_H
#define QCUTSCREENVIEW_H
#include <QGraphicsView>

class QCSIManager;
class QCutScreenItem;
class QCutScreenScene;
class QCutScreenView : public QGraphicsView
{
public:
    QCutScreenView(QCutScreenScene *scene,int width,int height,QWidget *parent = 0);
    void createCutScreen(int type);
    void updateCutScreen();

protected:
   void setBkColor();
   void addItem(int xStart,int yStart,int width,int height,int partId);

public:
    QCSIManager* m_qcsiMgr;

private:
    QCutScreenScene* m_scene;
    int m_width;
    int m_height;
};

#endif // QCUTSCREENVIEW_H
