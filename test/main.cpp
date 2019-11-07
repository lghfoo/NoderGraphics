#include<QApplication>
#include<QTabWidget>
#include<QMainWindow>
#include"src/applications/mather/controller/application_controller.hpp"
#include"src/applications/filer/controller/application_controller.hpp"
#include"src/applications/texter/controller/application_controller.hpp"
#include"src/applications/imager/controller/application_controller.hpp"
#include"src/core/controller/application_controller.hpp"
#include"testqchart.hpp"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NoderGraphics::ApplicationController::GetInstance()->Init();

    auto mather_controller = new Mather::ApplicationController;
    auto texter_controller = new Texter::ApplicationController;
    auto filer_controller = new Filer::ApplicationController;
    auto imager_controller = new Imager::ApplicationController;

    QMainWindow main_window;
    QTabWidget tab_widget;
    main_window.setCentralWidget(&tab_widget);

    tab_widget.addTab(imager_controller->GetMainView(), "Imager");
    tab_widget.addTab(filer_controller->GetMainView(), "Filer");
    tab_widget.addTab(texter_controller->GetMainView(), "Texter");
    tab_widget.addTab(mather_controller->GetMainView(), "Mather");

    main_window.show();

    Test::TestQChart();
    return a.exec();
}
