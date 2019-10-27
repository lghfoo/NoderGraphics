#pragma once
#include"Noder/src/applications/filer/node_factory.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"select_file_node_controller.hpp"
#include"../view/select_file_node_graphics.hpp"
namespace Filer {
    using namespace NoderGraphics;

    class NodeControllerFactory{
    public:
        static NodeController* CreateNodeController(const NodeFactory::NodeType& node_type){
            switch (node_type) {
            case NodeFactory::NodeType::FILE_SELECT:
                return new SelectFileNodeController(NodeFactory::CreateNode(node_type), new SelectFileNodeGraphics);
            default:
                return nullptr;
            }
        }
    };
}
