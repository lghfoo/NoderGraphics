#pragma once
#include"../view/main_view.hpp"
#include"../view/connection_graphics.hpp"
#include"../../../core/node_controller.hpp"
#include"port_controller.hpp"
#include"Noder/src/applications/mather/node_factory.hpp"
namespace Mather {
    template <typename T>
    class BinaryOpNodeController : public NoderGraphics::NodeController{
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

//    class Int64AddNodeController : public NoderGraphics::NodeController{
//    private:
//        using Node = Noder::Node;
//        using NodeGraphics = NoderGraphics::NodeGraphics;
//        using NodeController = NoderGraphics::NodeController;

//        PortController* lhs_input_port_controller = nullptr;
//        PortController* rhs_input_port_controller = nullptr;
//        PortController* output_port_controller = nullptr;
//    public:
//        Int64AddNodeController(Noder::Node* node,
//                             NoderGraphics::NodeGraphics* graphics)
//                            :NoderGraphics::NodeController(node, graphics){
//            auto value_graphics = dynamic_cast<BinaryOpNodeGraphics*>(graphics);
//            if(!value_graphics)return;
//            auto value_node = dynamic_cast<AddOpNode<long long, long long, long long>*>(node);
//            if(!value_node)return;

//            value_node->GetInputPort1()->FlushData(new Number<long long>());
//            value_node->GetInputPort2()->FlushData(new Number<long long>());
//            value_node->GetOutputPort()->FlushData(new Number<long long>());
//            // todo: use shared_ptr?
//            lhs_input_port_controller = new PortController(value_node->GetInputPort1().get(), value_graphics->GetLhsPortGraphics());
//            rhs_input_port_controller = new PortController(value_node->GetInputPort2().get(), value_graphics->GetRhsPortGraphics());
//            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetOutputPortGraphics());
//        }
//    };
}
