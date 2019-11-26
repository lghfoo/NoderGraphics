#pragma once
#include"../../../core/view/main_view.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/application_controller.hpp"
#include"text_value_node_controller.hpp"
#include"node_controlleres.hpp"
namespace Texter {
    using namespace NoderGraphics;

    class ApplicationController : public NoderGraphics::ApplicationController{
        using AddNodeHandler = MainView::AddNodeHandler;
    public:
        ApplicationController(){
            main_view->AddContextAction("Text", GetAddNodeHandler<TextValueNodeController>());
        }

    };
}
