#pragma once
#include"../../../core/view/main_view.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../../../core/controller/application_controller.hpp"
#include"node_controller_factory.hpp"
namespace Mather {
    class ApplicationController : public NoderGraphics::ApplicationController {
        using AddNodeHandler = MainView::AddNodeHandler;
        using NodeType = NodeFactory::NodeType;
    public:
        ApplicationController(){
            main_view->AddContextAction("Operation/Add/Int64", GetAddNodeHandler<NodeType::INT64_ADD>());
            main_view->AddContextAction("Operation/Substract/Int64", GetAddNodeHandler<NodeType::INT64_SUBSTRACT>());
            main_view->AddContextAction("Operation/Multiply/Int64", GetAddNodeHandler<NodeType::INT64_MULTIPLY>());
            main_view->AddContextAction("Operation/Divide/Int64", GetAddNodeHandler<NodeType::INT64_DIVIDE>());
            main_view->AddContextAction("Operation/Modulus/Int64", GetAddNodeHandler<NodeType::INT64_MODULUS>());
            main_view->AddContextAction("Value/Int64", GetAddNodeHandler<NodeType::INT64_VALUE>());
            main_view->AddContextAction("Value/Histogram", GetAddNodeHandler<NodeType::HISTOGRAM_VALUE>());
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
