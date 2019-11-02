#pragma once
#include<QGraphicsWidget>
#include<QDebug>
#include <QStyle>
#include<QPainter>
#include<QGraphicsProxyWidget>
#include<QGraphicsSceneWheelEvent>
#include <QGraphicsGridLayout>
#include <qsizepolicy.h>
namespace NoderGraphics {
    class WidgetProxy : public QGraphicsProxyWidget {
    public:
        virtual void NotifyPosChanged(){}
        template<typename T>
        T* GetWidget(){
            return static_cast<T*>(this->widget());
        }

        QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)override{
            if(change == ItemPositionHasChanged && scene()){
                this->NotifyPosChanged();
            }
            return value;
        }


        virtual void resizeEvent(QGraphicsSceneResizeEvent *event) override{
            QGraphicsProxyWidget::resizeEvent(event);
        }
    };

    class NodeGraphics: public QGraphicsWidget{
    protected:
        QList<WidgetProxy*> uis = {};
        QVariant itemChange(GraphicsItemChange change, const QVariant &value)
        {
            if (change == ItemPositionHasChanged && scene()) {
                this->NotifyPosChanged();
            }
            return QGraphicsItem::itemChange(change, value);
        }
    public:
        void NotifyPosChanged(){
            for(auto ui : uis){
                ui->NotifyPosChanged();
            }
        }
        template<typename T>
        T* GetUI(int id){
            return static_cast<T*>(uis[id]);
        }
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
//        NodeLayoutBuilder(){
//        }
        NodeLayoutBuilder(QList<WidgetProxy*>* proxies, int ui_count){
            widget_proxies = proxies;
            widget_proxies->clear();
            while(widget_proxies->size() < ui_count){
                widget_proxies->append(nullptr);
            }
        }
        QGraphicsLayout* Layout(){
            return layout;
        }

        NodeLayoutBuilder& NextRow(){
            row++;
            column = 0;
            return *this;
        }

        NodeLayoutBuilder& Skip(){
            return NextColumn();
        }

        NodeLayoutBuilder& NextColumn(){
            column++;
            return *this;
        }

        NodeLayoutBuilder& Add(int id, WidgetProxy* proxy){
            return Add(id, proxy, row, column);
        }

        NodeLayoutBuilder& Add(WidgetProxy* proxy){
            return Add(proxy, row, column);
        }

        NodeLayoutBuilder& Add(int id, WidgetProxy* proxy, int row, int column){
            return Add(id, proxy, row, column, current_row_span, current_column_span);
        }

        NodeLayoutBuilder& Add(WidgetProxy* proxy, int row, int column){
            return Add(proxy, row, column, current_row_span, current_column_span);
        }

        NodeLayoutBuilder& Add(int id, WidgetProxy* proxy, int row, int column, int row_span, int column_span){
            layout->addItem(proxy, this->row = row, column, row_span, column_span, alignment);
            this->column = column + column_span;
            if(widget_proxies && id < widget_proxies->size())
                (*widget_proxies)[id] = proxy;
            return *this;
        }

        NodeLayoutBuilder& Add(WidgetProxy* proxy, int row, int column, int row_span, int column_span){
            layout->addItem(proxy, this->row = row, column, row_span, column_span, alignment);
            this->column = column + column_span;
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
