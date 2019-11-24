#pragma once
#include"../core/view/node_graphics.hpp"
#include<QComboBox>
using namespace NoderGraphics;
//class ComboBox : public QComboBox{
//    Q_OBJECT
//protected:
//    virtual void mousePressEvent(QMouseEvent *e)override{
//        emit MousePress();
//        QComboBox::mousePressEvent(e);
//    }

//    virtual void mouseReleaseEvent(QMouseEvent *e) override{
//        emit MouseRelease();
//        QComboBox::mouseReleaseEvent(e);
//    }
//    virtual void focusInEvent(QFocusEvent *e) override{
////        printf("combo focus in\n");

////        QComboBox::focusInEvent(e);
//    }

//    virtual void focusOutEvent(QFocusEvent *e) override{
////        printf("combo focus out\n");

////        QComboBox::focusOutEvent(e);
//    }
//signals:
//    void MousePress();
//    void MouseRelease();
//};

class ComboBoxProxy : public WidgetProxy{
public:
    ComboBoxProxy(){
//        this->stackBefore(nullptr);
        this->setWidget(combo_box);
//        QObject::connect(combo_box,
//                         static_cast<void(ComboBox::*)()>(&ComboBox::MousePress),
//                         this, [&](){
//            backup_z_value = this->zValue();
//            this->setZValue(99999999);
//        });
//        QObject::connect(combo_box,
//                         static_cast<void(ComboBox::*)()>(&ComboBox::MouseRelease),
//                         this, [&](){
//            printf("z: %f\n", backup_z_value);
//            if(backup_z_value != -1){
//                this->setZValue(backup_z_value);
//            }
//        });
    }
    ~ComboBoxProxy(){
        delete combo_box;
    }
private:
    QComboBox* combo_box = new QComboBox();
//    double backup_z_value = -1;
};
