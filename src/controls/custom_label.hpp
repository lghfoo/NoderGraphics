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
namespace NoderGraphics {
    class Label:public QLabel{
    public:
        Label(const QString& text):QLabel(text){
            auto pal = this->palette();
            pal.setColor(QPalette::Background, Qt::transparent);
            this->setPalette(pal);
            QLabel l("sdf");
        }
        Label(): Label(""){
        }
    };
}
