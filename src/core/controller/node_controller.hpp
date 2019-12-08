#pragma once
#include<QGraphicsWidget>
#include<QDebug>
#include"Noder/src/core/noder/node.hpp"
#include"../view/node_graphics.hpp"
#include"graphics_controller.hpp"
#include"Noder/src/core/object.hpp"
#include"Noder/src/core/noder/port.hpp"
#include"../../controls/combo_box.hpp"
#include"../../controls/custom_label.hpp"
#include"../../controls/custom_text_edit.hpp"
#include"../../controls/double_spin_box.hpp"
#include"../../controls/file_box.hpp"
#include"../../controls/histogram_view.hpp"
#include"../../controls/image_view.hpp"
#include"../../controls/int_spin_box.hpp"

namespace NoderGraphics {
    using PObject = Noder::PObject;
    using Port = Noder::Port;
    template<typename NodeType, typename GraphicsType>
    class NodeController : public GraphicsController{
    public:
        using Node = Noder::Node;
        using NodeGraphics = NoderGraphics::NodeGraphics;
    protected:
        NodeType* node = nullptr;
        GraphicsType* node_graphics = nullptr;
    public:
        NodeController(PObject graphics_arg = nullptr,
                       PObject node_arg = nullptr){
            node = new NodeType(node_arg);
            node_graphics = new GraphicsType(graphics_arg);
        }
        Node* GetNode(){
            return node;
        }

        NodeGraphics* GetNodeGraphics(){
            return node_graphics;
        }

    };

    class BindingHelper{
    public:
        //////////////////////////////// TextEdit ////////////////////////////////
        BindingHelper& BindFromTo(TextEditProxy* proxy, Port* port){
            proxy->AddValueListener([=](PObject value){
                if(port->IsBusy())return;
                auto str = static_cast<QString*>(value)->toStdString();
                port->UpdateData(&str);
            });
            return *this;
        }

        BindingHelper& BindFromTo(Port* port, TextEditProxy* proxy){
            port->AddUpdateDataListener([=](PObject data){
                if(proxy->IsBusy())return;
                proxy->GetWidget<TextEdit>()->setText(QString(static_cast<string*>(data)->c_str()));
            });
            return *this;
        }

        //////////////////////////////// TextEdit ////////////////////////////////
        BindingHelper& BindFromTo(LineEditProxy* proxy, Port* port){
            proxy->AddValueListener([=](PObject value){
                if(port->IsBusy())return;
                auto str = static_cast<QString*>(value)->toStdString();
                port->UpdateData(&str);
            });
            return *this;
        }

        BindingHelper& BindFromTo(Port* port, LineEditProxy* proxy){
            port->AddUpdateDataListener([=](PObject data){
                if(proxy->IsBusy())return;
                proxy->GetWidget<LineEdit>()->setText(QString(static_cast<string*>(data)->c_str()));
            });
            return *this;
        }

        //////////////////////////////// Int64SpinBox ////////////////////////////////
        BindingHelper& BindFromTo(Int64SpinBoxProxy* proxy, Port* port){
            proxy->AddValueListener([=](PObject value){
                if(port->IsBusy())return;
                port->UpdateData(value);
            });
            return *this;
        }

        BindingHelper& BindFromTo(Port* port, Int64SpinBoxProxy* proxy){
            port->AddUpdateDataListener([=](PObject value){
                if(proxy->IsBusy())return;
                long long v = *static_cast<long long*>(value);
                proxy->GetWidget<Int64SpinBox>()->SetValue(*static_cast<long long*>(value));
            });
            return *this;
        }

        //////////////////////////////// Int32SpinBox ////////////////////////////////
        BindingHelper& BindFromTo(Int32SpinBoxProxy* proxy, Port* port){
            proxy->AddValueListener([=](PObject value){
                if(port->IsBusy())return;
                port->UpdateData(value);
            });
            return *this;
        }

        BindingHelper& BindFromTo(Port* port, Int32SpinBoxProxy* proxy){
            port->AddUpdateDataListener([=](PObject value){
                if(proxy->IsBusy())return;
                proxy->GetWidget<Int32SpinBox>()->SetValue(*static_cast<int*>(value));
            });
            return *this;
        }

        //////////////////////////////// FileBox ////////////////////////////////
        BindingHelper& BindFromTo(FileBoxProxy* proxy, Port* port){
            proxy->AddValueListener([=](PObject value){
                if(port->IsBusy())return;
                auto str = static_cast<QString*>(value)->toLocal8Bit().toStdString();
                port->UpdateData(&str);
            });
            return *this;
        }

        BindingHelper& BindFromTo(Port* port, FileBoxProxy* proxy){
            port->AddUpdateDataListener([=](PObject value){
                if(proxy->IsBusy())return;
                proxy->GetWidget<FileBox>()->setText(QString(static_cast<string*>(value)->c_str()));
            });
            return *this;
        }

        //////////////////////////////// ComboBox ////////////////////////////////
        BindingHelper& BindFromTo(ComboBoxProxy* proxy, Port* port){
            proxy->AddValueListener([=](PObject value){
                if(port->IsBusy())return;
                port->UpdateData(value);
            });
            return *this;
        }

        BindingHelper& BindFromTo(Port* port, ComboBoxProxy* proxy){
            port->AddUpdateDataListener([=](PObject data){
                if(proxy->IsBusy())return;
                int index = *(int*)data;
                auto combo_box = proxy->GetWidget<QComboBox>();
                index = qBound(0, index, combo_box->count() - 1);
                combo_box->setCurrentIndex(index);
            });
            return *this;
        }

        /****************************** Bind ******************************/
        template<typename ProxyType, typename PortType>
        BindingHelper& Bind(ProxyType* proxy, PortType* port){
            return this->BindFromTo(proxy, port)
                    .BindFromTo(port, proxy);
        }
    };
}
