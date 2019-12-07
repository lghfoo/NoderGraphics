#pragma once
#include"Noder/src/core/noder/node.hpp"

#include"Noder/src/applications/imager/binaryzation/otsu_node.hpp"

#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../../../core/view/node_graphics_presets/node_graphics_presets.hpp"
namespace Imager {
    using namespace NoderGraphics;
    using namespace Noder;
    class OTSUNodeController : public NodeController<OTSUNode, Label_1_1>{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        OTSUNodeController(PObject graphics_arg = nullptr,
                           PObject node_arg = nullptr)
            :NodeController<OTSUNode, Label_1_1> (graphics_arg, node_arg){
            auto value_graphics = this->node_graphics;
            auto value_node = this->node;
            value_node->GetInputPort()->FlushData(Pointer<Data>(new ImageData));
            value_node->GetOutputPort()->FlushData(Pointer<Data>(new ImageData));
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(), value_graphics->GetUI<PortProxy>(Label_1_1::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetUI<PortProxy>(Label_1_1::OUTPUT_PORT));
        }
    };
}
