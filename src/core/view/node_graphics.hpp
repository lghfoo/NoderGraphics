#pragma once
#include<QGraphicsWidget>
#include<QDebug>
#include <QStyle>
#include<QPainter>
#include<QGraphicsSceneWheelEvent>
namespace NoderGraphics {
    class NodeGraphics: public QGraphicsWidget{
    public:
        NodeGraphics(){
            this->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable);
            this->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);
        }

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override{
            // save painter
            painter->save();
            // get bound
            double padding = 1;
            auto bound = this->boundingRect();
            bound = QRectF(bound.x() + padding, bound.y() + padding, bound.width() - 2 * padding, bound.height() - 2 * padding);
            // fill bound: gray
            QPainterPath path;
            path.addRoundedRect(bound, 10, 10);
            painter->fillPath(path, Qt::gray);
            // draw boundary: black
            QPen pen = painter->pen();
            pen.setColor(Qt::black);
            pen.setWidth(2);
            painter->setPen(pen);
            painter->drawRoundedRect(bound, 10, 10);
            // restore painter
            painter->restore();
            QGraphicsWidget::paint(painter, option, widget);
        }

        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event)override{
            event->accept();
            QGraphicsWidget::mousePressEvent(event);
        }
    };
}
