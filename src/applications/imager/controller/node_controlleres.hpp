#pragma once
#include"Noder/src/core/noder/node.hpp"
#include"Noder/src/applications/imager/noise/gaussian_noise_node.hpp"
#include"../view/node_graphicses.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
namespace Imager {
    using namespace NoderGraphics;
    using namespace Noder;
    class GaussianNoiseNodeController : public NodeController<GaussianNoiseNode, GaussianNoiseNodeGraphics>{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        GaussianNoiseNodeController(PObject graphics_arg = nullptr,
                                PObject node_arg = nullptr)
            :NodeController<GaussianNoiseNode, GaussianNoiseNodeGraphics> (graphics_arg, node_arg){
#define GNN GaussianNoiseNode
#define GNG GaussianNoiseNodeGraphics
            // sample num
            {
                auto sample_port_proxy = node_graphics->GetUI<PortProxy>(GNG::SAMPLE_PORT);
                auto sample_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(GNG::SAMPLE_BOX);
                auto sample_port = node->GetInputPort(GNN::SAMPLE_NUM_INPUT);
                auto sample_controller = new PortController(sample_port, sample_port_proxy);
                BindingHelper().Bind(sample_port_box, sample_port);
            }
            // width
            {
                auto width_port_proxy = node_graphics->GetUI<PortProxy>(GNG::WIDTH_PORT);
                auto width_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(GNG::WIDTH_BOX);
                auto width_port = node->GetInputPort(GNN::WIDTH_INPUT);
                auto width_controller = new PortController(width_port, width_port_proxy);
                BindingHelper().Bind(width_port_box, width_port);
            }
            // height
            {
                auto height_port_proxy = node_graphics->GetUI<PortProxy>(GNG::HEIGHT_PORT);
                auto height_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(GNG::HEIGHT_BOX);
                auto height_port = node->GetInputPort(GNN::HEIGHT_INPUT);
                auto height_controller = new PortController(height_port, height_port_proxy);
                BindingHelper().Bind(height_port_box, height_port);
            }
            // image
            {
                auto output_port_proxy = node_graphics->GetUI<PortProxy>(GNG::OUTPUT_IMAGE_PORT);
                auto output_port = node->GetOutputPort(GNN::IMAGE_OUTPUT);
                auto output_controller = new PortController(output_port, output_port_proxy);
            }
#undef GNN
#undef GNG
        }
    };
}
