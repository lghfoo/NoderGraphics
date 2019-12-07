#pragma once
#include"Noder/src/core/noder/node.hpp"

#include"Noder/src/applications/imager/grayen_node.hpp"
#include"../view/grayen_node_graphics.hpp"

#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
namespace Imager {
    using namespace NoderGraphics;
    using namespace Noder;
    class GrayenNodeController : public NodeController<GrayenNode, GrayenNodeGraphics>{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        GrayenNodeController(PObject graphics_arg = nullptr,
                             PObject node_arg = nullptr)
            :NodeController<GrayenNode, GrayenNodeGraphics> (graphics_arg, node_arg){
            auto value_graphics = this->node_graphics;
            auto value_node = this->node;
            value_node->GetInputPort()->FlushData(Pointer<Data>(new ImageData));
            value_node->GetOutputPort()->FlushData(Pointer<Data>(new ImageData));
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(), value_graphics->GetUI<PortProxy>(GrayenNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetUI<PortProxy>(GrayenNodeGraphics::OUTPUT_PORT));
        }
    };
}
