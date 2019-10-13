#pragma once
#include<QGraphicsWidget>
#include<QLabel>
#include<QGraphicsEllipseItem>
#include<QGraphicsGridLayout>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsProxyWidget>
#include "src/controls/custom_label.hpp"
#include"../../../controls/int64_spin_box.hpp"
#include"../../../controls/port_widget.hpp"
#include"../../../core/node_graphics.hpp"
namespace Mather {
    using namespace NoderGraphics;
    class Int64ValueNodeGraphics: public NodeGraphics{
        Q_OBJECT
    protected:
        QVariant itemChange(GraphicsItemChange change, const QVariant &value)
        {
            if (change == ItemPositionHasChanged && scene()) {
                input_ellipse->NotifyPosChanged();
                output_ellipse->NotifyPosChanged();
            }
            return QGraphicsItem::itemChange(change, value);
        }
    public:
        Int64ValueNodeGraphics(){

            node_name_label->setAlignment(Qt::AlignCenter);
//            input_name_label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
//            output_name_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

            node_name_label_proxy_widget->setWidget(node_name_label);
//            input_name_label_proxy_widget->setWidget(input_name_label);
//            output_name_label_proxy_widget->setWidget(output_name_label);
            input_ellipse_proxy_widget->setWidget(input_ellipse);
            output_ellipse_proxy_widget->setWidget(output_ellipse);
            input_spin_box_proxy_widget->setWidget(input_spin_box);

            main_layout->addItem(node_name_label_proxy_widget, 0, 0, 1, 3, Qt::AlignCenter);
//            main_layout->addItem(input_ellipse_proxy_widget, 1, 0, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(input_name_label_proxy_widget, 1, 1, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(input_spin_box_proxy_widget, 2, 1, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(output_name_label_proxy_widget, 3, 1, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(output_ellipse_proxy_widget, 3, 2, 1, 1, Qt::AlignCenter);

            main_layout->addItem(input_ellipse_proxy_widget, 1, 0, 1, 1, Qt::AlignCenter);
            main_layout->addItem(input_spin_box_proxy_widget, 1, 1, 1, 1, Qt::AlignCenter);
            main_layout->addItem(output_ellipse_proxy_widget, 1, 2, 1, 1, Qt::AlignCenter);

            this->setLayout(main_layout);

            connect(input_spin_box, &Int64SpinBox::ValueChanged, this, &Int64ValueNodeGraphics::InputValueChanged);
        }

        void SetInputValue(long long value){
            input_spin_box->SetValue(value);
        }

        PortWidget* GetInputPortGraphics(){
            return dynamic_cast<PortWidget*>(input_ellipse_proxy_widget->widget());
        }

        PortWidget* GetOutputPortGraphics(){
            return dynamic_cast<PortWidget*>(output_ellipse_proxy_widget->widget());
        }

    signals:
        void InputValueChanged(long long);
    private:
        Label* node_name_label = new Label("Int64 Value Node");
//        Label* input_name_label = new Label("Input");
//        Label* output_name_label = new Label("Output");
        PortWidget* input_ellipse = new PortWidget;
        PortWidget* output_ellipse = new PortWidget;
        Int64SpinBox* input_spin_box = new Int64SpinBox;

        QGraphicsProxyWidget* node_name_label_proxy_widget = new QGraphicsProxyWidget;
//        QGraphicsProxyWidget* input_name_label_proxy_widget = new QGraphicsProxyWidget;
//        QGraphicsProxyWidget* output_name_label_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* input_ellipse_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* output_ellipse_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* input_spin_box_proxy_widget = new QGraphicsProxyWidget;

        QGraphicsGridLayout* main_layout = new QGraphicsGridLayout;
    };
}
