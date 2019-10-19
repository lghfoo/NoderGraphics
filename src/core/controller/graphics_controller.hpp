#pragma once
#include<QGraphicsWidget>
#include<QDebug>
#include"Noder/src/core/noder/node.hpp"
namespace NoderGraphics {
    class GraphicsController{
    protected:
        bool is_busy = false;
    public:
        bool IsBusy(){
            return is_busy;
        }

        void SetBusy(bool busy){
            is_busy = busy;
        }
    };
}
