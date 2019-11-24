#pragma once
#include"Noder/src/applications/imager/node_factory.hpp"

#include"../view/image_node_graphics.hpp"
#include"../view/ppm_fimage_node_graphics.hpp"
#include"../view/grayen_node_graphics.hpp"
#include"../view/bernsen_node_graphics.hpp"

#include"../../../core/view/node_graphics_presets/node_graphics_presets.hpp"

#include"image_node_controller.hpp"
#include"ppm_fimage_node_controller.hpp"
#include"grayen_node_controller.hpp"
#include"binaryzation_otsu_node_controller.hpp"
#include"binaryzation_kittler_node_controller.hpp"
#include"binaryzation_bernsen_node_controller.hpp"
#include"image_histogram_node_controller.hpp"
namespace Imager {
    using namespace NoderGraphics;
    class NodeControllerFactory{
    public:
        static NodeController* CreateNodeController(const NodeFactory::NodeType& node_type){
            switch (node_type) {
            case NodeFactory::NodeType::IMAGE_VALUE:
                return new ImageNodeController;
            case NodeFactory::NodeType::PPM_FILE_2_IMAGE:
                return new PPMFImageNodeController;
            case NodeFactory::NodeType::GRAYEN:
                return new GrayenNodeController;
            case NodeFactory::NodeType::OTSU_BINARYZATION:
                return new OTSUNodeController;
            case NodeFactory::NodeType::KITTLER_BINARYZATION:
                return new KittlerNodeController;
            case NodeFactory::NodeType::BERNSEN_BINARYZATION:
                return new BernsenNodeController;
            case NodeFactory::NodeType::IMAGE_HISTOGRAM:
                return new ImageHistogramNodeController;
            default:
                return nullptr;
            }
        }
    };
}
