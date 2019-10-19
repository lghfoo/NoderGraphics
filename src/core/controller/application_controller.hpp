#pragma once
#include<QMainWindow>
#include<QMap>
//#include"../model/application.hpp"
#include"../view/main_view.hpp"
#include"connection_controller.hpp"
#include"node_controller.hpp"
//#include"node_controller_factory.hpp"
namespace NoderGraphics {
    class ApplicationController{
        using NodeController = NoderGraphics::NodeController;
    private:
        ApplicationController(){}
    public:
        static ApplicationController* GetInstance(){
            static ApplicationController* instance = new ApplicationController();
            return instance;
        }

        void Init(){
            ConnectionController::Init();
        }

    };
}
