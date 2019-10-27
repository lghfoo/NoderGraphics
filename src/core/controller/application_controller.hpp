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
        using AddNodeHandler = MainView::AddNodeHandler;
        using NodeController = NoderGraphics::NodeController;
    public:
        ApplicationController(){}
        static ApplicationController* GetInstance(){
            static ApplicationController* instance = new ApplicationController();
            return instance;
        }

        void Init(){
            ConnectionController::Init();
        }

        const MainView* GetMainView()const{
            return main_view;
        }

        MainView* GetMainView(){
            return main_view;
        }
    protected:
        MainView* main_view = new MainView();
    };
}
