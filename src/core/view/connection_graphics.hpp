#pragma once
#include<QGraphicsLineItem>
#include<QGraphicsScene>
#include<QPainter>
namespace NoderGraphics {
    class ConnectionGraphics:public QGraphicsLineItem{
    public:
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override{
            painter->setPen(this->pen());
            QPainterPath path;
            auto p1 = this->line().p1();
            auto p2 = this->line().p2();
            auto dp = p2 - p1;
            auto radio = 0.3;
            auto ctrlPt1 = QPointF(p1.x() + dp.x() * radio, p1.y());
            auto ctrlPt2 = QPointF(p2.x() - dp.x() * radio, p2.y());
            path.moveTo(p1);
            path.cubicTo(ctrlPt1, ctrlPt2, p2);
            painter->drawPath(path);
        }

        void SetP1(const QPointF& p1){
            auto l  = this->line();
            l.setP1(p1);
            this->setLine(l);
        }
        void SetP2(const QPointF& p2){
            auto l = this->line();
            l.setP2(p2);
            this->setLine(l);
        }

        void RemoveFromScene(){
            if(scene()){
                scene()->removeItem(this);
            }
        }
    };
}
