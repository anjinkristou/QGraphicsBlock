#include "Scene.h"
#include "qgraphicsblock.h"
#include <QDebug>

Scene::Scene(QObject *parent) :
    QGraphicsScene(parent),
    m_line(NULL)
{
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    QGraphicsBlock *item;
    item = dynamic_cast<QGraphicsBlock *>(itemAt(event->scenePos())); //Get the item at the position
    if (item) //If there is an item at that position
    {
        int inputId = item->getInputId(item->mapFromScene(event->scenePos()));
        int outputId = item->getOutputId(item->mapFromScene(event->scenePos()));
        if(inputId >= 0){
            m_line = new QGraphicsLineItem();
            addItem(m_line);
            QPointF inputPos = item->getInputPos(inputId);
            m_line->setLine(QLineF(inputPos, inputPos));
        }
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if(m_line){
        QLineF line = m_line->line();
        line.setP2(event->scenePos());
        line.setLength(line.length() - 1);
        m_line->setLine(line);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if(m_line){
        QGraphicsBlock *item;
        item = dynamic_cast<QGraphicsBlock *>(itemAt(event->scenePos())); //Get the item at the position
        if (item) //If there is an item at that position
        {
            qDebug() << "block is " << item->getId();
            int inputId = item->getInputId(item->mapFromScene(event->scenePos()));
            int outputId = item->getOutputId(item->mapFromScene(event->scenePos()));
            if(outputId >= 0 && m_line){
                qDebug() << "Output " << outputId;
                QPointF outputPos = item->getOutputPos(outputId);
                QLineF line = m_line->line();
                line.setP2(outputPos);
                addLine(line);
            }
        }
        removeItem(m_line);
        delete m_line;
        m_line = NULL;
    }
}
