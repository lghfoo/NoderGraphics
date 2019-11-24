#pragma once
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../view/select_file_node_graphics.hpp"
#include"Noder/src/applications/filer/file_node.hpp"
namespace Filer {
    using namespace NoderGraphics;
    class SelectFileNodeController : public NodeController{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        SelectFileNodeController(){
            this->node = new FileNode;
            this->node_graphics = new SelectFileNodeGraphics;
            auto value_graphics = static_cast<SelectFileNodeGraphics*>(this->node_graphics);
            auto value_node = static_cast<FileNode*>(this->node);
            value_node->GetInputPort()->FlushData(new Text);
            value_node->GetOutputPort()->FlushData(new Text);
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(), value_graphics->GetUI<PortProxy>(SelectFileNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetUI<PortProxy>(SelectFileNodeGraphics::OUTPUT_PORT));
            auto text_graphics = value_graphics->GetUI<FileBoxProxy>(SelectFileNodeGraphics::FILE_BOX);
            QObject::connect(text_graphics->GetWidget<QLineEdit>(), &QLineEdit::textChanged, [=](const QString& text){
                if(this->IsBusy())return;
                this->SetBusy(true);
                auto str = text.toLocal8Bit().toStdString();
                value_node->GetInputPort()->UpdateData(&str);
                this->SetBusy(false);
            });

            value_node->GetInputPort()->AddUpdateDataListener([=](PObject data){
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
