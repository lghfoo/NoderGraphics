#pragma once
#include<QMainWindow>
#include<QMap>
#include"../model/application.hpp"
#include"../view/main_view.hpp"
#include"connection_controller.hpp"
#include"../../../core/node_controller.hpp"
#include"node_controller_factory.hpp"
namespace Mather {
    class ApplicationController{
        using NodeController = NoderGraphics::NodeController;
        using GraphicsType = MainView::GraphicsType;
        using NodeType = NodeFactory::NodeType;
    private:
        MainView* main_view = nullptr;
        Application* application = Application::GetInstance();
        QMap<GraphicsType, NodeType>type_map = {
            {GraphicsType::INT64_ADD, NodeType::INT64_ADD},
            {GraphicsType::INT64_SUBSTRACT, NodeType::INT64_SUBSTRACT},
            {GraphicsType::INT64_MULTIPLY, NodeType::INT64_MULTIPLY},
            {GraphicsType::INT64_DIVIDE, NodeType::INT64_DIVIDE},
            {GraphicsType::INT64_MODULUS, NodeType::INT64_MODULUS},
            {GraphicsType::INT64_VALUE, NodeType::INT64_VALUE}

        };
    private:
        ApplicationController(){}
        void Init(){
            main_view = new MainView();
            QObject::connect(main_view, &MainView::add_node,[&](const GraphicsType& type){
                NodeController* controller = NodeControllerFactory::CreateNodeController(type_map.value(type));
                auto scene = MainScene::GetInstance();
                scene->AddItemAtCursor(controller->GetNodeGraphics());
            });

            ConnectionController::Init();
        }
    public:
        static ApplicationController* GetInstance(){
            static ApplicationController* instance = new ApplicationController();
            return instance;
        }
        int Run(int argc, char *argv[]){
            QApplication a(argc, argv);
            ApplicationController::Init();

            QMainWindow mainWindow;
            mainWindow.setCentralWidget(main_view);
            mainWindow.show();

            return a.exec();
        }

    };
}
