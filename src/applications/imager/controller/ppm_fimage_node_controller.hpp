#pragma once
#include"Noder/src/core/noder/node.hpp"
#include"Noder/src/applications/imager/ppm_fimage_node.hpp"
#include"../view/image_node_graphics.hpp"
#include"../view/ppm_fimage_node_graphics.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
namespace Imager {
    using namespace NoderGraphics;
    using namespace Noder;
    class PPMFImageNodeController : public NodeController{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        PPMFImageNodeController(Node* node,
                                NodeGraphics* graphics)
                               :NodeController(node, graphics){
            auto value_graphics = dynamic_cast<PPMFImageNodeGraphics*>(graphics);
            if(!value_graphics)return;
            auto value_node = dynamic_cast<PPMFImageNode*>(node);
            if(!value_node)return;
            value_node->GetInputPort()->FlushData(new Text());
            value_node->GetOutputPort()->FlushData(new ImageData());
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(), value_graphics->GetUI<PortProxy>(PPMFImageNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetUI<PortProxy>(PPMFImageNodeGraphics::OUTPUT_PORT));
//            auto text_graphics = value_graphics->GetUI<TextEditProxy>(TextValueNodeGraphics::TEXT_EDIT);
//            QObject::connect(text_graphics->GetWidget<QTextEdit>(), &QTextEdit::textChanged, [=](){
//                if(this->IsBusy())return;
//                this->SetBusy(true);
//                auto text = text_graphics->GetWidget<QTextEdit>()->toPlainText();
//                auto str = text.toStdString();
//                value_node->GetInputPort()->UpdateData(&str);
//                this->SetBusy(false);
//            });

//            value_node->GetInputPort()->AddUpdateDataListener([=](PObject data){
//                if(this->IsBusy())return;
//                this->SetBusy(true);
//                auto text_edit = text_graphics->GetWidget<QTextEdit>();
//                auto str = *static_cast<string*>(data);
//                text_edit->setText(QString(str.c_str()));
//                this->SetBusy(false);
//            });
        }
    };
}
