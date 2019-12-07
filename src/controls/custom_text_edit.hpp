#pragma once
#include<QTextEdit>
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
        TextEditProxy(const QString& text, Qt::Alignment alignment = Qt::AlignCenter){
            auto text_edit = new TextEdit(text);
            text_edit->setAlignment(alignment);
            auto pal = text_edit->palette();
            pal.setColor(QPalette::Background, Qt::transparent);
            text_edit->setPalette(pal);
            this->setWidget(text_edit);

            QObject::connect(text_edit, &QTextEdit::textChanged, [=](){
                QString text = text_edit->toPlainText();
                this->NotifyListeners(&text);
            });
        }

        TextEditProxy() : TextEditProxy(""){

        }
    };
}
