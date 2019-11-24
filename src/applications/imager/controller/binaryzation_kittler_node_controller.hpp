#pragma once
#include"Noder/src/core/noder/node.hpp"

#include"Noder/src/applications/imager/binaryzation/kittler_node.hpp"

#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../../../core/view/node_graphics_presets/node_graphics_presets.hpp"
namespace Imager {
    using namespace NoderGraphics;
    using namespace Noder;
    class KittlerNodeController : public NodeController{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        KittlerNodeController(){
            this->node = new KittlerNode;
            this->node_graphics = new Label_1_1("Kittler Node");
            auto value_graphics = static_cast<Label_1_1*>(this->node_graphics);
            auto value_node = static_cast<KittlerNode*>(this->node);
            value_node->GetInputPort()->FlushData(new ImageData);
            value_node->GetOutputPort()->FlushData(new ImageData);
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(), value_graphics->GetUI<PortProxy>(Label_1_1::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetUI<PortProxy>(Label_1_1::OUTPUT_PORT));
        }
    };
}
