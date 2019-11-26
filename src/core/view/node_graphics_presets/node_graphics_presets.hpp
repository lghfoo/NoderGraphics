#pragma once
#include"../node_graphics.hpp"
#include"../port_view.hpp"
#include"../../../controls/custom_label.hpp"
namespace NoderGraphics {
    class Label_1_1 : public NodeGraphics{
    public:
        enum {INPUT_PORT, OUTPUT_PORT, UI_COUNT};
        Label_1_1(PObject arg){
            QString name = arg? *static_cast<QString*>(arg) : "";
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Add(new LabelProxy(name), 0, 0, 1, 4).NextRow()
                            .Add(INPUT_PORT, new PortProxy).Add(new LabelProxy("Src")).Add(new LabelProxy("Dst")).Add(OUTPUT_PORT, new PortProxy)
                            .Layout());
        }
    };
}
