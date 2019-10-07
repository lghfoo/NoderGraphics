#pragma once
#include"../view/main_view.hpp"
#include"../view/connection_graphics.hpp"
#include"port_controller.hpp"
#include"Noder/src/core/noder/connection.hpp"
namespace Mather {
    class ConnectionController{
    private:
        PortController* src_port_controller = nullptr;
        PortController* dst_port_controller = nullptr;
        ConnectionGraphics* connection_graphics = nullptr;
        Connection* connection = nullptr;
    public:
        ConnectionController(){
            connection_graphics = new ConnectionGraphics();
            connection = new Connection();
            QPen pen;
            pen.setWidth(2);
            connection_graphics->setPen(pen);
        }
        ~ConnectionController(){
            connection_graphics->RemoveFromScene();
            if(src_port_controller && src_port_pos_changed_handler){
                src_port_controller->GetPortGraphics()->RemovePosChangedHandler(src_port_pos_changed_handler);
                delete src_port_pos_changed_handler;
                src_port_pos_changed_handler = nullptr;
            }
            if(dst_port_controller && dst_port_pos_changed_handler){
                dst_port_controller->GetPortGraphics()->RemovePosChangedHandler(dst_port_pos_changed_handler);
                delete dst_port_pos_changed_handler;
                dst_port_pos_changed_handler = nullptr;
            }
            if(connection){
                delete connection;
                connection = nullptr;
            }

        }
        void SetSrcPortController(PortController* src_port_controller){
            this->src_port_controller = src_port_controller;
            this->connection->SetSrcPort(src_port_controller->GetPort());
        }
        void SetDstPortController(PortController* dst_port_controller){
            this->dst_port_controller = dst_port_controller;
            this->connection->SetDstPort(dst_port_controller->GetPort());
        }
        static void Init(){
            auto scene = MainScene::GetInstance();
            scene->AddMouseDragMoveHandler(ConnectionController::GetMouseDragMoveHandler());
            PortController::SetDragBeginHandler([=](Port* port, NoderGraphics::PortWidget* src_ellipse){
                auto center = scene->MapFromScreen(src_ellipse->GetCenterOnScreen());
                auto connection = new ConnectionController();
                connection->SetSrcPortController(new PortController(port, src_ellipse));
                scene->AddItem(connection->connection_graphics);
                connection->connection_graphics->setLine(center.x(), center.y(), center.x(), center.y());
                src_ellipse->AddPosChangedHandler(connection->src_port_pos_changed_handler);
                SetCreatingConnection(connection);
            });
            PortController::SetDropHandler([=](Port* port, NoderGraphics::PortWidget* dst_ellipse){
                auto connection = ConnectionController::GetCreatingConnection();
                if(!connection)return;
                auto center = scene->MapFromScreen(dst_ellipse->GetCenterOnScreen());
                connection->connection_graphics->SetP2(center);
                connection->SetDstPortController(new PortController(port, dst_ellipse));
                ConnectionController::SetCreatingConnection(nullptr);
                dst_ellipse->AddPosChangedHandler(connection->dst_port_pos_changed_handler);
            });
            PortController::SetIgnoreDropHandler([=]{
                auto connection = ConnectionController::GetCreatingConnection();
                if(!connection)return;
                delete connection;
                ConnectionController::SetCreatingConnection(nullptr);
            });
        }
    private:
        NoderGraphics::PortWidget::PPosChangedHandler src_port_pos_changed_handler = new NoderGraphics::PortWidget::PosChangedHandler([=](const QPoint& center_on_screen){
            auto scene = MainScene::GetInstance();
            auto center = scene->MapFromScreen(center_on_screen);
            this->connection_graphics->SetP1(center);
        });
        NoderGraphics::PortWidget::PPosChangedHandler dst_port_pos_changed_handler = new NoderGraphics::PortWidget::PosChangedHandler([=](const QPoint& center_on_screen){
            auto scene = MainScene::GetInstance();
            auto center = scene->MapFromScreen(center_on_screen);
            this->connection_graphics->SetP2(center);
        });
        static MainScene::PMouseDragMoveHandler GetMouseDragMoveHandler(){
            static MainScene::PMouseDragMoveHandler mouse_drag_move_handler = new MainScene::MouseDragMoveHandler([=](const QPointF& pos){
                auto connection = GetCreatingConnection();
                if(connection != nullptr){
                    auto line = connection->connection_graphics->line();
                    line.setP2(pos);
                    connection->connection_graphics->setLine(line);
                }
            });
            return mouse_drag_move_handler;
        }

        static ConnectionController*& GetCreatingConnection(){
            static ConnectionController* ret = nullptr;
            return ret;
        }

        static void SetCreatingConnection(ConnectionController* const connection){
            GetCreatingConnection()=connection;
        }
    };
}
