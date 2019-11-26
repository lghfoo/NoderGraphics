#pragma once
#include<QGraphicsWidget>
#include<QLabel>
#include<QGraphicsEllipseItem>
#include<QGraphicsGridLayout>
#include<QGraphicsProxyWidget>
#include "src/controls/custom_label.hpp"
#include"../../../controls/int64_spin_box.hpp"
#include"../../../core/view/port_view.hpp"
#include"../../../core/view/node_graphics.hpp"
namespace Mather {
    using namespace NoderGraphics;
    class BinaryOpNodeGraphics: public NodeGraphics{
        Q_OBJECT
    public:
        enum {LhsPort, RhsPort, OutputPort, UICount};
        BinaryOpNodeGraphics(PObject arg = nullptr){
            QString node_name = arg? *static_cast<QString*>(arg) : "";
            this->setLayout(NodeLayoutBuilder(&(this->uis), UICount)
                            .Add(new LabelProxy(node_name), 0, 0, 1, 3).NextRow()
                            .Add(LhsPort, new PortProxy()).Add(new LabelProxy("LHS", Qt::AlignVCenter | Qt::AlignLeft)).NextRow()
                            .Add(RhsPort, new PortProxy()).Add(new LabelProxy("RHS", Qt::AlignVCenter | Qt::AlignLeft)).NextRow()
                            .Skip().Add(new LabelProxy("Output", Qt::AlignVCenter | Qt::AlignRight)).Add(OutputPort, new PortProxy())
                            .Layout());
        }
        PortProxy* GetLhsPortGraphics(){
            return this->GetUI<PortProxy>(LhsPort);
        }

        PortProxy* GetRhsPortGraphics(){
            return this->GetUI<PortProxy>(RhsPort);
        }

        PortProxy* GetOutputPortGraphics(){
            return this->GetUI<PortProxy>(OutputPort);
        }
    };
}
