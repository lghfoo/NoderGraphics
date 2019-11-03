#pragma once
#include"Noder/src/core/noder/node.hpp"

#include"Noder/src/applications/imager/binaryzation/otsu_node.hpp"

#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../../../core/view/node_graphics_presets/node_graphics_presets.hpp"
namespace Imager {
    using namespace NoderGraphics;
    using namespace Noder;
    class OTSUNodeController : public NodeController{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        OTSUNodeController(Node* node,
                                NodeGraphics* graphics)
                               :NodeController(node, graphics){
            auto value_graphics = dynamic_cast<Label_1_1*>(graphics);
            if(!value_graphics)return;
            auto value_node = dynamic_cast<OTSUNode*>(node);
            if(!value_node)return;
            value_node->GetInputPort()->FlushData(new ImageData);
            value_node->GetOutputPort()->FlushData(new ImageData);
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(), value_graphics->GetUI<PortProxy>(Label_1_1::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetUI<PortProxy>(Label_1_1::OUTPUT_PORT));
        }
    };
}
