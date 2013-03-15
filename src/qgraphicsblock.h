#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class QGraphicsBlock : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit QGraphicsBlock(QObject *parent = 0);
    ~QGraphicsBlock();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    
public slots:

private:
    bool m_hovered;
    QRectF m_rect;
    QSizeF m_ioSize;
    QSizeF m_edge;
    int m_inputs;
    int m_outputs;
    int m_inputOffset;
    QColor m_backgroundColor;
};

#endif // BLOCK_H
