#pragma once
#include"../view/main_view.hpp"
#include"../view/connection_graphics.hpp"
#include"../../../core/node_controller.hpp"
#include"Noder/src/applications/mather/node_factory.hpp"
#include"value_node_controller.hpp"
namespace Mather {
    using NodeType = NodeFactory::NodeType;
    using NodeController = NoderGraphics::NodeController;

    class NodeControllerFactory{
    public:
        static NodeController* CreateNodeController(const NodeType& nodeType){
            NodeController* ret = nullptr;
            switch (nodeType) {
            case NodeType::INT64_ADD:
                // todo create int64 node
                break;
            case NodeType::INT64_VALUE:
                ret = new Int64ValueController(new ValueNode(), new Int64ValueNodeGraphics());
                break;
            default:
                break;
            }
            return ret;
        }
    private:

    };
}
