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
    m_backgroundColor(245, 245, 245)
{
    setFlag(ItemIsMovable);
    m_hovered = false;
    setAcceptHoverEvents(true);
}

QGraphicsBlock::~QGraphicsBlock()
{
}

QRectF QGraphicsBlock::boundingRect() const
{
    return m_rect;
}

void QGraphicsBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(QBrush(m_hovered ? m_backgroundColor : Qt::white));
    painter->drawRoundedRect(m_rect, 5, 5);
    painter->setPen(QPen(Qt::black));
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
        painter->drawRect(itemRect);
    }

    for(int i = 0; i < m_outputs; i++){
        int xPos = m_rect.x() + m_rect.width() - m_ioSize.width() - m_edge.width();
        int yPos = m_rect.y() +5 + ((m_ioSize.height() +5) * i);
        QRectF itemRect(xPos, yPos, m_ioSize.width(), m_ioSize.height());
        painter->drawRect(itemRect);
    }
}

void QGraphicsBlock::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_hovered = true;
    update();
}

void QGraphicsBlock::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_hovered = false;
    update();
}

void QGraphicsBlock::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    bool clickOnIO = false;
    for(int i = 0; i < m_inputs; i++){
        int xPos = m_rect.x() +5;
        int yPos = m_rect.y() + m_inputOffset +5 + ((m_ioSize.height() +5) * i);
        QRectF itemRect(xPos, yPos, m_ioSize.width(), m_ioSize.height());
        if(itemRect.contains(event->pos())){
            clickOnIO = true;
            break;
        }
    }

    if(!clickOnIO){
        for(int i = 0; i < m_outputs; i++){
            int xPos = m_rect.x() + m_rect.width() - m_ioSize.width() - m_edge.width();
            int yPos = m_rect.y() +5 + ((m_ioSize.height() +5) * i);
            QRectF itemRect(xPos, yPos, m_ioSize.width(), m_ioSize.height());
            if(itemRect.contains(event->pos())){
                clickOnIO = true;
                break;
            }
        }
    }

    setFlag(ItemIsMovable, !clickOnIO);

    QGraphicsItem::mousePressEvent(event);
}

void QGraphicsBlock::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setFlag(ItemIsMovable);
    QGraphicsItem::mouseReleaseEvent(event);
}
