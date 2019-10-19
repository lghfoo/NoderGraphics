#pragma once
#include<QGraphicsWidget>
#include<QDebug>
#include"Noder/src/core/noder/node.hpp"
#include"../view/node_graphics.hpp"
#include"graphics_controller.hpp"
namespace NoderGraphics {
    class NodeController : public GraphicsController{
        using Node = Noder::Node;
        using NodeGraphics = NoderGraphics::NodeGraphics;
    protected:
        Node* node = nullptr;
        NodeGraphics* node_graphics = nullptr;
    public:
        NodeController(Node* node, NodeGraphics* graphics)
                      :node(node), node_graphics(graphics){
        }

        Node* GetNode(){
            return node;
        }

        NodeGraphics* GetNodeGraphics(){
            return node_graphics;
        }

    };
}
