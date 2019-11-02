#pragma once
#include"../node_graphics.hpp"
#include"../port_view.hpp"
#include"../../../controls/custom_label.hpp"
namespace NoderGraphics {
    class Label_1_1 : public NodeGraphics{
    public:
        enum {INPUT_PORT, OUTPUT_PORT, UI_COUNT};
        Label_1_1(const QString& name, const QString& src_label = "Src", const QString& dst_label = "Dst"){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Add(new LabelProxy(name), 0, 0, 1, 4).NextRow()
                            .Add(INPUT_PORT, new PortProxy).Add(new LabelProxy(src_label)).Add(new LabelProxy(dst_label)).Add(OUTPUT_PORT, new PortProxy)
                            .Layout());
        }
    };
}
