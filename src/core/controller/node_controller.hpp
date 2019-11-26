#pragma once
#include<QGraphicsWidget>
#include<QDebug>
#include"Noder/src/core/noder/node.hpp"
#include"../view/node_graphics.hpp"
#include"graphics_controller.hpp"
#include"Noder/src/core/object.hpp"
namespace NoderGraphics {
    using PObject = Noder::PObject;
    template<typename NodeType, typename GraphicsType>
    class NodeController : public GraphicsController{
    public:
        using Node = Noder::Node;
        using NodeGraphics = NoderGraphics::NodeGraphics;
    protected:
        NodeType* node = nullptr;
        GraphicsType* node_graphics = nullptr;
    public:
        NodeController(PObject graphics_arg = nullptr,
                       PObject node_arg = nullptr){
            node = new NodeType(node_arg);
            node_graphics = new GraphicsType(graphics_arg);
        }
        Node* GetNode(){
            return node;
        }

        NodeGraphics* GetNodeGraphics(){
            return node_graphics;
        }

    };
}
