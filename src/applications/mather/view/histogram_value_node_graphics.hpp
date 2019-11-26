#pragma once
#include<QGraphicsWidget>
#include<QLabel>
#include<QGraphicsEllipseItem>
#include<QGraphicsGridLayout>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsProxyWidget>
#include "src/controls/custom_label.hpp"
#include"../../../controls/histogram_view.hpp"
#include"../../../core/view/port_view.hpp"
#include"../../../core/view/node_graphics.hpp"
namespace Mather {
    using namespace NoderGraphics;
    class HistogramValueNodeGraphics: public NodeGraphics{
        Q_OBJECT
    public:
        enum {INPUT_PORT, HISTOGRAM_VIEW, OUTPUT_PORT, UI_COUNT};
        HistogramValueNodeGraphics(PObject arg = nullptr){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Align(Qt::AlignCenter)
                            .Add(new LabelProxy("Histogram"), 0, 0, 1, 3).NextRow()
                            .Add(INPUT_PORT, new PortProxy()) .Add(HISTOGRAM_VIEW, new HistogramProxy()) .Add(OUTPUT_PORT, new PortProxy())
                            .Layout());

        }
    };

}
