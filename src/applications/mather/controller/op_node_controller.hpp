#pragma once
#include"../../../core/view/connection_graphics.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../view/op_node_graphics.hpp"
#include"Noder/src/applications/mather/op_node.hpp"
namespace Mather {
    template <typename OpNodeType, typename DataType, typename GraphicsType>
    class BinaryOpNodeController : public NoderGraphics::NodeController<OpNodeType, GraphicsType>{
        using PortController = NoderGraphics::PortController;
    private:
        using Node = Noder::Node;
        using NodeGraphics = NoderGraphics::NodeGraphics;

        PortController* lhs_input_port_controller = nullptr;
        PortController* rhs_input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        BinaryOpNodeController(PObject graphics_arg = nullptr,
                               PObject node_arg = nullptr)
            :NoderGraphics::NodeController<OpNodeType, GraphicsType> (graphics_arg, node_arg){
            auto value_graphics = this->node_graphics;
            auto value_node = this->node;
            value_node->GetInputPort1()->FlushData(Pointer<Data>(new Number<DataType>()));
            value_node->GetInputPort2()->FlushData(Pointer<Data>(new Number<DataType>()));
            value_node->GetOutputPort()->FlushData(Pointer<Data>(new Number<DataType>()));
            // todo: use shared_ptr?
            lhs_input_port_controller = new PortController(value_node->GetInputPort1().get(), value_graphics->GetLhsPortGraphics());
            rhs_input_port_controller = new PortController(value_node->GetInputPort2().get(), value_graphics->GetRhsPortGraphics());
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetOutputPortGraphics());
        }
    };

    using Int64AddOpNodeController = BinaryOpNodeController<AddOpNode<int64_t>, int64_t, BinaryOpNodeGraphics>;
    using Int64SubstractOpNodeController = BinaryOpNodeController<SubstractOpNode<int64_t>, int64_t, BinaryOpNodeGraphics>;
    using Int64MultiplyOpNodeController = BinaryOpNodeController<MultiplyOpNode<int64_t>, int64_t, BinaryOpNodeGraphics>;
    using Int64DivideOpNodeController = BinaryOpNodeController<DivideOpNode<int64_t>, int64_t, BinaryOpNodeGraphics>;
    using Int64ModulusOpNodeController = BinaryOpNodeController<ModulusOpNode<int64_t>, int64_t, BinaryOpNodeGraphics>;

    using Int32AddOpNodeController = BinaryOpNodeController<AddOpNode<int32_t>, int32_t, BinaryOpNodeGraphics>;
    using Int32SubstractOpNodeController = BinaryOpNodeController<SubstractOpNode<int32_t>, int32_t, BinaryOpNodeGraphics>;
    using Int32MultiplyOpNodeController = BinaryOpNodeController<MultiplyOpNode<int32_t>, int32_t, BinaryOpNodeGraphics>;
    using Int32DivideOpNodeController = BinaryOpNodeController<DivideOpNode<int32_t>, int32_t, BinaryOpNodeGraphics>;
    using Int32ModulusOpNodeController = BinaryOpNodeController<ModulusOpNode<int32_t>, int32_t, BinaryOpNodeGraphics>;
}
