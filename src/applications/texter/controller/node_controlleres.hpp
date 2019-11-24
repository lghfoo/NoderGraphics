#pragma once
#include"Noder/src/core/noder/node.hpp"
#include"Noder/src/applications/texter/nodes.hpp"
#include"../view/node_graphicses.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
namespace Texter {
    using namespace NoderGraphics;
    using namespace Noder;
    class ToStringNodeController : public NodeController{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        ToStringNodeController(Node* node,
                                NodeGraphics* graphics)
                               :NodeController(node, graphics){
            auto value_graphics = dynamic_cast<ToStringNodeGraphics*>(graphics);
            if(!value_graphics)return;
            auto value_node = dynamic_cast<ToStringNode*>(node);
            if(!value_node)return;
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort(ToStringNode::DATA_INPUT).get(), value_graphics->GetUI<PortProxy>(ToStringNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort(ToStringNode::STRING_OUTPUT).get(), value_graphics->GetUI<PortProxy>(ToStringNodeGraphics::OUTPUT_PORT));
            auto text_graphics = value_graphics->GetUI<TextEditProxy>(ToStringNodeGraphics::TEXT_EDIT);
            value_node->GetOutputPort(ToStringNode::STRING_OUTPUT)->AddUpdateDataListener([=](PObject data){
                if(this->IsBusy())return;
                this->SetBusy(true);
                auto text_edit = text_graphics->GetWidget<QTextEdit>();
                auto str = *static_cast<string*>(data);
                text_edit->setText(QString(str.c_str()));
                this->SetBusy(false);
            });
        }
    };
}
