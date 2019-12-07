#pragma once
#include<QGraphicsWidget>
#include<QLabel>
#include<QGraphicsEllipseItem>
#include<QGraphicsGridLayout>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsProxyWidget>
#include "src/controls/custom_label.hpp"
#include"../../../controls/int_spin_box.hpp"
#include"../../../core/view/port_view.hpp"
#include"../../../core/view/node_graphics.hpp"
namespace Mather {
    using namespace NoderGraphics;
    class Int64ValueNodeGraphics: public NodeGraphics{
        Q_OBJECT
    public:
        enum {INPUT_PORT, VALUE_SPIN_BOX, OUTPUT_PORT, UI_COUNT};
        Int64ValueNodeGraphics(PObject arg = nullptr){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Align(Qt::AlignCenter)
                            .Add(new LabelProxy("Int64 Value Node"), 0, 0, 1, 3).NextRow()
                            .Add(INPUT_PORT, new PortProxy()) .Add(VALUE_SPIN_BOX, new Int64SpinBoxProxy()) .Add(OUTPUT_PORT, new PortProxy())
                            .Layout());
        }

    };

    class Int32ValueNodeGraphics: public NodeGraphics{
        Q_OBJECT
    public:
        enum {INPUT_PORT, VALUE_SPIN_BOX, OUTPUT_PORT, UI_COUNT};
        Int32ValueNodeGraphics(PObject arg = nullptr){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Align(Qt::AlignCenter)
                            .Add(new LabelProxy("Int32 Value Node"), 0, 0, 1, 3).NextRow()
                            .Add(INPUT_PORT, new PortProxy()) .Add(VALUE_SPIN_BOX, new Int32SpinBoxProxy()) .Add(OUTPUT_PORT, new PortProxy())
                            .Layout());
        }

    };
}
