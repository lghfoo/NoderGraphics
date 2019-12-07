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
    class PPMFImageNodeController : public NodeController<PPMFImageNode, PPMFImageNodeGraphics>{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        PPMFImageNodeController(PObject graphics_arg = nullptr,
                                PObject node_arg = nullptr)
            :NodeController<PPMFImageNode, PPMFImageNodeGraphics> (graphics_arg, node_arg){
            auto value_graphics = this->node_graphics;
            auto value_node = this->node;
            value_node->GetInputPort()->FlushData(Pointer<Data>(new Text()));
            value_node->GetOutputPort()->FlushData(Pointer<Data>(new ImageData()));
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort(), value_graphics->GetUI<PortProxy>(PPMFImageNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort(), value_graphics->GetUI<PortProxy>(PPMFImageNodeGraphics::OUTPUT_PORT));
        }
    };
}
