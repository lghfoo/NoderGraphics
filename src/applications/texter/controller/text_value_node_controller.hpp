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
            BindingHelper().Bind(text_graphics, value_node->GetInputPort().get());
        }
    };
}
