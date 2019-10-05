#pragma once
#include<QMainWindow>
#include"../view/main_view.hpp"
#include"connection_controller.hpp"
namespace Mather {
    class ApplicationController{
    public:
        static int Run(int argc, char *argv[]){
            QApplication a(argc, argv);

            QMainWindow mainWindow;
            MainView* main_view = new MainView();
            mainWindow.setCentralWidget(main_view);
            mainWindow.show();

            ApplicationController::Init();

            return a.exec();
        }

        static void Init(){
            ConnectionController::Init();
        }
    };
}
