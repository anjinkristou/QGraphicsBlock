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
    QRectF boundingRect() const;
    QPointF getInputPos(int index);
    QPointF getOutputPos(int index);
    int getInputId(QPointF pos);
    int getOutputId(QPointF pos);

    void setId(int id);
    int getId();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void inputClicked(int id);
    void outputClicked(int id);

public slots:

private:
    bool m_hovered;
    QRectF m_rect;
    QSizeF m_ioSize;
    QSizeF m_edge;
    int m_inputs;
    int m_outputs;
    int m_inputOffset;
    int m_id;
    QPen m_pen;
    QPen m_highlightPen;
    int m_currentInput;
    int m_currentOutput;

};

#endif // BLOCK_H
