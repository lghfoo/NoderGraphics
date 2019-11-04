#pragma once
#include"../../../core/view/main_view.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/application_controller.hpp"
#include"../../../applications/filer/controller/application_controller.hpp"
#include"node_controller_factory.hpp"
namespace Imager {
    class ApplicationController : public NoderGraphics::ApplicationController{
        using AddNodeHandler = MainView::AddNodeHandler;
        using NodeType = NodeFactory::NodeType;
    public:
        ApplicationController(){
            main_view->AddContextAction("Image", GetAddNodeHandler<NodeType::IMAGE_VALUE>());
            main_view->AddContextAction("File/PPM", GetAddNodeHandler<NodeType::PPM_FILE_2_IMAGE>());
            main_view->AddContextAction("Operation/Grayen", GetAddNodeHandler<NodeType::GRAYEN>());
            main_view->AddContextAction("Operation/Binaryzation/OTSU", GetAddNodeHandler<NodeType::OTSU_BINARYZATION>());
            main_view->AddContextAction("Operation/Binaryzation/Kittler", GetAddNodeHandler<NodeType::KITTLER_BINARYZATION>());
            main_view->AddContextAction("Operation/Binaryzation/Bernsen", GetAddNodeHandler<NodeType::BERNSEN_BINARYZATION>());
            main_view->AddContextAction("Filer/File", Filer::ApplicationController::
                                        GetAddNodeHandler<Filer::NodeFactory::
                                        NodeType::FILE_SELECT>());
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
