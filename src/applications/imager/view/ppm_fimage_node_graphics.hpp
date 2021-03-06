#pragma once
#include"../../../core/view/node_graphics.hpp"
#include"../../../controls/custom_label.hpp"
#include"../../../controls/file_box.hpp"
#include"../../../controls/image_view.hpp"
#include"../../../core/view/port_view.hpp"
namespace Imager {
    using namespace NoderGraphics;
    class PPMFImageNodeGraphics : public NodeGraphics{
    public:
        enum {INPUT_PORT, OUTPUT_PORT, UI_COUNT};
        PPMFImageNodeGraphics(PObject arg = nullptr){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Add(new LabelProxy("PPM File to Image"), 0, 0, 1, 3).NextRow()
                            .Add(INPUT_PORT, new PortProxy).Add(new LabelProxy("filename")).Add(OUTPUT_PORT, new PortProxy)
                            .Layout());
        }
    };
}
