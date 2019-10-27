#pragma once
#include"../../../controls/custom_label.hpp"
#include"../../../controls/custom_text_edit.hpp"
#include"../../../core/view/port_view.hpp"
#include"../../../core/view/node_graphics.hpp"
namespace Texter {
    using namespace NoderGraphics;
    class TextValueNodeGraphics : public NodeGraphics{
    public:
        enum {INPUT_PORT, OUTPUT_PORT, TEXT_EDIT, UI_COUNT};
        TextValueNodeGraphics(){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Add(new LabelProxy("Text"), 0, 0, 1, 3).NextRow()
                            .Add(INPUT_PORT, new PortProxy).Add(TEXT_EDIT, new TextEditProxy("", Qt::AlignLeft)).Add(OUTPUT_PORT, new PortProxy)
                            .Layout());
        }
    };
}
