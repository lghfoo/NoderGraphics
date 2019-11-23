#pragma once
#include"../core/view/node_graphics.hpp"
#include<QComboBox>
using namespace NoderGraphics;
class ComboBoxProxy : public WidgetProxy{
public:
    ComboBoxProxy(){
        this->setWidget(combo_box);
    }
    ~ComboBoxProxy(){
        delete combo_box;
    }
private:
    QComboBox* combo_box = new QComboBox();
};
