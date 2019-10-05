#pragma once
#include<QGraphicsWidget>
#include<QDebug>
namespace NoderGraphics {
    class NodeGraphicsBase: public QGraphicsWidget{
//    protected:
//        QVariant itemChange(GraphicsItemChange change, const QVariant &value)
//        {
//            if (change == ItemPositionChange && scene()) {
//                // value is the new position.
//                qDebug()<<"item pos change";
//            }
//            return QGraphicsItem::itemChange(change, value);
//        }
    };
}
