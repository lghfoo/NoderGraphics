#pragma once
#include"../core/view/node_graphics.hpp"
#include <QLabel>
#include"Noder/src/core/utility/utility.hpp"
#include<QGraphicsView>
#include<QGraphicsPixmapItem>
using namespace NoderGraphics;
class ImageView : public QLabel{
public:
    ImageView(){
        QImage image(128, 128, QImage::Format_ARGB32);
        image.fill(Qt::black);
        this->SetImage(image);

//        this->setPixmap(QPixmap::fromImage(image));
        this->setStyleSheet("QLabel{border:3px solid black;}");
    }
    void SetImage(const QImage& image){
        this->setPixmap(QPixmap::fromImage(image));
        this->setFixedSize(image.size());
    }

    virtual void resizeEvent(QResizeEvent *event) override{
        if(resizeListener.IsValid()){
            resizeListener(event->size().width(), event->size().height());
        }
        QLabel::resizeEvent(event);
    }

    void SetResizeListener(const Noder::Listener<void, int, int>& listener){
        this->resizeListener = listener;
    }
private:
    Noder::Listener<void, int, int> resizeListener;
};
//class ImageView : public QGraphicsView{
//public:
//    ImageView(){
//        QImage image(128, 128, QImage::Format_ARGB32);
//        image.fill(Qt::black);
//        this->SetImage(image);

////        this->setPixmap(QPixmap::fromImage(image));
//        this->setStyleSheet("QGraphicsView{border:3px solid black;}");
//    }
//    void SetImage(const QImage& image){
//        pixmap_item->setPixmap(QPixmap::fromImage(image));
//        this->setFixedSize(image.size());
//    }

//    virtual void resizeEvent(QResizeEvent *event) override{
//        if(resizeListener.IsValid()){
//            resizeListener(event->size().width(), event->size().height());
//        }
//        QGraphicsView::resizeEvent(event);
//    }

//    void SetResizeListener(const Noder::Listener<void, int, int>& listener){
//        this->resizeListener = listener;
//    }
//private:
//    Noder::Listener<void, int, int> resizeListener;
//    QGraphicsPixmapItem* pixmap_item = new QGraphicsPixmapItem;
//};
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
