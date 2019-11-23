#pragma once
#include"../../../core/view/node_graphics.hpp"
#include"../../../controls/custom_label.hpp"
#include"../../../controls/file_box.hpp"
#include"../../../controls/int64_spin_box.hpp"
#include"../../../controls/combo_box.hpp"
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

    class PickBufferFromFilenameNodeGraphics : public NodeGraphics{
    public:
        enum{FILE_INPUT_PORT, FILE_BOX,
             BEGIN_ADDRESS_INPUT_PORT, BEGIN_ADDRESS_BOX,
             BUFFER_SIZE_INPUT_PORT, BUFFER_SIZE_BOX,
             END_ADDRESS_OUTPUT_PORT,
             OUTPUT_PORT,
             UI_COUNT};
        PickBufferFromFilenameNodeGraphics(){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Add(new LabelProxy("Pick Buffer From File"), 0, 0, 1, 3).NextRow()
                            .Add(FILE_INPUT_PORT, new PortProxy).Add(FILE_BOX, new FileBoxProxy).NextRow()
                            .Add(BEGIN_ADDRESS_INPUT_PORT, new PortProxy).Add(BEGIN_ADDRESS_BOX, new Int64SpinBoxProxy).NextRow()
                            .Add(BUFFER_SIZE_INPUT_PORT, new PortProxy).Add(BUFFER_SIZE_BOX, new Int64SpinBoxProxy).NextRow()
                            .Skip().Add(new LabelProxy("Buffer")).Add(OUTPUT_PORT, new PortProxy)
                            .Layout());
        }
    };

    class PickNumberFromBufferNodeGraphics : public NodeGraphics{
    public:
        enum{
            BUFFER_INPUT_PORT,
            BEGIN_ADDRESS_PORT, BEGIN_ADDRESS_BOX,
            NUMBER_TYPE_PORT, NUMBER_TYPE_BOX,
            FORMAT_TYPE_PORT, FORMAT_TYPE_BOX,
            ENDIAN_TYPE_PORT, ENDIAN_TYPE_BOX,
            END_ADDRESS_OUTPUT_PORT,
            NUMBER_OUTPUT_PORT,
            UI_COUNT
        };
        PickNumberFromBufferNodeGraphics(){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Add(new LabelProxy("Pick Number From Buffer"), 0, 0, 1, 3).NextRow()
                            .Add(BUFFER_INPUT_PORT, new PortProxy).Add(new LabelProxy("Target Buffer")).NextRow()
                            .Add(BEGIN_ADDRESS_PORT, new PortProxy).Add(BEGIN_ADDRESS_BOX, new Int64SpinBoxProxy).NextRow()
                            .Add(NUMBER_TYPE_PORT, new PortProxy).Add(NUMBER_TYPE_BOX, new ComboBoxProxy).NextRow()
                            .Add(FORMAT_TYPE_PORT, new PortProxy).Add(FORMAT_TYPE_BOX, new ComboBoxProxy).NextRow()
                            .Add(ENDIAN_TYPE_PORT, new PortProxy).Add(ENDIAN_TYPE_BOX, new ComboBoxProxy).NextRow()
                            .Skip().Add(new LabelProxy("End")).Add(END_ADDRESS_OUTPUT_PORT, new PortProxy).NextRow()
                            .Skip().Add(new LabelProxy("Number")).Add(NUMBER_OUTPUT_PORT, new PortProxy).NextRow()
                            .Layout());
        }

    };
}
