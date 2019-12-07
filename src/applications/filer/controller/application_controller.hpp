#pragma once
#include"../../../core/view/main_view.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"

#include"../../../applications/texter/controller/application_controller.hpp"
#include"../../../applications/mather/controller/application_controller.hpp"
#include"node_controller_factory.hpp"
#include"select_file_node_controller.hpp"
#include"node_controlleres.hpp"
namespace Filer {
    using namespace NoderGraphics;
    class ApplicationController : public NoderGraphics::ApplicationController{
        using AddNodeHandler = MainView::AddNodeHandler;
    public:
        ApplicationController(){
            main_view->AddContextAction("Filer/File", GetAddNodeHandler<SelectFileNodeController>());
            main_view->AddContextAction("Filer/File Length", GetAddNodeHandler<FilelenNodeController>());
            main_view->AddContextAction("Filer/Pick Buffer From File", GetAddNodeHandler<PickBufferFromFileNodeController>());
            main_view->AddContextAction("Filer/Pick Number From Buffer", GetAddNodeHandler<PickNumberFromBufferNodeController>());
            main_view->AddContextAction("Mather/Value/Int64", GetAddNodeHandler<Mather::Int64ValueController>());
            main_view->AddContextAction("Mather/Value/Int32", GetAddNodeHandler<Mather::Int32ValueController>());
            main_view->AddContextAction("Texter/Text", GetAddNodeHandler<Texter::TextValueNodeController>());
            main_view->AddContextAction("Texter/To Text", GetAddNodeHandler<Texter::ToStringNodeController>());
        }
    };
}
