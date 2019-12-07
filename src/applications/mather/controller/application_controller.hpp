#pragma once
#include"../../../core/view/main_view.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../../../core/controller/application_controller.hpp"
#include"node_controller_factory.hpp"
#include"op_node_controller.hpp"
#include"value_node_controller.hpp"
#include"histogram_value_node_controller.hpp"
namespace Mather {
    class ApplicationController : public NoderGraphics::ApplicationController {
        using AddNodeHandler = NoderGraphics::MainView::AddNodeHandler;
    public:
        ApplicationController(){
            main_view->AddContextAction("Operation/Add/Int64", AddInt64AddHandler());
            main_view->AddContextAction("Operation/Substract/Int64", AddInt64SubstractHandler());
            main_view->AddContextAction("Operation/Multiply/Int64", AddInt64MultiplyHandler());
            main_view->AddContextAction("Operation/Divide/Int64", AddInt64DivideHandler());
            main_view->AddContextAction("Operation/Modulus/Int64", AddInt64ModulusHandler());

            main_view->AddContextAction("Operation/Add/Int32", AddInt32AddHandler());
            main_view->AddContextAction("Operation/Substract/Int32", AddInt32SubstractHandler());
            main_view->AddContextAction("Operation/Multiply/Int32", AddInt32MultiplyHandler());
            main_view->AddContextAction("Operation/Divide/Int32", AddInt32DivideHandler());
            main_view->AddContextAction("Operation/Modulus/Int32", AddInt32ModulusHandler());

            main_view->AddContextAction("Value/Int64", GetAddNodeHandler<Int64ValueController>());
            main_view->AddContextAction("Value/Int32", GetAddNodeHandler<Int32ValueController>());

            main_view->AddContextAction("Value/Histogram", GetAddNodeHandler<HistogramValueNodeController>());
        }
#define DECLARE_ADD_NODE_HANDLER(NODE_NAME, NAME_STRING, CONTROLLER_TYPE)                           \
        static AddNodeHandler Add##NODE_NAME##Handler(){                                            \
            static QString name = NAME_STRING;                                                      \
            static auto ret = GetAddNodeHandler<CONTROLLER_TYPE>(&name);                            \
            return ret;                                                                             \
        }
        DECLARE_ADD_NODE_HANDLER(Int64Add, "Int64 Addition", Int64AddOpNodeController)
        DECLARE_ADD_NODE_HANDLER(Int64Substract, "Int64 Substraction", Int64SubstractOpNodeController)
        DECLARE_ADD_NODE_HANDLER(Int64Multiply, "Int64 Multiplication", Int64MultiplyOpNodeController)
        DECLARE_ADD_NODE_HANDLER(Int64Divide, "Int64 Division", Int64DivideOpNodeController)
        DECLARE_ADD_NODE_HANDLER(Int64Modulus, "Int64 Modulus", Int64ModulusOpNodeController)

        DECLARE_ADD_NODE_HANDLER(Int32Add, "Int32 Addition", Int32AddOpNodeController)
        DECLARE_ADD_NODE_HANDLER(Int32Substract, "Int32 Substraction", Int32SubstractOpNodeController)
        DECLARE_ADD_NODE_HANDLER(Int32Multiply, "Int32 Multiplication", Int32MultiplyOpNodeController)
        DECLARE_ADD_NODE_HANDLER(Int32Divide, "Int32 Division", Int32DivideOpNodeController)
        DECLARE_ADD_NODE_HANDLER(Int32Modulus, "Int32 Modulus", Int32ModulusOpNodeController)
#undef DECLARE_ADD_NODE_HANDLER(NAME_STRING)
    };
}
