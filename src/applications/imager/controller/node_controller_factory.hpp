#pragma once
#include"Noder/src/applications/imager/node_factory.hpp"

#include"../view/image_node_graphics.hpp"
#include"../view/ppm_fimage_node_graphics.hpp"
#include"../view/grayen_node_graphics.hpp"

#include"image_node_controller.hpp"
#include"ppm_fimage_node_controller.hpp"
#include"grayen_node_controller.hpp"

namespace Imager {
    using namespace NoderGraphics;
    class NodeControllerFactory{
    public:
        static NodeController* CreateNodeController(const NodeFactory::NodeType& node_type){
            switch (node_type) {
            case NodeFactory::NodeType::IMAGE_VALUE:
                return new ImageNodeController(NodeFactory::CreateNode(node_type), new ImageNodeGraphics);
            case NodeFactory::NodeType::PPM_FILE_2_IMAGE:
                return new PPMFImageNodeController(NodeFactory::CreateNode(node_type), new PPMFImageNodeGraphics);
            case NodeFactory::NodeType::GRAYEN:
                return new GrayenNodeController(NodeFactory::CreateNode(node_type), new GrayenNodeGraphics);
            default:
                return nullptr;
            }
        }
    };
}
