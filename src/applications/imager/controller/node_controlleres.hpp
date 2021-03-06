#pragma once
#include"Noder/src/core/noder/node.hpp"
#include"Noder/src/applications/imager/noise/gaussian_noise_node.hpp"
#include"Noder/src/applications/imager/noise/voronoi_noise_node.hpp"
#include"Noder/src/applications/imager/noise/white_noise_node.hpp"
#include"Noder/src/applications/imager/noise/value_noise_node.hpp"
#include"Noder/src/applications/imager/noise/perlin_noise_node.hpp"
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

    class VoronoiNoiseNodeController : public NodeController<VoronoiNoiseNode, VoronoiNoiseNodeGraphics>{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        VoronoiNoiseNodeController(PObject graphics_arg = nullptr,
                                PObject node_arg = nullptr)
            :NodeController<VoronoiNoiseNode, VoronoiNoiseNodeGraphics> (graphics_arg, node_arg){
#define VNN VoronoiNoiseNode
#define VNG VoronoiNoiseNodeGraphics
            // cell width
            {
                auto cell_w_port_proxy = node_graphics->GetUI<PortProxy>(VNG::CELLW_PORT);
                auto cell_w_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(VNG::CELLW_BOX);
                auto cell_w_port = node->GetInputPort(VNN::CELLW_INPUT);
                auto cell_w_controller = new PortController(cell_w_port, cell_w_port_proxy);
                BindingHelper().Bind(cell_w_port_box, cell_w_port);
            }
            // cell height
            {
                auto cell_h_port_proxy = node_graphics->GetUI<PortProxy>(VNG::CELLH_PORT);
                auto cell_h_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(VNG::CELLH_BOX);
                auto cell_h_port = node->GetInputPort(VNN::CELLH_INPUT);
                auto cell_h_controller = new PortController(cell_h_port, cell_h_port_proxy);
                BindingHelper().Bind(cell_h_port_box, cell_h_port);
            }
            {
                auto order_port_proxy = node_graphics->GetUI<PortProxy>(VNG::ORDER_PORT);
                auto order_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(VNG::ORDER_BOX);
                auto order_port = node->GetInputPort(VNN::ORDER_INPUT);
                auto order_controller = new PortController(order_port, order_port_proxy);
                BindingHelper().Bind(order_port_box, order_port);
            }
            // width
            {
                auto width_port_proxy = node_graphics->GetUI<PortProxy>(VNG::WIDTH_PORT);
                auto width_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(VNG::WIDTH_BOX);
                auto width_port = node->GetInputPort(VNN::WIDTH_INPUT);
                auto width_controller = new PortController(width_port, width_port_proxy);
                BindingHelper().Bind(width_port_box, width_port);
            }
            // height
            {
                auto height_port_proxy = node_graphics->GetUI<PortProxy>(VNG::HEIGHT_PORT);
                auto height_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(VNG::HEIGHT_BOX);
                auto height_port = node->GetInputPort(VNN::HEIGHT_INPUT);
                auto height_controller = new PortController(height_port, height_port_proxy);
                BindingHelper().Bind(height_port_box, height_port);
            }
            // image
            {
                auto output_port_proxy = node_graphics->GetUI<PortProxy>(VNG::OUTPUT_IMAGE_PORT);
                auto output_port = node->GetOutputPort(VNN::IMAGE_OUTPUT);
                auto output_controller = new PortController(output_port, output_port_proxy);
            }
#undef VNN
#undef VNG
        }
    };

    class WhiteNoiseNodeController : public NodeController<WhiteNoiseNode, WhiteNoiseNodeGraphics>{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        WhiteNoiseNodeController(PObject graphics_arg = nullptr,
                                PObject node_arg = nullptr)
            :NodeController<WhiteNoiseNode, WhiteNoiseNodeGraphics> (graphics_arg, node_arg){
#define WNN WhiteNoiseNode
#define WNG WhiteNoiseNodeGraphics
            // cell width
            {
                auto cell_w_port_proxy = node_graphics->GetUI<PortProxy>(WNG::CELLW_PORT);
                auto cell_w_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(WNG::CELLW_BOX);
                auto cell_w_port = node->GetInputPort(WNN::CELLW_INPUT);
                auto cell_w_controller = new PortController(cell_w_port, cell_w_port_proxy);
                BindingHelper().Bind(cell_w_port_box, cell_w_port);
            }
            // cell height
            {
                auto cell_h_port_proxy = node_graphics->GetUI<PortProxy>(WNG::CELLH_PORT);
                auto cell_h_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(WNG::CELLH_BOX);
                auto cell_h_port = node->GetInputPort(WNN::CELLH_INPUT);
                auto cell_h_controller = new PortController(cell_h_port, cell_h_port_proxy);
                BindingHelper().Bind(cell_h_port_box, cell_h_port);
            }
            // width
            {
                auto width_port_proxy = node_graphics->GetUI<PortProxy>(WNG::WIDTH_PORT);
                auto width_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(WNG::WIDTH_BOX);
                auto width_port = node->GetInputPort(WNN::WIDTH_INPUT);
                auto width_controller = new PortController(width_port, width_port_proxy);
                BindingHelper().Bind(width_port_box, width_port);
            }
            // height
            {
                auto height_port_proxy = node_graphics->GetUI<PortProxy>(WNG::HEIGHT_PORT);
                auto height_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(WNG::HEIGHT_BOX);
                auto height_port = node->GetInputPort(WNN::HEIGHT_INPUT);
                auto height_controller = new PortController(height_port, height_port_proxy);
                BindingHelper().Bind(height_port_box, height_port);
            }
            // image
            {
                auto output_port_proxy = node_graphics->GetUI<PortProxy>(WNG::OUTPUT_IMAGE_PORT);
                auto output_port = node->GetOutputPort(WNN::IMAGE_OUTPUT);
                auto output_controller = new PortController(output_port, output_port_proxy);
            }
#undef WNN
#undef WNG
        }
    };

    class ValueNoiseNodeController : public NodeController<ValueNoiseNode, ValueNoiseNodeGraphics>{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        ValueNoiseNodeController(PObject graphics_arg = nullptr,
                                PObject node_arg = nullptr)
            :NodeController<ValueNoiseNode, ValueNoiseNodeGraphics> (graphics_arg, node_arg){
#define VNN ValueNoiseNode
#define VNG ValueNoiseNodeGraphics
            // cell width
            {
                auto cell_w_port_proxy = node_graphics->GetUI<PortProxy>(VNG::CELLW_PORT);
                auto cell_w_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(VNG::CELLW_BOX);
                auto cell_w_port = node->GetInputPort(VNN::CELLW_INPUT);
                auto cell_w_controller = new PortController(cell_w_port, cell_w_port_proxy);
                BindingHelper().Bind(cell_w_port_box, cell_w_port);
            }
            // cell height
            {
                auto cell_h_port_proxy = node_graphics->GetUI<PortProxy>(VNG::CELLH_PORT);
                auto cell_h_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(VNG::CELLH_BOX);
                auto cell_h_port = node->GetInputPort(VNN::CELLH_INPUT);
                auto cell_h_controller = new PortController(cell_h_port, cell_h_port_proxy);
                BindingHelper().Bind(cell_h_port_box, cell_h_port);
            }
            // width
            {
                auto width_port_proxy = node_graphics->GetUI<PortProxy>(VNG::WIDTH_PORT);
                auto width_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(VNG::WIDTH_BOX);
                auto width_port = node->GetInputPort(VNN::WIDTH_INPUT);
                auto width_controller = new PortController(width_port, width_port_proxy);
                BindingHelper().Bind(width_port_box, width_port);
            }
            // height
            {
                auto height_port_proxy = node_graphics->GetUI<PortProxy>(VNG::HEIGHT_PORT);
                auto height_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(VNG::HEIGHT_BOX);
                auto height_port = node->GetInputPort(VNN::HEIGHT_INPUT);
                auto height_controller = new PortController(height_port, height_port_proxy);
                BindingHelper().Bind(height_port_box, height_port);
            }
            // image
            {
                auto output_port_proxy = node_graphics->GetUI<PortProxy>(VNG::OUTPUT_IMAGE_PORT);
                auto output_port = node->GetOutputPort(VNN::IMAGE_OUTPUT);
                auto output_controller = new PortController(output_port, output_port_proxy);
            }
#undef VNN
#undef VNG
        }
    };

    class PerlinNoiseNodeController : public NodeController<PerlinNoiseNode, PerlinNoiseNodeGraphics>{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        PerlinNoiseNodeController(PObject graphics_arg = nullptr,
                                PObject node_arg = nullptr)
            :NodeController<PerlinNoiseNode, PerlinNoiseNodeGraphics> (graphics_arg, node_arg){
#define PNN PerlinNoiseNode
#define PNG PerlinNoiseNodeGraphics
            // cell width
            {
                auto cell_w_port_proxy = node_graphics->GetUI<PortProxy>(PNG::CELLW_PORT);
                auto cell_w_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(PNG::CELLW_BOX);
                auto cell_w_port = node->GetInputPort(PNN::CELLW_INPUT);
                auto cell_w_controller = new PortController(cell_w_port, cell_w_port_proxy);
                BindingHelper().Bind(cell_w_port_box, cell_w_port);
            }
            // cell height
            {
                auto cell_h_port_proxy = node_graphics->GetUI<PortProxy>(PNG::CELLH_PORT);
                auto cell_h_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(PNG::CELLH_BOX);
                auto cell_h_port = node->GetInputPort(PNN::CELLH_INPUT);
                auto cell_h_controller = new PortController(cell_h_port, cell_h_port_proxy);
                BindingHelper().Bind(cell_h_port_box, cell_h_port);
            }
            // width
            {
                auto width_port_proxy = node_graphics->GetUI<PortProxy>(PNG::WIDTH_PORT);
                auto width_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(PNG::WIDTH_BOX);
                auto width_port = node->GetInputPort(PNN::WIDTH_INPUT);
                auto width_controller = new PortController(width_port, width_port_proxy);
                BindingHelper().Bind(width_port_box, width_port);
            }
            // height
            {
                auto height_port_proxy = node_graphics->GetUI<PortProxy>(PNG::HEIGHT_PORT);
                auto height_port_box = node_graphics->GetUI<Int32SpinBoxProxy>(PNG::HEIGHT_BOX);
                auto height_port = node->GetInputPort(PNN::HEIGHT_INPUT);
                auto height_controller = new PortController(height_port, height_port_proxy);
                BindingHelper().Bind(height_port_box, height_port);
            }
            // image
            {
                auto output_port_proxy = node_graphics->GetUI<PortProxy>(PNG::OUTPUT_IMAGE_PORT);
                auto output_port = node->GetOutputPort(PNN::IMAGE_OUTPUT);
                auto output_controller = new PortController(output_port, output_port_proxy);
            }
#undef PNN
#undef PNG
        }
    };
}
