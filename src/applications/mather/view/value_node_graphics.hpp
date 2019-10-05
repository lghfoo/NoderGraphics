#pragma once
#include<QGraphicsWidget>
#include<QLabel>
#include<QGraphicsEllipseItem>
#include<QGraphicsGridLayout>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsProxyWidget>
#include"../../../controls/int64_spin_box.hpp"
#include"../../../controls/port_widget.hpp"
#include"../../../core/node_graphics_base.hpp"
namespace Mather {
    class Int64ValueNodeGraphics: public NoderGraphics::NodeGraphicsBase{
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

            this->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable);
            this->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);

            node_name_label->setAlignment(Qt::AlignCenter);
            input_name_label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            output_name_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

            node_name_label_proxy_widget->setWidget(node_name_label);
            input_name_label_proxy_widget->setWidget(input_name_label);
            output_name_label_proxy_widget->setWidget(output_name_label);
            input_ellipse_proxy_widget->setWidget(input_ellipse);
            output_ellipse_proxy_widget->setWidget(output_ellipse);
            input_spin_box_proxy_widget->setWidget(input_spin_box);

            main_layout->addItem(node_name_label_proxy_widget, 0, 0, 1, 3, Qt::AlignCenter);
            main_layout->addItem(input_ellipse_proxy_widget, 1, 0, 1, 1, Qt::AlignCenter);
            main_layout->addItem(input_name_label_proxy_widget, 1, 1, 1, 1, Qt::AlignCenter);
            main_layout->addItem(input_spin_box_proxy_widget, 2, 1, 1, 1, Qt::AlignCenter);
            main_layout->addItem(output_name_label_proxy_widget, 3, 1, 1, 1, Qt::AlignCenter);
            main_layout->addItem(output_ellipse_proxy_widget, 3, 2, 1, 1, Qt::AlignCenter);

            this->setLayout(main_layout);
        }
    private:
        QLabel* node_name_label = new QLabel("Int64 Value Node");
        QLabel* input_name_label = new QLabel("Input");
        QLabel* output_name_label = new QLabel("Output");
        PortWidget* input_ellipse = new PortWidget;
        PortWidget* output_ellipse = new PortWidget;
        Int64SpinBox* input_spin_box = new Int64SpinBox;

        QGraphicsProxyWidget* node_name_label_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* input_name_label_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* output_name_label_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* input_ellipse_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* output_ellipse_proxy_widget = new QGraphicsProxyWidget;
        QGraphicsProxyWidget* input_spin_box_proxy_widget = new QGraphicsProxyWidget;

        QGraphicsGridLayout* main_layout = new QGraphicsGridLayout;
    public:
//        void mousePressEvent(QGraphicsSceneMouseEvent* event)override{

//            if(nullptr){
//                qDebug()<<"xxx";
//            }
//            else{
//                qDebug()<<"item is null";
//            }
//            QGraphicsWidget::mousePressEvent(event);
//        }
    };
}
