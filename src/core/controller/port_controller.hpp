#pragma once
#include"../view/connection_graphics.hpp"
#include"../../core/view/port_view.hpp"
#include"graphics_controller.hpp"
#include"Noder/src/applications/mather/value_node.hpp"
namespace NoderGraphics {
    using namespace Noder;
    class PortController: public NoderGraphics::GraphicsController{
    private:
        using Node = Noder::Node;
        using DragBeginHandler = Listener<void, Port*, NoderGraphics::PortView*>;
        using DropHandler = Listener<void, Port*, NoderGraphics::PortView*>;
        using IgnoreDropHandler = Listener<void>;
    protected:
        Port* port = nullptr;
        NoderGraphics::PortView* port_graphics = nullptr;
    public:
        PortController(Port* port,  NoderGraphics::PortView* port_graphics)
                            :port(port), port_graphics(port_graphics){
            this->port_graphics->SetDragBeginHandler([=](NoderGraphics::PortView* port_widget){
                auto handler = PortController::GetDragBeginHandler();
                if(handler.IsValid()){
                    handler(port, port_widget);
                }
                else{
                    //todo: warning
                }
            });

            this->port_graphics->SetDropHandler([=](NoderGraphics::PortView* port_widget){
                auto handler = PortController::GetDropHandler();
                if(handler.IsValid()){
                    handler(port, port_widget);
                }
            });
            this->port_graphics->SetIgnoreDropHandler([=]{
                auto handler = PortController::GetIgnoreDropHandler();
                if(handler.IsValid()){
                    handler();
                }
            });

        }

        Port* GetPort(){
            return port;
        }

        NoderGraphics::PortView* GetPortGraphics(){
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
