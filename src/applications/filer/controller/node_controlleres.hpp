#pragma once
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../view/node_graphicses.hpp"
#include"Noder/src/applications/filer/nodes.hpp"
namespace Filer {
    using namespace NoderGraphics;
    class FilelenNodeController : public NodeController{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        FilelenNodeController(Noder::Node* node,
                                 NoderGraphics::NodeGraphics* graphics)
                                :NoderGraphics::NodeController(node, graphics){
            auto filelen_graphics = dynamic_cast<FilelenNodeGraphics*>(graphics);
            if(!filelen_graphics)return;
            auto filelen_node = dynamic_cast<FilelenNode*>(node);
            if(!filelen_node)return;
            // todo: use shared_ptr?
            input_port_controller = new PortController(filelen_node->GetInputPort(FilelenNode::FILENAME_INPUT).get(), filelen_graphics->GetUI<PortProxy>(FilelenNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(filelen_node->GetOutputPort(FilelenNode::FILELEN_OUTPUT).get(), filelen_graphics->GetUI<PortProxy>(FilelenNodeGraphics::OUTPUT_PORT));
            auto text_graphics = filelen_graphics->GetUI<FileBoxProxy>(FilelenNodeGraphics::FILE_BOX);
            QObject::connect(text_graphics->GetWidget<QLineEdit>(), &QLineEdit::textChanged, [=](const QString& text){
                if(this->IsBusy())return;
                this->SetBusy(true);
                auto str = text.toLocal8Bit().toStdString();
                filelen_node->GetInputPort(FilelenNode::FILENAME_INPUT)->UpdateData(&str);
                this->SetBusy(false);
            });

            filelen_node->GetInputPort(FilelenNode::FILENAME_INPUT)->AddUpdateDataListener([=](PObject data){
                if(this->IsBusy())return;
                this->SetBusy(true);
                auto text_edit = text_graphics->GetWidget<QLineEdit>();
                auto str = *static_cast<string*>(data);
                text_edit->setText(QString(str.c_str()));
                this->SetBusy(false);
            });
        }
    };
}
