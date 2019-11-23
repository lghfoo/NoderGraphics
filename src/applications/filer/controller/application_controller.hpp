#pragma once
#include"../../../core/view/main_view.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../../../applications/texter/controller/application_controller.hpp"
#include"../../../applications/mather/controller/application_controller.hpp"
#include"node_controller_factory.hpp"
namespace Filer {
    using namespace NoderGraphics;
    class ApplicationController{
        using AddNodeHandler = MainView::AddNodeHandler;
        using NodeType = NodeControllerFactory::NodeType;
    public:
        ApplicationController(){
            main_view->AddContextAction("File", GetAddNodeHandler<NodeControllerFactory::FILE_SELECT>());
            main_view->AddContextAction("Utility/File Length", GetAddNodeHandler<NodeControllerFactory::FILELEN_NODE>());
            main_view->AddContextAction("Mather/Value/Int64", Mather::ApplicationController::GetAddNodeHandler<Mather::NodeFactory::NodeType::INT64_VALUE>());
            main_view->AddContextAction("Texter/Text", Texter::ApplicationController::GetAddNodeHandler<Texter::NodeFactory::NodeType::TEXT_VALUE>());
        }

        const MainView* GetMainView()const{
            return main_view;
        }

        MainView* GetMainView(){
            return main_view;
        }

        template<NodeType NODE_TYPE>
        static AddNodeHandler& GetAddNodeHandler(){
            static AddNodeHandler handler = [](MainView* view){
                NodeController* controller = NodeControllerFactory::CreateNodeController(NODE_TYPE);
                auto scene = static_cast<MainScene*>(view->scene());
                scene->AddItemAtCursor(controller->GetNodeGraphics());
            };
            return handler;
        }
    private:
        MainView* main_view = new MainView();
    };
}
