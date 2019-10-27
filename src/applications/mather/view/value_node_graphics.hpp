#pragma once
#include<QGraphicsWidget>
#include<QLabel>
#include<QGraphicsEllipseItem>
#include<QGraphicsGridLayout>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsProxyWidget>
#include "src/controls/custom_label.hpp"
#include"../../../controls/int64_spin_box.hpp"
#include"../../../core/view/port_view.hpp"
#include"../../../core/view/node_graphics.hpp"
namespace Mather {
    using namespace NoderGraphics;
    class Int64ValueNodeGraphics: public NodeGraphics{
        Q_OBJECT
    public:
        enum {INPUT_PORT, VALUE_SPIN_BOX, OUTPUT_PORT, UI_COUNT};
        Int64ValueNodeGraphics(){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Align(Qt::AlignCenter)
                            .Add(new LabelProxy("Int64 Value Node"), 0, 0, 1, 3).NextRow()
                            .Add(INPUT_PORT, new PortProxy()) .Add(VALUE_SPIN_BOX, new Int64SpinBoxProxy()) .Add(OUTPUT_PORT, new PortProxy())
                            .Layout());
            auto spin_box = this->GetUI<Int64SpinBoxProxy>(VALUE_SPIN_BOX)->GetWidget<Int64SpinBox>();
            connect(spin_box, &Int64SpinBox::ValueChanged, this, &Int64ValueNodeGraphics::InputValueChanged);
        }

        void SetInputValue(long long value){
            this->GetUI<Int64SpinBoxProxy>(VALUE_SPIN_BOX)->GetWidget<Int64SpinBox>()->SetValue(value);
        }

        PortProxy* GetInputPortGraphics(){
            return this->GetUI<PortProxy>(INPUT_PORT);
        }

        PortProxy* GetOutputPortGraphics(){
            return this->GetUI<PortProxy>(OUTPUT_PORT);
        }
    signals:
        void InputValueChanged(long long);
    };



//    class Int64ValueNodeGraphics: public NodeGraphics{
//        Q_OBJECT
//    protected:
//        QVariant itemChange(GraphicsItemChange change, const QVariant &value)
//        {
//            if (change == ItemPositionHasChanged && scene()) {
//                input_port->NotifyPosChanged();
//                output_port->NotifyPosChanged();
//            }
//            return QGraphicsItem::itemChange(change, value);
//        }
//    public:
//        Int64ValueNodeGraphics(){
//            node_name_label->setAlignment(Qt::AlignCenter);
//            node_name_label_proxy_widget->setWidget(node_name_label);
//            input_spin_box_proxy_widget->setWidget(input_spin_box);
//            main_layout->addItem(node_name_label_proxy_widget, 0, 0, 1, 3, Qt::AlignCenter);
//            main_layout->addItem(input_port, 1, 0, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(input_spin_box_proxy_widget, 1, 1, 1, 1, Qt::AlignCenter);
//            main_layout->addItem(output_port, 1, 2, 1, 1, Qt::AlignCenter);
//            this->setLayout(main_layout);
//            connect(input_spin_box, &Int64SpinBox::ValueChanged, this, &Int64ValueNodeGraphics::InputValueChanged);
//        }

//        void SetInputValue(long long value){
//            input_spin_box->SetValue(value);
//        }

//        PortView* GetInputPortGraphics(){
//            return input_port;
//        }

//        PortView* GetOutputPortGraphics(){
//            return output_port;
//        }

//    signals:
//        void InputValueChanged(long long);
//    private:
//        Label* node_name_label = new Label("Int64 Value Node");
//        Int64SpinBox* input_spin_box = new Int64SpinBox;
//        QGraphicsProxyWidget* node_name_label_proxy_widget = new QGraphicsProxyWidget;
//        PortView* input_port = new PortView;
//        PortView* output_port = new PortView;
//        QGraphicsProxyWidget* input_spin_box_proxy_widget = new QGraphicsProxyWidget;
//        QGraphicsGridLayout* main_layout = new QGraphicsGridLayout;
//    };
}
