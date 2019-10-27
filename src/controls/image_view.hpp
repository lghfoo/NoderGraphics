#pragma once
#include"../core/view/node_graphics.hpp"
#include <QLabel>
using namespace NoderGraphics;
class ImageView : public QLabel{
public:
    ImageView(){

    }
    ~ImageView(){
        delete image;
    }
private:
    QImage* image = new QImage();
};
class ImageViewProxy : public WidgetProxy{
public:
    ImageViewProxy(){
        this->setWidget(image_view);
    }
    ~ImageViewProxy(){
        delete image_view;
    }
private:
    ImageView* image_view = new ImageView();
};
