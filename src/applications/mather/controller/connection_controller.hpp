#pragma once
#include"../view/main_view.hpp"
#include"../view/connection_graphics.hpp"
namespace Mather {
    class ConnectionController{
    public:
        ConnectionController(){
        }
        static void Init(){
            auto scene = MainScene::GetInstance();
//            scene->AddMouseMoveHandler(ConnectionController::GetMouseMoveHandler());
            scene->AddMouseDragMoveHandler(ConnectionController::GetMouseDragMoveHandler());
            PortWidget::SetDragBeginHandler([=](PortWidget* src_ellipse){
                ConnectionGraphics* connection = new ConnectionGraphics;
                QPen pen;
                pen.setWidth(2);
                connection->setPen(pen);
                scene->addItem(connection);
                auto center = scene->MapFromScreen(src_ellipse->GetCenterOnScreen());
                connection->setLine(center.x(), center.y(), center.x(), center.y());
                connection->SetSrcEllipse(src_ellipse);
                src_ellipse->AddPosChangedHandler(new PortWidget::PosChangedHandler([=]{
                    auto center = scene->MapFromScreen(src_ellipse->GetCenterOnScreen());
                    connection->SetP1(center);
                }));
                SetCreatingConnection(connection);
            });
            PortWidget::SetDropHandler([=](PortWidget* dst_ellipse){
                auto connection = ConnectionController::GetCreatingConnection();
                if(!connection)return;
                auto center = scene->MapFromScreen(dst_ellipse->GetCenterOnScreen());
                connection->SetP2(center);
                connection->SetDstEllipse(dst_ellipse);
                ConnectionController::SetCreatingConnection(nullptr);
                dst_ellipse->AddPosChangedHandler(new PortWidget::PosChangedHandler([=]{
                    auto center = scene->MapFromScreen(dst_ellipse->GetCenterOnScreen());
                    connection->SetP2(center);
                }));
            });
            PortWidget::SetIgnoreDropHandler([=]{
                auto connection = ConnectionController::GetCreatingConnection();
                if(!connection)return;
                connection->RemoveFromScene();
                delete connection;
                ConnectionController::SetCreatingConnection(nullptr);
            });
        }
    private:
//        static MainScene::PMouseMoveHandler GetMouseMoveHandler(){
//            static MainScene::PMouseMoveHandler mouse_move_handler = new MainScene::MouseMoveHandler([=](QGraphicsSceneMouseEvent* event){
//                auto connection = GetCreatingConnection();
//                if(connection != nullptr){
//                    auto line = connection->line();
//                    line.setP2(event->scenePos());
//                    connection->setLine(line);
//                }
//            });
//            return mouse_move_handler;
//        }
        static MainScene::PMouseDragMoveHandler GetMouseDragMoveHandler(){
            static MainScene::PMouseDragMoveHandler mouse_drag_move_handler = new MainScene::MouseDragMoveHandler([=](QGraphicsSceneDragDropEvent* event){
                auto connection = GetCreatingConnection();
                if(connection != nullptr){
                    auto line = connection->line();
                    line.setP2(event->scenePos());
                    connection->setLine(line);
                }
            });
            return mouse_drag_move_handler;
        }

        static ConnectionGraphics*& GetCreatingConnection(){
            static ConnectionGraphics* ret = nullptr;
            return ret;
        }

        static void SetCreatingConnection(ConnectionGraphics* const connection){
            GetCreatingConnection()=connection;
        }
    };
}
