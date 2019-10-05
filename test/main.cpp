#include<QApplication>
#include"src/applications/mather/controller/application_controller.hpp"
using namespace Mather;
int main(int argc, char *argv[])
{
    return ApplicationController::Run(argc, argv);
}
