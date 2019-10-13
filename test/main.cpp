#include<QApplication>
#include"src/applications/mather/controller/application_controller.hpp"
int main(int argc, char *argv[])
{
    return Mather::ApplicationController::GetInstance()->Run(argc, argv);
}
