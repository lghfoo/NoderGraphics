#pragma once
#include<QGraphicsItem>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QMenu>
#include<functional>
#include<QTransform>
#include<QGraphicsSceneWheelEvent>
#include <QApplication>
#include"Noder/src/core/utility/utility.hpp"
namespace NoderGraphics {
    using namespace Noder;
    class EmptyItem : public QGraphicsItem{
    public:
        QRectF boundingRect() const override
        {
            return QRectF();
        }
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override
        {
        }
    };

    class CursorItem : public QGraphicsItem{
    public:
        QRectF boundingRect() const override
        {
            return QRectF(-outer_radius, -outer_radius, outer_radius * 2, outer_radius * 2);
        }
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
        {
            QPen pen = painter->pen();
            pen.setWidth(2);
            pen.setColor(Qt::white);
            painter->setPen(pen);
            auto cycle = QRectF(-radius, -radius, radius * 2, radius * 2);
            painter->drawEllipse(cycle);

            pen.setCapStyle(Qt::PenCapStyle::RoundCap);
            painter->setPen(pen);
            constexpr int len = 4;
            qreal x0s[len] = {inner_radius, 0, -inner_radius, 0};
            qreal y0s[len] = {0, inner_radius, 0, -inner_radius};
            qreal x1s[len] = {outer_radius, 0, -outer_radius, 0};
            qreal y1s[len] = {0, outer_radius, 0, -outer_radius};
            for(int i = 0; i < len; i++){
                painter->drawLine(QLineF(x0s[i], y0s[i], x1s[i], y1s[i]));
            }

        }
    private:
        qreal radius = 12.0;
        qreal inner_radius = 6;
        qreal outer_radius = radius + 6;
    };

    class MainScene:public QGraphicsScene{
    public:
        using MouseMoveHandler = std::function<void(QGraphicsSceneMouseEvent*)>;
        using PMouseMoveHandler = MouseMoveHandler*;
        using MouseDragMoveHandler = Listener<void, const QPointF&>;
    private:
        EmptyItem* root_item = new EmptyItem();
        CursorItem* cursor_item = new CursorItem();
        QList<PMouseMoveHandler> mouseMoveHandlers = {};
        QList<MouseDragMoveHandler> mouseDragMoveHandlers = {};
    public:
        MainScene(){
            this->setBackgroundBrush(QImage(":/images/tile.png"));
            this->addItem(root_item);
            this->addItem(cursor_item);
        }

        void AddMouseMoveHandler(PMouseMoveHandler const& handler){
            mouseMoveHandlers.append(handler);
        }

        void AddMouseDragMoveHandler(MouseDragMoveHandler const& handler){
            mouseDragMoveHandlers.append(handler);
        }

        void RemoveMouseMoveHandler(PMouseMoveHandler const& handler){
            mouseMoveHandlers.removeOne(handler);
            // todo delete
        }

        void RemoveMouseDragMoveHandler(MouseDragMoveHandler const& handler){
            mouseDragMoveHandlers.removeOne(handler);
            // todo delete
        }

        QPointF MapFromScreen(QPoint pos){
            auto view = this->views().first();
            if(view){
                return root_item->mapFromScene(view->mapToScene(view->mapFromGlobal(pos)));
            }
            return QPointF();
        }

        void AddItemAtCursor(QGraphicsItem* item){
            item->setParentItem(root_item);
            item->setPos(root_item->mapFromScene(cursor_item->pos()));
        }

        void AddItem(QGraphicsItem* item){
            item->setParentItem(root_item);
        }
    protected:
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override{
            for(auto handler : mouseMoveHandlers){
                (*handler)(event);
            }
            if(event->buttons() & Qt::MiddleButton){
                auto dPos = event->scenePos() - event->lastScenePos();
                root_item->setPos(root_item->pos() + dPos);
                cursor_item->setPos(cursor_item->pos() + dPos);
            }
            else{
                QGraphicsScene::mouseMoveEvent(event);
            }
        }

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override{
            if(event->button() & Qt::MiddleButton){
                QGraphicsScene::mousePressEvent(event);
//                QApplication::setOverrideCursor(QCursor(Qt::ClosedHandCursor));
            }
            else{
                QGraphicsScene::mousePressEvent(event);
                if(event->isAccepted())return;
                cursor_item->setPos(event->scenePos());
            }
        }

        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override{
            // after drag, clear drag move handler
            this->mouseDragMoveHandlers.clear();
//            if(event->button() & Qt::MiddleButton){
//                QApplication::restoreOverrideCursor();
//            }
            QGraphicsScene::mouseReleaseEvent(event);
        }

        void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)override{
            QGraphicsScene::wheelEvent(wheelEvent);
            if(wheelEvent->isAccepted())return;
            double scale = 1.0;
            double down = 1.05;
            if(wheelEvent->delta() > 0){
                scale = down;
            }
            else if(wheelEvent->delta()<0){
                scale = 1 / down;
            }
            auto pos = root_item->mapFromScene(wheelEvent->scenePos());
            auto transform = root_item->transform();
            root_item->setTransform(transform.translate(pos.x(), pos.y()).scale(scale, scale).translate(-pos.x(), -pos.y()));
        }


        virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override{
            event->acceptProposedAction();
            QGraphicsScene::dragEnterEvent(event);
        }
        virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event)override{
            for(auto handler : mouseDragMoveHandlers){
                handler(root_item->mapFromScene(event->scenePos()));
            }
            event->acceptProposedAction();
            QGraphicsScene::dragMoveEvent(event);
        }
        virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event)override{
            event->acceptProposedAction();
            QGraphicsScene::dragLeaveEvent(event);
        }
    };

    class MainView:public QGraphicsView{
        Q_OBJECT
    public:
        using AddNodeHandler = Noder::Listener<void, MainView*>;
        void scrollContentsBy(int, int)override
        {
            //don't do anything hah!
        }

        void AddContextAction(const QString& action_path, const AddNodeHandler& handler){
            auto list = action_path.split(('/'));
            QMenu* last_menu = right_click_menu;
            auto prefix = QString("");
            for(int i = 0; i < list.length() - 1; i++){
                auto menu_text = list.at(i);
                auto menu_id = prefix + QString("_") + menu_text;
                prefix = menu_id;
                auto iter = context_menu_map.find(menu_id);
                // alreay exist
                if(iter != context_menu_map.end()){
                    last_menu = iter.value();
                }
                // new menu, insert
                else{
                    auto menu = new QMenu(menu_text);
                    context_menu_map.insert(menu_id, menu);
                    last_menu->addMenu(menu);
                    last_menu = menu;
                }
            }
            if(list.isEmpty()){
                return;
            }
            auto action_text = list.last();
            auto action_id = prefix + QString("_") + action_text;
            auto iter = context_action_map.find(action_id);
            // already exit, ignore
            // todo: raise warning
            if(iter != context_action_map.end()){
                return;
            }
            // add action
            else{
                auto action = new QAction(action_text);
                last_menu->addAction(action);
                this->context_action_map.insert(action_id, action);
                this->add_node_handler_map.insert(action, handler);
            }
        }
        MainView(){
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            this->setRenderHint(QPainter::Antialiasing);
            this->setScene(main_scene);
            this->setMinimumSize(800, 600);
            InitContextMenu();
        }

    private:
        void InitContextMenu(){
            this->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(this, &QWidget::customContextMenuRequested,
                    this, &MainView::OnRightClick);
        }
        QGraphicsScene* main_scene = new MainScene();
        QMenu* right_click_menu = new QMenu;
        QMap<QAction*, AddNodeHandler> add_node_handler_map = {};
        QMap<QString, QMenu*> context_menu_map = {};
        QMap<QString, QAction*> context_action_map = {};
    public slots:
        void OnRightClick(const QPoint& pos){
            QPoint globalPos = this->mapToGlobal(pos);
            QAction* selectedItem = right_click_menu->exec(globalPos);
            auto handler = add_node_handler_map.value(selectedItem);
            if(handler.IsValid()){
                handler(this);
            }
        }
    };
}
