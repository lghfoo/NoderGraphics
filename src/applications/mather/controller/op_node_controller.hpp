#pragma once
#include"../../../core/view/connection_graphics.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../view/op_node_graphics.hpp"
#include"Noder/src/applications/mather/node_factory.hpp"
namespace Mather {
    template <typename T>
    class BinaryOpNodeController : public NoderGraphics::NodeController{
        using PortController = NoderGraphics::PortController;
    private:
        using Node = Noder::Node;
        using NodeGraphics = NoderGraphics::NodeGraphics;
        using NodeController = NoderGraphics::NodeController;

        PortController* lhs_input_port_controller = nullptr;
        PortController* rhs_input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        BinaryOpNodeController(Noder::Node* node,
                             NoderGraphics::NodeGraphics* graphics)
                            :NoderGraphics::NodeController(node, graphics){
            auto value_graphics = dynamic_cast<BinaryOpNodeGraphics*>(graphics);
            if(!value_graphics)return;
            auto value_node = dynamic_cast<BinaryOpNode*>(node);
            if(!value_node)return;

            value_node->GetInputPort1()->FlushData(new Number<T>());
            value_node->GetInputPort2()->FlushData(new Number<T>());
            value_node->GetOutputPort()->FlushData(new Number<T>());
            // todo: use shared_ptr?
            lhs_input_port_controller = new PortController(value_node->GetInputPort1().get(), value_graphics->GetLhsPortGraphics());
            rhs_input_port_controller = new PortController(value_node->GetInputPort2().get(), value_graphics->GetRhsPortGraphics());
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetOutputPortGraphics());
        }
    };
}
