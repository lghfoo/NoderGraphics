#pragma once
#include<QGraphicsWidget>
#include<QLabel>
#include<QGraphicsEllipseItem>
#include<QGraphicsGridLayout>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsProxyWidget>
#include"../../../controls/int64_spin_box.hpp"
#include"../../../core/view/node_graphics.hpp"
#include"op_node_graphics.hpp"
#include"value_node_graphics.hpp"
namespace Mather {
    enum NodeType{
      INT64_ADD,
      INT64_VALUE
    };
    class NodeGraphicsFactory{
    public:
        static NoderGraphics::NodeGraphics* CreateNodeGraphics(const NodeType& type){
            switch (type) {
            case INT64_VALUE:
                return new Int64ValueNodeGraphics();
            default:
                return nullptr;
            }
        }
    };
}
