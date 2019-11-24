#pragma once
#include"Noder/src/applications/filer/node_factory.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"select_file_node_controller.hpp"
#include"../view/select_file_node_graphics.hpp"
#include"../controller/node_controlleres.hpp"
#include"../view/node_graphicses.hpp"
namespace Filer {
    using namespace NoderGraphics;

    class NodeControllerFactory{
    public:
        enum NodeType{
            FILE_SELECT,
            FILELEN_NODE,
            PICK_BUFFER_FROM_FILE_NODE,
            PICK_NUMBER_FROM_BUFFER_NODE
        };
        static NodeController* CreateNodeController(const NodeType& node_type){
            switch (node_type) {
            case FILE_SELECT:
                return new SelectFileNodeController;
            case FILELEN_NODE:
                return new FilelenNodeController;
            case PICK_BUFFER_FROM_FILE_NODE:
                return new PickBufferFromFileNodeController;
            case PICK_NUMBER_FROM_BUFFER_NODE:
                return new PickNumberFromBufferNodeController;
            default:
                return nullptr;
            }
        }
    };
}
