#pragma once
#include"../../../core/view/node_graphics.hpp"
#include"../../../controls/custom_label.hpp"
#include"../../../controls/int64_spin_box.hpp"
#include"../../../controls/image_view.hpp"
#include"../../../core/view/port_view.hpp"
namespace Imager {
    using namespace NoderGraphics;
    class BernsenNodeGraphics : public NodeGraphics{
    public:
        enum {INPUT_IMAGE_PORT, WINDOW_SIZE_PORT, WINDOW_SIZE_BOX, OUTPUT_PORT, UI_COUNT};
        BernsenNodeGraphics(){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Add(new LabelProxy("Bernsen Node"), 0, 0, 1, 3).NextRow()
                            .Add(INPUT_IMAGE_PORT, new PortProxy).Add(new LabelProxy("Input Image", Qt::AlignLeft)).NextRow()
                            .Add(WINDOW_SIZE_PORT, new PortProxy).Add(WINDOW_SIZE_BOX, new Int64SpinBoxProxy).NextRow()
                            .Skip().Add(new LabelProxy("Output", Qt::AlignRight)).Add(OUTPUT_PORT, new PortProxy)
                            .Layout());
        }
    };
}
