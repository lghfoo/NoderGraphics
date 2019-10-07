#pragma once
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QMenu>
#include"op_node_graphics.hpp"
#include"value_node_graphics.hpp"
#include<functional>
#include<QTransform>
#include<QGraphicsSceneWheelEvent>
namespace Mather {
    class EmptyItem : public QGraphicsItem{
    public:
        QRectF boundingRect() const override
        {
            return QRectF();
        }
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
        {
        }
    };

    class CursorItem : public QGraphicsItem{
    public:
        QRectF boundingRect() const override
        {
            return QRectF(-outer_radius / 2.0, -outer_radius / 2.0, outer_radius, outer_radius);
        }
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
        {
            QPen pen = painter->pen();
            pen.setWidth(2);
            pen.setColor(Qt::white);
            painter->setPen(pen);
            auto cycle = QRectF(-radius / 2.0, -radius / 2.0, radius, radius);
            painter->drawEllipse(cycle);
        }
    private:
        qreal radius = 35.0;
        qreal inner_radius = 5.0;
        qreal outer_radius = radius + 5.0;
    };

    class MainScene:public QGraphicsScene{
    private:
        EmptyItem* root_item = new EmptyItem();
        CursorItem* cursor_item = new CursorItem();
        MainScene(){
            this->setBackgroundBrush(QImage(":/images/tile.png"));
            this->addItem(root_item);
            this->addItem(cursor_item);
        }
    public:
        using MouseMoveHandler = std::function<void(QGraphicsSceneMouseEvent*)>;
        using PMouseMoveHandler = MouseMoveHandler*;
        using MouseDragMoveHandler = std::function<void(const QPointF& pos)>;
        using PMouseDragMoveHandler = MouseDragMoveHandler*;
        QList<PMouseMoveHandler> mouseMoveHandlers = {};
        QList<PMouseDragMoveHandler> mouseDragMoveHandlers = {};
        static MainScene* GetInstance(){
            static MainScene* main_scene = new MainScene;
            return main_scene;
        }
        void AddMouseMoveHandler(PMouseMoveHandler const& handler){
            mouseMoveHandlers.append(handler);
        }
        void AddMouseDragMoveHandler(PMouseDragMoveHandler const& handler){
            mouseDragMoveHandlers.append(handler);
        }
        void RemoveMouseMoveHandler(PMouseMoveHandler const& handler){
            mouseMoveHandlers.removeOne(handler);
            // todo delete
        }
        void RemoveMouseDragMoveHandler(PMouseDragMoveHandler const& handler){
            mouseDragMoveHandlers.removeOne(handler);
            // todo delete
        }
        // todo: map error
        QPointF MapFromScreen(QPoint pos){
            auto view = this->views().first();
            if(view){
                return root_item->mapFromScene(view->mapToScene(view->mapFromGlobal(pos)));
            }
            return QPointF();
        }

        void AddItem(QGraphicsItem* item){
            item->setParentItem(root_item);
            item->setPos(root_item->mapFromScene(cursor_item->pos()));
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
                QApplication::setOverrideCursor(QCursor(Qt::ClosedHandCursor));
            }
            else{
                QGraphicsScene::mousePressEvent(event);
                if(event->isAccepted())return;
                cursor_item->setPos(event->scenePos());
            }
        }

        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override{
            if(event->button() & Qt::MiddleButton){
                QApplication::restoreOverrideCursor();
            }
            QGraphicsScene::mouseReleaseEvent(event);
        }

        void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)override{
            QGraphicsScene::wheelEvent(wheelEvent);
            if(wheelEvent->isAccepted())return;
            double scale = 1.0;
            double down = 1.05;
            if(wheelEvent->delta() > 0){
                scale = down;
//                root_item->setScale(root_item->scale() + 0.1);
            }
            else if(wheelEvent->delta()<0){
                scale = 1 / down;
//                root_item->setScale(root_item->scale() - 0.1);
            }
            auto pos = root_item->mapFromScene(wheelEvent->scenePos());
            auto transform = root_item->transform();
            root_item->setTransform(transform.translate(pos.x(), pos.y()).scale(scale, scale).translate(-pos.x(), -pos.y()));
        }


        virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override{
//            qDebug()<<"scene drag enter";
            event->acceptProposedAction();
            QGraphicsScene::dragEnterEvent(event);
        }
        virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event)override{
//            qDebug()<<"scene drag move";
            for(auto handler : mouseDragMoveHandlers){
                (*handler)(root_item->mapFromScene(event->scenePos()));
            }
            event->acceptProposedAction();
            QGraphicsScene::dragMoveEvent(event);
        }
        virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event)override{
//            qDebug()<<"scene drag leave";
            event->acceptProposedAction();
            QGraphicsScene::dragLeaveEvent(event);
        }
    };

    class MainView:public QGraphicsView{
        Q_OBJECT
    public:
        MainView(){
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            this->setRenderHint(QPainter::Antialiasing);
            this->setScene(scene);
            this->setMinimumSize(800, 600);
            InitContextMenu();
        }

        void scrollContentsBy(int, int)override
        {
            //don't do anything hah!
        }

    private:
        void InitContextMenu(){
            this->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(this, &QWidget::customContextMenuRequested,
                    this, &MainView::OnRightClick);
            right_click_menu->addMenu(op_node_menu);
            right_click_menu->addMenu(value_node_menu);
            right_click_menu->addMenu(function_node_menu);

            op_node_menu->addMenu(add_operation_node_menu);
            op_node_menu->addMenu(substract_operation_node_menu);
            op_node_menu->addMenu(multiply_operation_node_menu);
            op_node_menu->addMenu(divide_operation_node_menu);
            op_node_menu->addMenu(minus_operation_node_menu);

            value_node_menu->addAction(int64_value_node_action);
            value_node_menu->addAction(double_value_node_action);

            add_operation_node_menu->addAction(int64_add_node_action);
            add_operation_node_menu->addAction(double_add_node_action);

            substract_operation_node_menu->addAction(int64_substract_node_action);
            substract_operation_node_menu->addAction(double_substract_node_action);

            multiply_operation_node_menu->addAction(int64_multiply_node_action);
            multiply_operation_node_menu->addAction(double_multiply_node_action);

            divide_operation_node_menu->addAction(int64_divide_node_action);
            divide_operation_node_menu->addAction(double_divide_node_action);

            minus_operation_node_menu->addAction(int64_minus_node_action);
            minus_operation_node_menu->addAction(double_minus_node_action);
        }
        QGraphicsScene* scene = MainScene::GetInstance();
        QMenu* right_click_menu = new QMenu;

        QMenu* op_node_menu = new QMenu("Operation");
        QMenu* add_operation_node_menu = new QMenu("Add");
        QAction* int64_add_node_action = new QAction("Int64");
        QAction* double_add_node_action = new QAction("Double");

        QMenu* substract_operation_node_menu = new QMenu("Substract");
        QAction* int64_substract_node_action = new QAction("Int64");
        QAction* double_substract_node_action = new QAction("Double");

        QMenu* multiply_operation_node_menu = new QMenu("Multiply");
        QAction* int64_multiply_node_action = new QAction("Int64");
        QAction* double_multiply_node_action = new QAction("Double");

        QMenu* divide_operation_node_menu = new QMenu("Divide");
        QAction* int64_divide_node_action = new QAction("Int64");
        QAction* double_divide_node_action = new QAction("Double");

        QMenu* minus_operation_node_menu = new QMenu("Minus");
        QAction* int64_minus_node_action = new QAction("Int64");
        QAction* double_minus_node_action = new QAction("Double");


        QMenu* value_node_menu = new QMenu("Value");
        QAction* int64_value_node_action = new QAction("Int64");
        QAction* double_value_node_action = new QAction("Double");

        QMenu* function_node_menu = new QMenu("Function");

    public:
        enum GraphicsType{
            INT64_ADD,
            INT64_VALUE
        };
    signals:
        void add_int64_add_node();
        void add_int64_value_node();
        void add_node(const GraphicsType& type);
    public slots:
        void OnRightClick(const QPoint& pos){
            QPoint globalPos = this->mapToGlobal(pos);
            QAction* selectedItem = right_click_menu->exec(globalPos);
            if (selectedItem)
            {
                if(selectedItem == int64_add_node_action){
                    emit add_node(INT64_ADD);
                }
                else if(selectedItem == int64_value_node_action){
                    emit add_node(INT64_VALUE);
                }
            }
        }

    };
}
