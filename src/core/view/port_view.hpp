#pragma once
#include "node_graphics.hpp"
#include<QWidget>
#include<functional>
#include<QPainter>
#include<QDrag>
#include<QDropEvent>
#include<QGraphicsProxyWidget>
#include <QMimeData>
#include <QGraphicsScene>
#include<QGraphicsView>
#include<Noder/src/core/utility/utility.hpp>
namespace NoderGraphics {
    using namespace Noder;
    class PortWidget:public QWidget{
        Q_OBJECT
    public:
        using DragBeginHandler = Listener<void>;//std::function<void(PortWidget*)>;
        using DropHandler = Listener<void>;//std::function<void(PortWidget*)>;
        using IgnoreDropHandler = Listener<void>;//std::function<void(void)>;
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
        void UpdateGeometry(){
            this->setFixedSize((radius + padding) * 2, (radius + padding) * 2);
            this->update();
        }
    private:
        qreal radius = 6.0;
        qreal padding = 5.0;
        DragBeginHandler on_drag_begin_handler = nullptr;
        DropHandler on_drop_handler = nullptr;
        IgnoreDropHandler ignore_drop_handler = nullptr;
    public:
        void dragEnterEvent(QDragEnterEvent* event)override{
            event->acceptProposedAction();
        }
        void dragMoveEvent(QDragMoveEvent* event)override{
            event->acceptProposedAction();

        }
        void dropEvent(QDropEvent* event)override{
            auto handler = PortWidget::GetDropHandler();
            if(handler.IsValid())
                handler();
            event->acceptProposedAction();
        }
        void mousePressEvent(QMouseEvent*)override{
            auto handler = PortWidget::GetDragBeginHandler();
            if(handler.IsValid())
                handler();
            QDrag* drag = new QDrag(this);
            QMimeData *data = new QMimeData;
            drag->setMimeData(data);
            Qt::DropAction dropAction = drag->exec();
            if(dropAction == Qt::IgnoreAction){
                auto ignore_drop_handler = PortWidget::GetIgnoreDropHandler();
                if(ignore_drop_handler.IsValid()){
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

    class PortProxy: public WidgetProxy{
    public:
        using DragBeginHandler = Listener<void, PortProxy*>;
        using DropHandler = Listener<void, PortProxy*>;
        using PosChangedHandler = Listener<void, PortProxy*, const QPoint&>;
        using IgnoreDropHandler = Listener<void>;
    private:
        PortWidget widget;
        DragBeginHandler drag_begin_handler;
        DropHandler drop_handler;
        PosChangedHandler pos_changed_handler;
        IgnoreDropHandler ignore_drop_handler;
        QList<PosChangedHandler> pos_changed_handlers = {};
    public:
        PortProxy(){
            this->setWidget(&widget);
            widget.SetDropHandler([=]{
                if(this->drop_handler.IsValid()){
                    this->drop_handler(this);
                }
            });
            widget.SetDragBeginHandler([=]{
                if(this->drag_begin_handler.IsValid()){
                    this->drag_begin_handler(this);
                }
            });
            widget.SetIgnoreDropHandler([=]{
                if(this->ignore_drop_handler.IsValid()){
                    this->ignore_drop_handler();
                }
            });

        }

        void NotifyPosChanged(){
            for(auto handler : pos_changed_handlers){
                handler(this, this->GetCenterOnScreen());
            }
        }

        void SetDragBeginHandler(const DragBeginHandler& handler){
            this->drag_begin_handler = handler;
        }

        void SetDropHandler(const DropHandler& handler){
            this->drop_handler = handler;
        }

        void SetIgnoreDropHandler(const IgnoreDropHandler& handler){
            this->ignore_drop_handler = handler;
        }

        void AddPosChangedHandler(const PosChangedHandler& pos_changed_handler){
            this->pos_changed_handlers.append(pos_changed_handler);
        }
        void RemovePosChangedHandler(const PosChangedHandler& pos_changed_handler){
            this->pos_changed_handlers.removeOne(pos_changed_handler);
        }

        QPoint GetCenterOnScreen(){
            auto center = this->boundingRect().center();
            auto center_in_scene = this->mapToScene(center);
            auto view = this->scene()->views().first();
            auto center_in_view = view->mapFromScene(center_in_scene);
            auto center_in_screen = view->mapToGlobal(center_in_view);
            return center_in_screen;
        }
    };
}
