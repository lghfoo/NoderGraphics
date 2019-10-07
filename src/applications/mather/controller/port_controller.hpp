#pragma once
#include"../view/main_view.hpp"
#include"../view/connection_graphics.hpp"
#include"../../../core/graphics_controller.hpp"
#include"../view/op_node_graphics.hpp"
#include"Noder/src/applications/mather/value_node.hpp"
namespace Mather {
    class PortController: public NoderGraphics::GraphicsController{
    private:
        using Node = Noder::Node;
        using NodeGraphics = NoderGraphics::NodeGraphics;
        using DragBeginHandler = std::function<void(Port*, NoderGraphics::PortWidget*)>;
        using DropHandler = std::function<void(Port*, NoderGraphics::PortWidget*)>;
        using PosChangedHandler = std::function<void(void)>;
        using PPosChangedHandler = PosChangedHandler*;
        using IgnoreDropHandler = std::function<void(void)>;
    protected:
        Port* port = nullptr;
        NoderGraphics::PortWidget* port_graphics = nullptr;
    public:
        PortController(Port* port,  NoderGraphics::PortWidget* port_graphics)
                            :port(port), port_graphics(port_graphics){
            this->port_graphics->SetDragBeginHandler([=](NoderGraphics::PortWidget* port_widget){
                auto handler = PortController::GetDragBeginHandler();
                handler(port, port_widget);
            });

            this->port_graphics->SetDropHandler([=](NoderGraphics::PortWidget* port_widget){
                auto handler = PortController::GetDropHandler();
                handler(port, port_widget);
            });
            this->port_graphics->SetIgnoreDropHandler([=]{
                auto handler = PortController::GetIgnoreDropHandler();
                handler();
            });

        }

        Port* GetPort(){
            return port;
        }

        NoderGraphics::PortWidget* GetPortGraphics(){
            return port_graphics;
        }

        static DragBeginHandler& GetDragBeginHandler(){
            static DragBeginHandler on_drag_begin_handler = nullptr;
            return on_drag_begin_handler;
        }

        static DropHandler& GetDropHandler(){
            static DropHandler on_drop_handler = nullptr;
            return on_drop_handler;
        }

        static IgnoreDropHandler& GetIgnoreDropHandler(){
            static IgnoreDropHandler ignore_drop_handler = nullptr;
            return ignore_drop_handler;
        }

        static void SetDragBeginHandler(const DragBeginHandler& handler){
            GetDragBeginHandler() = handler;
        }

        static void SetDropHandler(const DropHandler& handler){
            GetDropHandler() = handler;
        }

        static void SetIgnoreDropHandler(const IgnoreDropHandler& handler){
            GetIgnoreDropHandler() = handler;
        }
    };
}
