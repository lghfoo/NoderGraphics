#pragma once
#include"../../../core/view/connection_graphics.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../view/op_node_graphics.hpp"
#include"../view/value_node_graphics.hpp"
#include"Noder/src/applications/mather/value_node.hpp"
namespace Mather {
    class Int64ValueController: public NoderGraphics::NodeController{
    private:
        using Node = Noder::Node;
        using NodeGraphics = NoderGraphics::NodeGraphics;
        using NodeController = NoderGraphics::NodeController;

        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        Int64ValueController(){
            this->node = new ValueNode;
            this->node_graphics = new Int64ValueNodeGraphics;
            auto value_graphics = static_cast<Int64ValueNodeGraphics*>(this->node_graphics);
            auto value_node = static_cast<ValueNode*>(this->node);
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
