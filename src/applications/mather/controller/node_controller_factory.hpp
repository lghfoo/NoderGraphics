#pragma once
#include"../../../core/controller/node_controller.hpp"
#include"Noder/src/applications/mather/node_factory.hpp"
#include"value_node_controller.hpp"
#include"op_node_controller.hpp"
namespace Mather {
    using NodeType = NodeFactory::NodeType;
    using NodeController = NoderGraphics::NodeController;

    class NodeControllerFactory{
    public:
        static NodeController* CreateNodeController(const NodeType& nodeType){
#define BIN_OP_CASE(e, type, node_name)                                                                             \
case NodeType::e:                                                                                                   \
    ret = new BinaryOpNodeController<type>(NodeFactory::CreateNode(nodeType), new BinaryOpNodeGraphics(node_name)); \
    break;

            NodeController* ret = nullptr;
            switch (nodeType) {
            BIN_OP_CASE(INT64_ADD, long long, "Int64 Addition")
            BIN_OP_CASE(INT64_SUBSTRACT, long long, "Int64 Substraction")
            BIN_OP_CASE(INT64_MULTIPLY, long long, "Int64 Multiplication")
            BIN_OP_CASE(INT64_DIVIDE, long long, "Int64 Division")
            BIN_OP_CASE(INT64_MODULUS, long long, "Int64 Modulus")
            case NodeType::INT64_VALUE:
                ret = new Int64ValueController(new ValueNode(), new Int64ValueNodeGraphics());
                break;
            default:
                break;
            }
            return ret;
#undef BIN_OP_CASE(e, type, node_name)
        }
    private:

    };
}
