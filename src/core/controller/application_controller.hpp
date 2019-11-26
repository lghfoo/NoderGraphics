#pragma once
#include<QMainWindow>
#include<QMap>
//#include"../model/application.hpp"
#include"../view/main_view.hpp"
#include"connection_controller.hpp"
#include"node_controller.hpp"
//#include"node_controller_factory.hpp"
namespace NoderGraphics {
    class ApplicationController{
        using AddNodeHandler = MainView::AddNodeHandler;
        template<typename NodeType, typename GraphicsType>
        using NodeController = NoderGraphics::NodeController<NodeType, GraphicsType>;
    public:
        ApplicationController(){}
        static ApplicationController* GetInstance(){
            static ApplicationController* instance = new ApplicationController();
            return instance;
        }

        void Init(){
            ConnectionController::Init();
        }

        const MainView* GetMainView()const{
            return main_view;
        }

        MainView* GetMainView(){
            return main_view;
        }

        template<typename ControllerType>
        static AddNodeHandler& GetAddNodeHandler(PObject graphics_arg = nullptr,
                                                 PObject node_arg = nullptr){
            static AddNodeHandler handler = [=](MainView* view){
                ControllerType* controller = new ControllerType(graphics_arg, node_arg);
                auto scene = static_cast<MainScene*>(view->scene());
                scene->AddItemAtCursor(controller->GetNodeGraphics());
            };
            return handler;
        }
    protected:
        MainView* main_view = new MainView();
    };
}
