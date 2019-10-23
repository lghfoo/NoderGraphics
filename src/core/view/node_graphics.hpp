#pragma once
#include<QGraphicsWidget>
#include<QDebug>
#include <QStyle>
#include<QPainter>
#include<QGraphicsProxyWidget>
#include<QGraphicsSceneWheelEvent>
#include <QGraphicsGridLayout>
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

    class WidgetProxy : public QGraphicsProxyWidget {

    };

    class NodeLayoutBuilder{
    private:
        int row = 0;
        int column = 0;
        int current_row_span = 1;
        int current_column_span = 1;
        QGraphicsGridLayout* layout = new QGraphicsGridLayout();
        QList<WidgetProxy*>* widget_proxies = nullptr;
        Qt::Alignment alignment = Qt::AlignCenter;
    public:
        NodeLayoutBuilder(){
        }
        NodeLayoutBuilder(QList<WidgetProxy*>* proxies){
            widget_proxies = proxies;
        }
        QGraphicsLayout* Layout(){
            return layout;
        }

        NodeLayoutBuilder& NextRow(){
            row++;
            return *this;
        }

        NodeLayoutBuilder& NextColumn(){
            column++;
            return *this;
        }

        NodeLayoutBuilder& Add(int id, WidgetProxy* proxy){
            this->Add(id, proxy, row, column);
            return *this;
        }

        NodeLayoutBuilder& Add(WidgetProxy* proxy){
            this->Add(proxy, row, column);
            return *this;
        }

        NodeLayoutBuilder& Add(int id, WidgetProxy* proxy, int row, int column){
            layout->addItem(proxy, this->row = row, (this->column = column)++, current_row_span, current_column_span, alignment);
            if(widget_proxies && id < widget_proxies->size())
                (*widget_proxies)[id] = proxy;
            return *this;
        }

        NodeLayoutBuilder& Add(WidgetProxy* proxy, int row, int column){
            layout->addItem(proxy, this->row = row, (this->column = column)++, current_row_span, current_column_span, alignment);
            return *this;
        }

        NodeLayoutBuilder& RowSpan(int rs){
            this->current_row_span = rs;
            return *this;
        }

        NodeLayoutBuilder& ColumnSpan(int cs){
            this->current_column_span = cs;
            return *this;
        }

        NodeLayoutBuilder& Span(int rs, int cs){
            this->current_row_span = rs;
            this->current_column_span = cs;
            return *this;
        }

        NodeLayoutBuilder& Align(Qt::Alignment align){
            this->alignment = align;
            return *this;
        }
    };
}
