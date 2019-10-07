#ifndef INT64_SPIN_BOX_HPP
#define INT64_SPIN_BOX_HPP
#include"spin_box_base.hpp"
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
signals:
    void ValueChanged(long long);
private:
};

#endif // INT64_SPIN_BOX_HPP
