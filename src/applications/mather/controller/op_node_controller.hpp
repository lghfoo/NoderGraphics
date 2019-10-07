#pragma once
#include"../view/main_view.hpp"
#include"../view/connection_graphics.hpp"
#include"../../../core/node_controller.hpp"
namespace Mather {
    class Int64AddNodeController : NoderGraphics::NodeController{
    public:
        Int64AddNodeController(Noder::Node* node,
                             NoderGraphics::NodeGraphics* graphics)
                            :NoderGraphics::NodeController(node, graphics){
        }
    };
}
