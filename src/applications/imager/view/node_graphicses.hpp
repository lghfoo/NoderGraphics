#pragma once
#include"../../../core/view/node_graphics.hpp"
#include"../../../controls/custom_label.hpp"
#include"../../../core/view/port_view.hpp"
#include"../../../controls/int_spin_box.hpp"
namespace Imager {
    using namespace NoderGraphics;
    class GaussianNoiseNodeGraphics : public NodeGraphics{
    public:
        enum {SAMPLE_PORT, SAMPLE_BOX,
              WIDTH_PORT, WIDTH_BOX,
              HEIGHT_PORT, HEIGHT_BOX,
              OUTPUT_IMAGE_PORT, UI_COUNT};
        GaussianNoiseNodeGraphics(PObject arg = nullptr){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Add(new LabelProxy("Gaussian Noise"), 0, 0, 1, 4).NextRow()
                            .Add(SAMPLE_PORT, new PortProxy).Add(new LabelProxy("Samples:", Qt::AlignLeft|Qt::AlignVCenter)).Add(SAMPLE_BOX, new Int32SpinBoxProxy).NextRow()
                            .Add(WIDTH_PORT, new PortProxy).Add(new LabelProxy("Width:", Qt::AlignLeft|Qt::AlignVCenter)).Add(WIDTH_BOX, new Int32SpinBoxProxy).NextRow()
                            .Add(HEIGHT_PORT, new PortProxy).Add(new LabelProxy("Height:", Qt::AlignLeft|Qt::AlignVCenter)).Add(HEIGHT_BOX, new Int32SpinBoxProxy).NextRow()
                            .Skip().Skip().Add(new LabelProxy("Output", Qt::AlignRight | Qt::AlignVCenter)).Add(OUTPUT_IMAGE_PORT, new PortProxy)
                            .Layout());
        }
    };

    class VoronoiNoiseNodeGraphics : public NodeGraphics{
    public:
        enum {CELLW_PORT, CELLW_BOX,
              CELLH_PORT, CELLH_BOX,
              WIDTH_PORT, WIDTH_BOX,
              HEIGHT_PORT, HEIGHT_BOX,
              OUTPUT_IMAGE_PORT, UI_COUNT};
        VoronoiNoiseNodeGraphics(PObject arg = nullptr){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Add(new LabelProxy("Gaussian Noise"), 0, 0, 1, 4).NextRow()
                            .Add(CELLW_PORT, new PortProxy).Add(new LabelProxy("Cell Width:", Qt::AlignLeft|Qt::AlignVCenter)).Add(CELLW_BOX, new Int32SpinBoxProxy).NextRow()
                            .Add(CELLH_PORT, new PortProxy).Add(new LabelProxy("Cell Height:", Qt::AlignLeft|Qt::AlignVCenter)).Add(CELLH_BOX, new Int32SpinBoxProxy).NextRow()
                            .Add(WIDTH_PORT, new PortProxy).Add(new LabelProxy("Width:", Qt::AlignLeft|Qt::AlignVCenter)).Add(WIDTH_BOX, new Int32SpinBoxProxy).NextRow()
                            .Add(HEIGHT_PORT, new PortProxy).Add(new LabelProxy("Height:", Qt::AlignLeft|Qt::AlignVCenter)).Add(HEIGHT_BOX, new Int32SpinBoxProxy).NextRow()
                            .Skip().Skip().Add(new LabelProxy("Output", Qt::AlignRight | Qt::AlignVCenter)).Add(OUTPUT_IMAGE_PORT, new PortProxy)
                            .Layout());
        }
    };
}
