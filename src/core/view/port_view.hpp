#pragma once
#include<QWidget>
#include<functional>
#include<QPainter>
#include<QDrag>
#include<QDropEvent>
#include<QGraphicsProxyWidget>
#include <QMimeData>
#include<Noder/src/core/utility/utility.hpp>
namespace NoderGraphics {
    using namespace Noder;
    class PortWidget:public QWidget{
        Q_OBJECT
    public:
        using DragBeginHandler = Listener<void>;//std::function<void(PortWidget*)>;
        using DropHandler = Listener<void>;//std::function<void(PortWidget*)>;
        using PosChangedHandler = Listener<void, const QPoint&>;//std::function<void(const QPoint&)>;
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
        QPoint GetCenterOnScreen(){
            return this->mapToGlobal(QPoint(padding + radius, padding + radius));
        }
    private:
        qreal radius;
        qreal padding=5.0;
        PosChangedHandler pos_changed_handler;
        DragBeginHandler on_drag_begin_handler = nullptr;
        DropHandler on_drop_handler = nullptr;
        IgnoreDropHandler ignore_drop_handler = nullptr;
    public:
        void NotifyPosChanged(){
            if(pos_changed_handler.IsValid()){
                pos_changed_handler(this->GetCenterOnScreen());
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
            if(handler.IsValid())
                handler();
            event->acceptProposedAction();
        }
        void mousePressEvent(QMouseEvent* event)override{
            auto handler = PortWidget::GetDragBeginHandler();
            if(handler.IsValid())
                handler();
            QDrag* drag = new QDrag(this);
            QMimeData *data = new QMimeData;
    //        data->setText("commentEdit->toPlainText()");
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

        void SetPosChangedHandler(const PosChangedHandler& handler){
            this->pos_changed_handler = handler;
        }
    };

    class PortView: public QGraphicsProxyWidget{
    public:
        using DragBeginHandler = Listener<void, PortView*>;
        using DropHandler = Listener<void, PortView*>;
        using PosChangedHandler = Listener<void, PortView*, const QPoint&>;
        using IgnoreDropHandler = Listener<void>;
    private:
        PortWidget widget;
        DragBeginHandler drag_begin_handler;
        DropHandler drop_handler;
        PosChangedHandler pos_changed_handler;
        IgnoreDropHandler ignore_drop_handler;
        QList<PosChangedHandler> pos_changed_handlers = {};
    public:
        PortView(){
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
            widget.SetPosChangedHandler([=](const QPoint& point){
                for(auto handler : pos_changed_handlers){
                    handler(this, point);
                }
            });
        }

        void NotifyPosChanged(){
            widget.NotifyPosChanged();
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
            return this->widget.GetCenterOnScreen();
        }
    };
}
