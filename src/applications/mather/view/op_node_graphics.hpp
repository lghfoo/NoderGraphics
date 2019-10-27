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
        BinaryOpNodeGraphics(const QString& node_name){
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

//    class BinaryOpNodeGraphics: public NoderGraphics::NodeGraphics{
//        Q_OBJECT
//    protected:
//        QVariant itemChange(GraphicsItemChange change, const QVariant &value)
//        {
//            if (change == ItemPositionHasChanged && scene()) {
//                lhs_port->NotifyPosChanged();
//                rhs_port->NotifyPosChanged();
//                output_port->NotifyPosChanged();
//            }
//            return QGraphicsItem::itemChange(change, value);
//        }
//    public:
//        BinaryOpNodeGraphics(const QString& node_name){
//            this->node_name_label->setText(node_name);
//            node_name_label->setAlignment(Qt::AlignCenter);
//            lhs_name_label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
//            rhs_name_label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
//            output_name_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

//            node_name_label_proxy_widget->setWidget(node_name_label);
//            lhs_name_label_proxy_widget->setWidget(lhs_name_label);
//            rhs_name_label_proxy_widget->setWidget(rhs_name_label);
//            output_name_label_proxy_widget->setWidget(output_name_label);
//            main_layout->addItem(node_name_label_proxy_widget, 0, 0, 1, 3, Qt::AlignCenter);
//            main_layout->addItem(lhs_name_label_proxy_widget, 1, 1, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(rhs_name_label_proxy_widget, 2, 1, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(output_name_label_proxy_widget, 3, 1, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(lhs_port, 1, 0, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(rhs_port, 2, 0, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(output_port, 3, 2, 1, 1, Qt::AlignCenter);
//            this->setLayout(main_layout);
//        }

//        PortView* GetLhsPortGraphics(){
//            return lhs_port;
//        }

//        PortView* GetRhsPortGraphics(){
//            return rhs_port;
//        }

//        PortView* GetOutputPortGraphics(){
//            return output_port;
//        }
//    private:
//        QGraphicsProxyWidget* node_name_label_proxy_widget = new QGraphicsProxyWidget;
//        QGraphicsProxyWidget* lhs_name_label_proxy_widget = new QGraphicsProxyWidget;
//        QGraphicsProxyWidget* rhs_name_label_proxy_widget = new QGraphicsProxyWidget;
//        QGraphicsProxyWidget* output_name_label_proxy_widget = new QGraphicsProxyWidget;
//        PortView* lhs_port = new PortView;
//        PortView* rhs_port = new PortView;
//        PortView* output_port = new PortView;

//        Label* node_name_label = new Label();
//        Label* lhs_name_label = new Label("LHS");
//        Label* rhs_name_label = new Label("RHS");
//        Label* output_name_label = new Label("Output");

//        QGraphicsGridLayout* main_layout = new QGraphicsGridLayout;
//    };
}
