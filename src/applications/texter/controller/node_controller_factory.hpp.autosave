#pragma once
#include"Noder/src/applications/texter/node_factory.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"text_value_node_controller.hpp"
#include"../view/text_value_node_graphics.hpp"
#include"../controller/node_controlleres.hpp"
namespace Texter {
    using namespace NoderGraphics;
    class NodeControllerFactory{
    public:
        enum NodeType{
            TEXT_VALUE,
            TO_STRING
        };
        static NodeController* CreateNodeController(const NodeType& node_type){
            switch (node_type) {
            case TEXT_VALUE:
                return new TextValueNodeController;
            case TO_STRING:
                return new ToStringNodeController;
            default:
                return nullptr;
            }
        }
    };
}
