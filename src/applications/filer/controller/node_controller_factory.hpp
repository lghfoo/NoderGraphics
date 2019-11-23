#pragma once
#include"Noder/src/applications/filer/node_factory.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"select_file_node_controller.hpp"
#include"../view/select_file_node_graphics.hpp"
#include"../controller/node_controllers.hpp"
namespace Filer {
    using namespace NoderGraphics;

    class NodeControllerFactory{
    public:
        enum NodeType{
            FILE_SELECT,
            FILELEN_NODE
        };
        static NodeController* CreateNodeController(const NodeType& node_type){
            switch (node_type) {
            case FILE_SELECT:
                return new SelectFileNodeController(new FileNode, new SelectFileNodeGraphics);
            case FILELEN_NODE:
                return new FilelenNodeController(new FilelenNode, new FilelenNodeGraphics);
            default:
                return nullptr;
            }
        }
    };
}
