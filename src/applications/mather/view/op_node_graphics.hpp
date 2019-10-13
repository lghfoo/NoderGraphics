#pragma once
#include<QGraphicsWidget>
#include<QLabel>
#include<QGraphicsEllipseItem>
#include<QGraphicsGridLayout>
#include<QGraphicsProxyWidget>
#include "src/controls/custom_label.hpp"
#include"../../../controls/int64_spin_box.hpp"
#include"../../../controls/port_widget.hpp"
#include"../../../core/node_graphics.hpp"
namespace Mather {
    using namespace NoderGraphics;
    class BinaryOpNodeGraphics: public NoderGraphics::NodeGraphics{
        Q_OBJECT
    protected:
        QVariant itemChange(GraphicsItemChange change, const QVariant &value)
        {
            if (change == ItemPositionHasChanged && scene()) {
                lhs_ellipse->NotifyPosChanged();
                rhs_ellipse->NotifyPosChanged();
                output_ellipse->NotifyPosChanged();
            }
            return QGraphicsItem::itemChange(change, value);
        }
    public:
        BinaryOpNodeGraphics(const QString& node_name){
            this->node_name_label->setText(node_name);
            node_name_label->setAlignment(Qt::AlignCenter);
            lhs_name_label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            rhs_name_label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            output_name_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

            node_name_label_proxy_widget->setWidget(node_name_label);
            lhs_name_label_proxy_widget->setWidget(lhs_name_label);
            rhs_name_label_proxy_widget->setWidget(rhs_name_label);
            output_name_label_proxy_widget->setWidget(output_name_label);
            lhs_ellipse_proxy_widget->setWidget(lhs_ellipse);
            rhs_ellipse_proxy_widget->setWidget(rhs_ellipse);
            output_ellipse_proxy_widget->setWidget(output_ellipse);
    //            lhs_spin_box_proxy_widget->setWidget(lhs_spin_box);
    //            rhs_spin_box_proxy_widget->setWidget(rhs_spin_box);
            main_layout->addItem(node_name_label_proxy_widget, 0, 0, 1, 3, Qt::AlignCenter);
            main_layout->addItem(lhs_name_label_proxy_widget, 1, 1, 1, 1, Qt::AlignCenter);
            main_layout->addItem(rhs_name_label_proxy_widget, 2, 1, 1, 1, Qt::AlignCenter);
            main_layout->addItem(output_name_label_proxy_widget, 3, 1, 1, 1, Qt::AlignCenter);
            main_layout->addItem(lhs_ellipse_proxy_widget, 1, 0, 1, 1, Qt::AlignCenter);
            main_layout->addItem(rhs_ellipse_proxy_widget, 2, 0, 1, 1, Qt::AlignCenter);
            main_layout->addItem(output_ellipse_proxy_widget, 3, 2, 1, 1, Qt::AlignCenter);
    //            main_layout->addItem(lhs_spin_box_proxy_widget, 1, 1);
    //            main_layout->addItem(rhs_spin_box_proxy_widget, 2, 0, 1, 2);
            this->setLayout(main_layout);
        }

        PortWidget* GetLhsPortGraphics(){
            return dynamic_cast<PortWidget*>(lhs_ellipse_proxy_widget->widget());
        }

        PortWidget* GetRhsPortGraphics(){
            return dynamic_cast<PortWidget*>(rhs_ellipse_proxy_widget->widget());
        }

        PortWidget* GetOutputPortGraphics(){
            return dynamic_cast<PortWidget*>(output_ellipse_proxy_widget->widget());
        }
    private:
        Label* node_name_label = new Label();
        Label* lhs_name_label = new Label("LHS");
        Label* rhs_name_label = new Label("RHS");
        Label* output_name_label = new Label("Output");
        PortWidget* lhs_ellipse = new PortWidget;
        PortWidget* rhs_ellipse = new PortWidget;
        PortWidget* output_ellipse = new PortWidget;
    //        Int64SpinBox* lhs_spin_box = new Int64SpinBox;
    //        Int64SpinBox* rhs_spin_box = new Int64SpinBox;

        QGraphicsProxyWidget* node_name_label_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* lhs_name_label_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* rhs_name_label_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* output_name_label_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* lhs_ellipse_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* rhs_ellipse_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* output_ellipse_proxy_widget = new QGraphicsProxyWidget;
    //        QGraphicsProxyWidget* lhs_spin_box_proxy_widget = new QGraphicsProxyWidget;
    //        QGraphicsProxyWidget* rhs_spin_box_proxy_widget = new QGraphicsProxyWidget;

        QGraphicsGridLayout* main_layout = new QGraphicsGridLayout;
    };
//    class Int64AddNodeGraphics: public NoderGraphics::NodeGraphics{
//        Q_OBJECT
//    protected:
//        QVariant itemChange(GraphicsItemChange change, const QVariant &value)
//        {
//            if (change == ItemPositionHasChanged && scene()) {
//                lhs_ellipse->NotifyPosChanged();
//                rhs_ellipse->NotifyPosChanged();
//                output_ellipse->NotifyPosChanged();
//            }
//            return QGraphicsItem::itemChange(change, value);
//        }
//    public:
//        Int64AddNodeGraphics(){



//            node_name_label->setAlignment(Qt::AlignCenter);
//            lhs_name_label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
//            rhs_name_label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
//            output_name_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

//            node_name_label_proxy_widget->setWidget(node_name_label);
//            lhs_name_label_proxy_widget->setWidget(lhs_name_label);
//            rhs_name_label_proxy_widget->setWidget(rhs_name_label);
//            output_name_label_proxy_widget->setWidget(output_name_label);
//            lhs_ellipse_proxy_widget->setWidget(lhs_ellipse);
//            rhs_ellipse_proxy_widget->setWidget(rhs_ellipse);
//            output_ellipse_proxy_widget->setWidget(output_ellipse);
////            lhs_spin_box_proxy_widget->setWidget(lhs_spin_box);
////            rhs_spin_box_proxy_widget->setWidget(rhs_spin_box);
//            main_layout->addItem(node_name_label_proxy_widget, 0, 0, 1, 3, Qt::AlignCenter);
//            main_layout->addItem(lhs_name_label_proxy_widget, 1, 1, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(rhs_name_label_proxy_widget, 2, 1, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(output_name_label_proxy_widget, 3, 1, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(lhs_ellipse_proxy_widget, 1, 0, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(rhs_ellipse_proxy_widget, 2, 0, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(output_ellipse_proxy_widget, 3, 2, 1, 1, Qt::AlignCenter);
////            main_layout->addItem(lhs_spin_box_proxy_widget, 1, 1);
////            main_layout->addItem(rhs_spin_box_proxy_widget, 2, 0, 1, 2);
//            this->setLayout(main_layout);
//        }

//        PortWidget* GetLhsPortGraphics(){
//            return dynamic_cast<PortWidget*>(lhs_ellipse_proxy_widget->widget());
//        }

//        PortWidget* GetRhsPortGraphics(){
//            return dynamic_cast<PortWidget*>(rhs_ellipse_proxy_widget->widget());
//        }

//        PortWidget* GetOutputPortGraphics(){
//            return dynamic_cast<PortWidget*>(output_ellipse_proxy_widget->widget());
//        }
//    private:
//        Label* node_name_label = new Label("Int64 Add Node");
//        Label* lhs_name_label = new Label("LHS");
//        Label* rhs_name_label = new Label("RHS");
//        Label* output_name_label = new Label("Output");
//        PortWidget* lhs_ellipse = new PortWidget;
//        PortWidget* rhs_ellipse = new PortWidget;
//        PortWidget* output_ellipse = new PortWidget;
////        Int64SpinBox* lhs_spin_box = new Int64SpinBox;
////        Int64SpinBox* rhs_spin_box = new Int64SpinBox;

//        QGraphicsProxyWidget* node_name_label_proxy_widget = new QGraphicsProxyWidget;
//        QGraphicsProxyWidget* lhs_name_label_proxy_widget = new QGraphicsProxyWidget;
//        QGraphicsProxyWidget* rhs_name_label_proxy_widget = new QGraphicsProxyWidget;
//        QGraphicsProxyWidget* output_name_label_proxy_widget = new QGraphicsProxyWidget;
//        QGraphicsProxyWidget* lhs_ellipse_proxy_widget = new QGraphicsProxyWidget;
//        QGraphicsProxyWidget* rhs_ellipse_proxy_widget = new QGraphicsProxyWidget;
//        QGraphicsProxyWidget* output_ellipse_proxy_widget = new QGraphicsProxyWidget;
////        QGraphicsProxyWidget* lhs_spin_box_proxy_widget = new QGraphicsProxyWidget;
////        QGraphicsProxyWidget* rhs_spin_box_proxy_widget = new QGraphicsProxyWidget;

//        QGraphicsGridLayout* main_layout = new QGraphicsGridLayout;
//    };
}
