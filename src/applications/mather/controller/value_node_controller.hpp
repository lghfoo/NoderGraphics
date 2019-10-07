#pragma once
#include"../view/main_view.hpp"
#include"../view/connection_graphics.hpp"
#include"../../../core/node_controller.hpp"
#include"../view/op_node_graphics.hpp"
#include"Noder/src/applications/mather/value_node.hpp"
#include"port_controller.hpp"
namespace Mather {
    class Int64ValueController: public NoderGraphics::NodeController{
    private:
        using Node = Noder::Node;
        using NodeGraphics = NoderGraphics::NodeGraphics;
        using NodeController = NoderGraphics::NodeController;

        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        Int64ValueController(Node* node,
                             NodeGraphics* graphics)
                            :NodeController(node, graphics){
            auto value_graphics = dynamic_cast<Int64ValueNodeGraphics*>(graphics);
            if(!value_graphics)return;
            auto value_node = dynamic_cast<ValueNode*>(node);
            if(!value_node)return;
            value_node->GetInputPort()->FlushData(new Number<long long>());
            value_node->GetOutputPort()->FlushData(new Number<long long>());
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(), value_graphics->GetInputPortGraphics());
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetOutputPortGraphics());
            QObject::connect(value_graphics, &Int64ValueNodeGraphics::InputValueChanged, [=](long long value){
                if(this->IsBusy())return;
                this->SetBusy(true);
                value_node->GetInputPort()->UpdateData(&value);
                this->SetBusy(false);
            });

            value_node->GetInputPort()->AddUpdateDataListener([=](PObject data){
                if(this->IsBusy())return;
                this->SetBusy(true);
                value_graphics->SetInputValue(*static_cast<long long*>(data));
                this->SetBusy(false);
            });
        }
    };
}
