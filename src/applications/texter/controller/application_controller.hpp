#pragma once
#include"../../../core/view/main_view.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"node_controller_factory.hpp"
#include"../../../core/controller/application_controller.hpp"
namespace Texter {
    class ApplicationController : public NoderGraphics::ApplicationController{
        using AddNodeHandler = MainView::AddNodeHandler;
        using NodeType = NodeControllerFactory::NodeType;
    public:
        ApplicationController(){
            main_view->AddContextAction("Text", GetAddNodeHandler<NodeType::TEXT_VALUE>());
        }

        template<NodeType NODE_TYPE>
        static AddNodeHandler& GetAddNodeHandler(){
            static AddNodeHandler handler = [](MainView* view){
                NoderGraphics::NodeController* controller = NodeControllerFactory::CreateNodeController(NODE_TYPE);
                auto scene = static_cast<MainScene*>(view->scene());
                scene->AddItemAtCursor(controller->GetNodeGraphics());
            };
            return handler;
        }
    };
}
