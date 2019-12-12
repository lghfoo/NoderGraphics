#pragma once
#include"spin_box_base.hpp"
#include"../core/view/node_graphics.hpp"
namespace NoderGraphics {
    class Int64SpinBox: public SpinBoxBase{
        Q_OBJECT
    public:
        long long GetValue(){
            return value_text.toLongLong();
        }
        long long GetStep(){
            return step_text.toLongLong();
        }
        virtual void ValueUp()override{
            auto value = value_text.toLongLong() + GetStep();
            value_text = QString::number(value);
            emit ValueChanged(value);
        }
        virtual void ValueDown()override{
            auto value = value_text.toLongLong() - GetStep();
            value_text = QString::number(value);
            emit ValueChanged(value);
        }
        virtual void SetValue(long long value){
            value_text = QString::number(value);
            emit ValueChanged(value);
            SpinBoxBase::update();
        }
        virtual void StepUp()override{
            step_text = QString::number(step_text.toLongLong() + 1);
        }
        virtual void StepDown()override{
            step_text = QString::number(step_text.toLongLong() - 1);
        }
    protected:
        virtual void keyPressEvent(QKeyEvent* event)override{
            SpinBoxBase::keyPressEvent(event);
            if(event->key() == Qt::Key_Enter){
                emit ValueChanged(this->GetValue());
            }
        }
        void focusOutEvent(QFocusEvent* event)override{
            if(this->cached_value == this->value_text){
                emit ValueChanged(this->GetValue());
            }
            SpinBoxBase::focusOutEvent(event);
        }
    signals:
        void ValueChanged(long long);
    private:
    };

    class Int64SpinBoxProxy : public WidgetProxy{
    public:
        Int64SpinBoxProxy(){
            auto box = new Int64SpinBox();
            this->setWidget(box);
            QObject::connect(box, &Int64SpinBox::ValueChanged, [=](long long value){
                this->NotifyListeners(&value);
            });
        }
    };

    class Int32SpinBox: public SpinBoxBase{
        Q_OBJECT
    public:
        int GetValue(){
            return value_text.toInt();
        }
        int GetStep(){
            return step_text.toInt();
        }
        virtual void ValueUp()override{
            auto value = value_text.toInt() + GetStep();
            value_text = QString::number(value);
            emit ValueChanged(value);
        }
        virtual void ValueDown()override{
            auto value = value_text.toInt() - GetStep();
            value_text = QString::number(value);
            emit ValueChanged(value);
        }
        virtual void SetValue(int value){
            value_text = QString::number(value);
            emit ValueChanged(value);
            SpinBoxBase::update();
        }
        virtual void StepUp()override{
            step_text = QString::number(step_text.toLongLong() + 1);
        }
        virtual void StepDown()override{
            step_text = QString::number(step_text.toLongLong() - 1);
        }
    protected:
        virtual void keyPressEvent(QKeyEvent* event)override{
            SpinBoxBase::keyPressEvent(event);
            if(event->key() == Qt::Key_Enter){
                emit ValueChanged(this->GetValue());
            }
        }

        void focusOutEvent(QFocusEvent* event)override{
            if(this->cached_value != this->value_text){
                emit ValueChanged(this->GetValue());
            }
            SpinBoxBase::focusOutEvent(event);
        }
    signals:
        void ValueChanged(int);
    private:
    };

    class Int32SpinBoxProxy : public WidgetProxy{
    public:
        Int32SpinBoxProxy(){
            auto box = new Int32SpinBox();
            this->setWidget(box);
            QObject::connect(box, &Int32SpinBox::ValueChanged, [=](int value){
                this->NotifyListeners(&value);
            });
        }
    };
}

