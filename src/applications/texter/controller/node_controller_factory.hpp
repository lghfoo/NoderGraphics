#pragma once
#include"Noder/src/applications/texter/node_factory.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"text_value_node_controller.hpp"
#include"../view/text_value_node_graphics.hpp"
namespace Texter {
    using namespace NoderGraphics;
    class NodeControllerFactory{
    public:
        static NodeController* CreateNodeController(const NodeFactory::NodeType& node_type){
            switch (node_type) {
            case NodeFactory::NodeType::TEXT_VALUE:
                return new TextValueNodeController(NodeFactory::CreateNode(node_type), new TextValueNodeGraphics);
            default:
                return nullptr;
            }
        }
    };
}
