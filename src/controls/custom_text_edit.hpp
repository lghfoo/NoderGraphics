#pragma once
#include<QTextEdit>
#include<QLineEdit>
#include<QLinkedList>
#include "../core/view/node_graphics.hpp"
namespace NoderGraphics {
    class TextEdit:public QTextEdit{
    public:
        TextEdit(const QString& text):QTextEdit(text){
            auto pal = this->palette();
            pal.setColor(QPalette::Background, Qt::transparent);
            this->setPalette(pal);
        }
        TextEdit(): TextEdit(""){
        }
    };

    class TextEditProxy : public WidgetProxy{
    public:
        TextEditProxy(const QString& text, Qt::Alignment alignment = Qt::AlignLeft){
            auto text_edit = new TextEdit(text);
            text_edit->setAlignment(alignment);
            this->setWidget(text_edit);

            QObject::connect(text_edit, &QTextEdit::textChanged, [=](){
                QString text = text_edit->toPlainText();
                this->NotifyListeners(&text);
            });
        }

        TextEditProxy() : TextEditProxy(""){

        }
    };


    class LineEdit : public QLineEdit{
    };

    class LineEditProxy : public WidgetProxy{
    public:
        LineEditProxy(){
            auto line_edit = new LineEdit;
            this->setWidget(line_edit);
            connect(line_edit, &QLineEdit::textChanged, [=](){
                auto text = line_edit->text();
                this->NotifyListeners(&text);
            });
        }
    };
}
