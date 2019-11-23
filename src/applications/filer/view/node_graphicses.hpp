#pragma once
#include"../../../core/view/node_graphics.hpp"
#include"../../../controls/custom_label.hpp"
#include"../../../controls/file_box.hpp"
#include"../../../core/view/port_view.hpp"
namespace Filer {
    using namespace NoderGraphics;
    class FilelenNodeGraphics : public NodeGraphics{
    public:
        enum {INPUT_PORT, FILE_BOX, OUTPUT_PORT, UI_COUNT};
        FilelenNodeGraphics(){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Add(new LabelProxy("Filelen"), 0, 0, 1, 3).NextRow()
                            .Add(INPUT_PORT, new PortProxy).Add(FILE_BOX, new FileBoxProxy).Add(OUTPUT_PORT, new PortProxy)
                            .Layout());
        }
    };
}
