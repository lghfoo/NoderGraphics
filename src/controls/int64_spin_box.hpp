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
        value_text = QString::number(value_text.toLongLong() + GetStep());
    }
    virtual void ValueDown()override{
        value_text = QString::number(value_text.toLongLong() - GetStep());
    }
    virtual void StepUp()override{
        step_text = QString::number(step_text.toLongLong() + 1);
    }
    virtual void StepDown()override{
        step_text = QString::number(step_text.toLongLong() - 1);
    }
private:
};

#endif // INT64_SPIN_BOX_HPP
