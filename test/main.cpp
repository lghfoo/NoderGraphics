#include<QApplication>
#include<QTabWidget>
#include<QMainWindow>
#include"src/applications/mather/controller/application_controller.hpp"
#include"src/core/controller/application_controller.hpp"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NoderGraphics::ApplicationController::GetInstance()->Init();
    Mather::ApplicationController* controller = new Mather::ApplicationController();
    QMainWindow main_window;
    QTabWidget tab_widget;
    main_window.setCentralWidget(&tab_widget);
    tab_widget.addTab(controller->GetMainView(), "Mather");
    main_window.show();
    return a.exec();
}
