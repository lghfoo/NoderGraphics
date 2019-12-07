#include "../core/view/node_graphics.hpp"
#include <QLineEdit>
#include <QFileDialog>
#pragma once
using namespace NoderGraphics;
class FileBox : public QLineEdit{
protected:
    virtual void mousePressEvent(QMouseEvent *e) override{
        if(e->button() == Qt::MidButton){
            auto filename = QFileDialog::getOpenFileName();
            if(!filename.isEmpty()){
                this->setText(filename);
            }
        }
        else{
            QLineEdit::mousePressEvent(e);
        }
    }

};

class FileBoxProxy : public WidgetProxy{
    Q_OBJECT
public:

    FileBoxProxy(){
        this->setWidget(file_edit);
        connect(file_edit, &QLineEdit::textChanged, [=](){
            auto text = file_edit->text();
            this->NotifyListeners(&text);
        });
    }
private:
    FileBox* file_edit = new FileBox();

};
