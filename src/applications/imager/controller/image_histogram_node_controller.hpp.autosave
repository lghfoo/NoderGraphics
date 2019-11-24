#pragma once
#include"Noder/src/core/noder/node.hpp"
#include"Noder/src/applications/imager/image_histogram_node.hpp"
#include"../view/image_node_graphics.hpp"
#include"../view/image_histogram_node_graphics.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
namespace Imager {
    using namespace NoderGraphics;
    using namespace Noder;
    class ImageHistogramNodeController : public NodeController{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        ImageHistogramNodeController(){
            this->node = new ImageHistogramNode;
            this->node_graphics = new ImageHistogramNodeGraphics;
            auto value_graphics = static_cast<ImageHistogramNodeGraphics*>(this->node_graphics);
            auto value_node = static_cast<ImageHistogramNode*>(this->node);
            value_node->GetInputPort()->FlushData(new ImageData);
            value_node->GetOutputPort()->FlushData(new Mather::VectorData<int>());
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(), value_graphics->GetUI<PortProxy>(ImageHistogramNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetUI<PortProxy>(ImageHistogramNodeGraphics::OUTPUT_PORT));
        }
    };
}
