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
        ImageHistogramNodeController(Node* node,
                                NodeGraphics* graphics)
                               :NodeController(node, graphics){
            auto value_graphics = dynamic_cast<ImageHistogramNodeGraphics*>(graphics);
            if(!value_graphics)return;
            auto value_node = dynamic_cast<ImageHistogramNode*>(node);
            if(!value_node)return;
            value_node->GetInputPort()->FlushData(new ImageData);
            value_node->GetOutputPort()->FlushData(new Mather::VectorData<int>());
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(), value_graphics->GetUI<PortProxy>(ImageHistogramNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetUI<PortProxy>(ImageHistogramNodeGraphics::OUTPUT_PORT));
        }
    };
}
