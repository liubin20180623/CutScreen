#ifndef QCUTSCREENSCENE_H
#define QCUTSCREENSCENE_H
#include <QGraphicsScene>

class QCutScreenScene : public QGraphicsScene
{
public:
    QCutScreenScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
};

#endif // QCUTSCREENSCENE_H
