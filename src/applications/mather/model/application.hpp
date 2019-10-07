#pragma once
#include<QMainWindow>
#include"Noder/src/applications/mather/op_node.hpp"
#include"Noder/src/core/utility/utility.hpp"
namespace Mather {
    class Application{
    private:
        Application(){

        }

        LinkedList<Node*>nodes = {};
    public:
        static Application* GetInstance(){
            static Application* instance = new Application();
            return instance;
        }

        void AddNode(Node* node){
            nodes.Append(node);
        }

        void RemoveNode(Node* node){
            nodes.Remove(node);
        }
    };
}
