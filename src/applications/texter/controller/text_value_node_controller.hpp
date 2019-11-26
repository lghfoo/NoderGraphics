#pragma once
#include"Noder/src/core/noder/node.hpp"
#include"Noder/src/applications/texter/text_node.hpp"
#include"../view/text_value_node_graphics.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
namespace Texter {
    using namespace NoderGraphics;
    using namespace Noder;
    class TextValueNodeController : public NodeController<TextNode, TextValueNodeGraphics>{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        TextValueNodeController(PObject graphics_arg = nullptr,
                                PObject node_arg = nullptr)
            :NodeController<TextNode, TextValueNodeGraphics> (graphics_arg, node_arg){
            auto value_graphics = this->node_graphics;
            auto value_node = this->node;
            value_node->GetInputPort()->FlushData(new Text());
            value_node->GetOutputPort()->FlushData(new Text());
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(), value_graphics->GetUI<PortProxy>(TextValueNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetUI<PortProxy>(TextValueNodeGraphics::OUTPUT_PORT));
            auto text_graphics = value_graphics->GetUI<TextEditProxy>(TextValueNodeGraphics::TEXT_EDIT);
            QObject::connect(text_graphics->GetWidget<QTextEdit>(), &QTextEdit::textChanged, [=](){
                if(this->IsBusy())return;
                this->SetBusy(true);
                auto text = text_graphics->GetWidget<QTextEdit>()->toPlainText();
                auto str = text.toStdString();
                value_node->GetInputPort()->UpdateData(&str);
                this->SetBusy(false);
            });

            value_node->GetInputPort()->AddUpdateDataListener([=](PObject data){
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
