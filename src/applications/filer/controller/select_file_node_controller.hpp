#pragma once
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../view/select_file_node_graphics.hpp"
#include"Noder/src/applications/filer/file_node.hpp"
namespace Filer {
    using namespace NoderGraphics;
    class SelectFileNodeController : public NodeController<FileNode, SelectFileNodeGraphics>{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        SelectFileNodeController(PObject graphics_arg = nullptr,
                                 PObject node_arg = nullptr)
            :NodeController<FileNode, SelectFileNodeGraphics> (graphics_arg, node_arg){
            auto value_graphics = this->node_graphics;
            auto value_node = this->node;
            value_node->GetInputPort()->FlushData(new Text);
            value_node->GetOutputPort()->FlushData(new Text);
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(), value_graphics->GetUI<PortProxy>(SelectFileNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetUI<PortProxy>(SelectFileNodeGraphics::OUTPUT_PORT));
            auto text_graphics = value_graphics->GetUI<FileBoxProxy>(SelectFileNodeGraphics::FILE_BOX);
            BindingHelper().Bind(text_graphics,
                                 value_node->GetInputPort().get());
        }
    };
}
