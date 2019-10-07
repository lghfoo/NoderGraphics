#pragma once
#include<QPaintEvent>
#include<QWidget>
#include<QPainter>
#include<QPainterPath>
#include<QDragEnterEvent>
#include<QDragLeaveEvent>
#include<QDragMoveEvent>
#include<QDrag>
#include<QDropEvent>
#include<QDebug>
#include<QMimeData>
#include<functional>
#include"../core/node_graphics.hpp"
namespace NoderGraphics {
    class PortWidget:public QWidget{
        Q_OBJECT
    public:
        using DragBeginHandler = std::function<void(PortWidget*)>;
        using DropHandler = std::function<void(PortWidget*)>;
        using PosChangedHandler = std::function<void(const QPoint&)>;
        using PPosChangedHandler = PosChangedHandler*;
        using IgnoreDropHandler = std::function<void(void)>;
        PortWidget(qreal radius = 6.0){
            this->SetRadius(radius);
            this->setAcceptDrops(true);
            QPalette palette = this->palette();
            palette.setColor(QPalette::Background, Qt::transparent);
            this->setPalette(palette);
        }
        void paintEvent(QPaintEvent* event) override{
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            QPainterPath path;
            path.addEllipse(QRectF(padding, padding, radius * 2, radius * 2));
            painter.fillPath(path, QBrush(Qt::black));
        }
        void SetRadius(qreal radius){
            this->radius = radius;
            UpdateGeometry();
        }
        void SetPadding(qreal padding){
            this->padding = padding;
            UpdateGeometry();
        }
        void AddPosChangedHandler(PPosChangedHandler const& pos_changed_handler){
            pos_changed_handlers.append(pos_changed_handler);
        }
        void RemovePosChangedHandler(PPosChangedHandler const& pos_changed_handler){
            // todo delete
            pos_changed_handlers.removeOne(pos_changed_handler);
        }
        void UpdateGeometry(){
            this->setFixedSize((radius + padding) * 2, (radius + padding) * 2);
            this->update();
        }
        QPoint GetCenterOnScreen(){
            return this->mapToGlobal(QPoint(padding + radius, padding + radius));
        }
    private:
        qreal radius;
        qreal padding=5.0;
        QList<PPosChangedHandler> pos_changed_handlers = {};
        DragBeginHandler on_drag_begin_handler = nullptr;
        DropHandler on_drop_handler = nullptr;
        IgnoreDropHandler ignore_drop_handler = nullptr;
    public:
        void NotifyPosChanged(){
            for(auto handler : pos_changed_handlers){
                (*handler)(this->GetCenterOnScreen());
            }
        }
        void dragEnterEvent(QDragEnterEvent* event)override{
            event->acceptProposedAction();
        }
        void dragMoveEvent(QDragMoveEvent* event)override{
            event->acceptProposedAction();

        }
        void dropEvent(QDropEvent* event)override{
            auto handler = PortWidget::GetDropHandler();
            if(handler)
                handler(this);
            event->acceptProposedAction();
        }
        void mousePressEvent(QMouseEvent* event)override{
            auto handler = PortWidget::GetDragBeginHandler();
            if(handler)
                handler(this);
            QDrag* drag = new QDrag(this);
            QMimeData *data = new QMimeData;
            data->setText("commentEdit->toPlainText()");
            drag->setMimeData(data);
            Qt::DropAction dropAction = drag->exec();
            if(dropAction == Qt::IgnoreAction){
                auto ignore_drop_handler = PortWidget::GetIgnoreDropHandler();
                if(ignore_drop_handler){
                    ignore_drop_handler();
                }
            }

        }

        DragBeginHandler& GetDragBeginHandler(){
            return on_drag_begin_handler;
        }

        DropHandler& GetDropHandler(){
            return on_drop_handler;
        }

        IgnoreDropHandler& GetIgnoreDropHandler(){
            return ignore_drop_handler;
        }

        void SetDragBeginHandler(const DragBeginHandler& handler){
            this->on_drag_begin_handler = handler;
        }

        void SetDropHandler(const DropHandler& handler){
            this->on_drop_handler = handler;
        }

        void SetIgnoreDropHandler(const IgnoreDropHandler& handler){
            this->ignore_drop_handler = handler;
        }
    };
}
