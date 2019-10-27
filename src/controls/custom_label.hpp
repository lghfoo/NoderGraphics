#pragma once
#include<QPaintEvent>
#include<QWidget>
#include<QPainter>
#include<QPainterPath>
#include<QDragEnterEvent>
#include<QDragLeaveEvent>
#include<QDragMoveEvent>
#include<QDrag>
#include<QDropEvent>
#include<QDebug>
#include<QMimeData>
#include<functional>
#include <QLabel>

#include "../core/view/node_graphics.hpp"
namespace NoderGraphics {
    class Label:public QLabel{
    public:
        Label(const QString& text):QLabel(text){
            auto pal = this->palette();
            pal.setColor(QPalette::Background, Qt::transparent);
            this->setPalette(pal);
        }
        Label(): Label(""){
        }
    };

    class LabelProxy : public WidgetProxy{
    public:
        LabelProxy(const QString& text, Qt::Alignment alignment = Qt::AlignCenter){
            auto label = new QLabel(text);
            label->setAlignment(alignment);
            auto pal = label->palette();
            pal.setColor(QPalette::Background, Qt::transparent);
            label->setPalette(pal);
            this->setWidget(label);
        }

        LabelProxy() : LabelProxy(""){

        }
    };
}
