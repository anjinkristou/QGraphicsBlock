#include "qgraphicsblock.h"
#include <QDebug>

QGraphicsBlock::QGraphicsBlock(QObject *parent) :
    QObject(parent),
    m_rect(-100, -50, 200, 100),
    m_ioSize(20, 20),
    m_edge(5, 5),
    m_inputs(2),
    m_outputs(2),
    m_inputOffset(30),
    m_pen(Qt::black),
    m_highlightPen(Qt::red),
    m_currentInput(-1),
    m_currentOutput(-1)
{
    m_pen.setWidth(1);
    m_highlightPen.setWidth(1);
    setFlag(ItemIsMovable);
    m_hovered = false;
    setAcceptHoverEvents(true);
}

QRectF QGraphicsBlock::boundingRect() const
{
    return m_rect;
}

void QGraphicsBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(QBrush(m_hovered ? Qt::lightGray : Qt::white));
    painter->drawRoundedRect(m_rect, 5, 5);

    painter->setPen(m_pen);
    //    painter->drawText(-20, -30, "test block");
    QPainterPath path1;
    path1.addRoundedRect(m_rect.adjusted(m_edge.width() *2, m_edge.height(), -(m_ioSize.width() + (m_edge.width() *2)), -m_edge.height()), 5, 5);
    QPainterPath path2;
    path2.addRect(QRectF(m_rect.x(), m_rect.y() + m_inputOffset, m_ioSize.width() + (m_edge.width() * 2), m_rect.height()));
    path1 = path1.subtracted(path2);
    painter->setBrush(QBrush(Qt::white));
    painter->drawPath(path1);

    for(int i = 0; i < m_inputs; i++){
        int xPos = m_rect.x() +5;
        int yPos = m_rect.y() + m_inputOffset +5 + ((m_ioSize.height() +5) * i);
        QRectF itemRect(xPos, yPos, m_ioSize.width(), m_ioSize.height());
        painter->setPen(m_currentInput == i ? m_highlightPen : m_pen);
        painter->drawRect(itemRect);
    }

    for(int i = 0; i < m_outputs; i++){
        int xPos = m_rect.x() + m_rect.width() - m_ioSize.width() - m_edge.width();
        int yPos = m_rect.y() +5 + ((m_ioSize.height() +5) * i);
        QRectF itemRect(xPos, yPos, m_ioSize.width(), m_ioSize.height());
        painter->setPen(m_currentOutput == i ? m_highlightPen : m_pen);
        painter->drawRect(itemRect);
    }
}

void QGraphicsBlock::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    m_hovered = true;
    update();
}

void QGraphicsBlock::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    m_hovered = false;
    m_currentInput = -1;
    m_currentOutput = -1;
    update();
}

void QGraphicsBlock::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    m_currentInput = getInputId(event->pos());
    m_currentOutput = getOutputId(event->pos());
    update();
    QGraphicsItem::hoverMoveEvent(event);
}

void QGraphicsBlock::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int inputId = getInputId(event->pos());
    int outputId = getOutputId(event->pos());
    setFlag(ItemIsMovable, inputId < 0 && outputId < 0);

    if(inputId >= 0){
        emit inputClicked(inputId);
    }
    if(outputId >= 0){
        emit outputClicked(outputId);
    }


    QGraphicsItem::mousePressEvent(event);
    qDebug() << "mousePressEvent: " << m_id;
}

void QGraphicsBlock::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setFlag(ItemIsMovable);
    QGraphicsItem::mouseReleaseEvent(event);
    qDebug() << "mouseReleaseEvent: " << m_id;
}

QPointF QGraphicsBlock::getInputPos(int index)
{
    int xPos = m_rect.x() +5;
    int yPos = m_rect.y() + m_inputOffset +5 + ((m_ioSize.height() +5) * index) + (m_ioSize.height() /2);
    return mapToScene(xPos, yPos);
}

QPointF QGraphicsBlock::getOutputPos(int index)
{
    int xPos = m_rect.x() + m_rect.width() - 5;
    int yPos = m_rect.y() +5 + ((m_ioSize.height() +5) * index) + (m_ioSize.height() /2);
    return mapToScene(xPos, yPos);
}

void QGraphicsBlock::setId(int id)
{
    m_id = id;
}

int QGraphicsBlock::getId()
{
    return m_id;
}


int QGraphicsBlock::getInputId(QPointF pos)
{
    for(int i = 0; i < m_inputs; i++){
        int xPos = m_rect.x() +5;
        int yPos = m_rect.y() + m_inputOffset +5 + ((m_ioSize.height() +5) * i);
        QRectF itemRect(xPos, yPos, m_ioSize.width(), m_ioSize.height());
        if(itemRect.contains(pos)){
            return i;
        }
    }
    return -1;
}

int QGraphicsBlock::getOutputId(QPointF pos)
{
    for(int i = 0; i < m_outputs; i++){
        int xPos = m_rect.x() + m_rect.width() - m_ioSize.width() - m_edge.width();
        int yPos = m_rect.y() +5 + ((m_ioSize.height() +5) * i);
        QRectF itemRect(xPos, yPos, m_ioSize.width(), m_ioSize.height());
        if(itemRect.contains(pos)){
            return i;
        }
    }
    return -1;
}
