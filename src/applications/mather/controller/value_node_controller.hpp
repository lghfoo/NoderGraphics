#pragma once
#include"../../../core/view/connection_graphics.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../view/op_node_graphics.hpp"
#include"../view/value_node_graphics.hpp"
#include"Noder/src/applications/mather/value_node.hpp"
namespace Mather {
    class Int64ValueController: public NoderGraphics::NodeController<ValueNode, Int64ValueNodeGraphics>{
    private:
        using Node = Noder::Node;
        using NodeGraphics = NoderGraphics::NodeGraphics;
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        Int64ValueController(PObject graphics_arg = nullptr,
                             PObject node_arg = nullptr)
            :NoderGraphics::NodeController<ValueNode, Int64ValueNodeGraphics> (graphics_arg, node_arg){
            auto value_graphics = this->node_graphics;
            auto value_node = this->node;
            value_node->GetInputPort()->FlushData(Pointer<Data>(new Number<long long>()));
            value_node->GetOutputPort()->FlushData(Pointer<Data>(new Number<long long>()));
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(),
                                                       value_graphics->GetUI<PortProxy>(Int64ValueNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(),
                                                        value_graphics->GetUI<PortProxy>(Int64ValueNodeGraphics::OUTPUT_PORT));
            BindingHelper().Bind(this->node_graphics
                                 ->GetUI<Int64SpinBoxProxy>(Int64ValueNodeGraphics::VALUE_SPIN_BOX),
                                 value_node->GetInputPort().get());

        }
    };

    class Int32ValueController: public NoderGraphics::NodeController<ValueNode, Int32ValueNodeGraphics>{
    private:
        using Node = Noder::Node;
        using NodeGraphics = NoderGraphics::NodeGraphics;
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        Int32ValueController(PObject graphics_arg = nullptr,
                             PObject node_arg = nullptr)
            :NoderGraphics::NodeController<ValueNode, Int32ValueNodeGraphics> (graphics_arg, node_arg){
            auto value_graphics = this->node_graphics;
            auto value_node = this->node;
            value_node->GetInputPort()->FlushData(Pointer<Data>(new Number<int>()));
            value_node->GetOutputPort()->FlushData(Pointer<Data>(new Number<int>()));
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(),
                                                       value_graphics->GetUI<PortProxy>(Int32ValueNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(),
                                                        value_graphics->GetUI<PortProxy>(Int32ValueNodeGraphics::OUTPUT_PORT));
            BindingHelper().Bind(this->node_graphics
                                 ->GetUI<Int32SpinBoxProxy>(Int32ValueNodeGraphics::VALUE_SPIN_BOX),
                                 value_node->GetInputPort().get());

        }
    };
}
