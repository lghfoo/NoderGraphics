#pragma once
#include"spin_box_base.hpp"
class DoubleSpinBox: public SpinBoxBase{
    Q_OBJECT
public:
    DoubleSpinBox(){
        this->value_text = "0.0";
        this->step_text = "1.0";
    }
    double GetValue(){
        return value_text.toDouble();
    }
    double GetStep(){
        return step_text.toDouble();
    }
    virtual void ValueUp()override{
        value_text = QString::number(value_text.toDouble() + GetStep());
    }
    virtual void ValueDown()override{
        value_text = QString::number(value_text.toDouble() - GetStep());
    }
    virtual void StepUp()override{
        step_text = QString::number(step_text.toDouble() + 0.1);
    }
    virtual void StepDown()override{
        step_text = QString::number(step_text.toDouble() - 0.1);
    }
private:
};

