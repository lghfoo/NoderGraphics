#pragma once
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QMenu>
#include"op_node_graphics.hpp"
#include"value_node_graphics.hpp"
#include<functional>
#include<QTransform>
namespace Mather {
    class MainScene:public QGraphicsScene{

    private:
        MainScene(){}
    public:
        using MouseMoveHandler = std::function<void(QGraphicsSceneMouseEvent*)>;
        using PMouseMoveHandler = MouseMoveHandler*;
        using MouseDragMoveHandler = std::function<void(QGraphicsSceneDragDropEvent*)>;
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
        QPointF MapFromScreen(QPoint pos){
            auto view = this->views().first();
            if(view){
                return view->mapToScene(view->mapFromGlobal(pos));
            }
            return QPointF();
        }
    protected:
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event){
            for(auto handler : mouseMoveHandlers){
                (*handler)(event);
            }
            QGraphicsScene::mouseMoveEvent(event);
        }
        virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override{
//            qDebug()<<"scene drag enter";
            event->acceptProposedAction();
            QGraphicsScene::dragEnterEvent(event);
        }
        virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event)override{
//            qDebug()<<"scene drag move";
            for(auto handler : mouseDragMoveHandlers){
                (*handler)(event);
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
//            Int64AddNodeGraphics* node_graphics = new Int64AddNodeGraphics;
//            scene->addItem(node_graphics);
            this->setRenderHint(QPainter::Antialiasing);
            this->setScene(scene);
            this->setMinimumSize(800, 600);
            InitContextMenu();
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
    public slots:
        void OnRightClick(const QPoint& pos){
            QPoint globalPos = this->mapToGlobal(pos);
            QAction* selectedItem = right_click_menu->exec(globalPos);
            if (selectedItem)
            {
                if(selectedItem == int64_add_node_action){
                    scene->addItem(new Int64AddNodeGraphics);
                }
                else if(selectedItem == int64_value_node_action){
                    scene->addItem(new Int64ValueNodeGraphics);
                }
            }
        }
    public:
//        void mousePressEvent(QMouseEvent* event){
//            auto item = scene->itemAt(event->pos(), QTransform());
//            QGraphicsProxyWidget* proxy_widget = static_cast<QGraphicsProxyWidget*>(item);
//            if(proxy_widget){
//                qDebug()<<"xxx";
//            }
//            else{
//                qDebug()<<"item is null";
//            }
//            QGraphicsView::mousePressEvent(event);
//        }
    };
}
