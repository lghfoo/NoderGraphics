#pragma once
#include"Noder/src/core/noder/node.hpp"

#include"Noder/src/applications/imager/binaryzation/bernsen_node.hpp"

#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../view/bernsen_node_graphics.hpp"
namespace Imager {
    using namespace NoderGraphics;
    using namespace Noder;
    class BernsenNodeController : public NodeController<BernsenNode, BernsenNodeGraphics>{
        PortController* input_port_1_controller = nullptr;
        PortController* input_port_2_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        BernsenNodeController(PObject graphics_arg = nullptr,
                              PObject node_arg = nullptr)
            :NodeController<BernsenNode, BernsenNodeGraphics>(graphics_arg, node_arg){
            auto value_graphics = this->node_graphics;
            auto value_node = this->node;
            value_node->GetInputPort1()->FlushData(new ImageData);
            value_node->GetInputPort2()->FlushData(new Mather::Number<long long>());
            value_node->GetOutputPort()->FlushData(new ImageData);
//            // todo: use shared_ptr?
            input_port_1_controller = new PortController(value_node->GetInputPort1().get(), value_graphics->GetUI<PortProxy>(BernsenNodeGraphics::INPUT_IMAGE_PORT));
            input_port_2_controller = new PortController(value_node->GetInputPort2().get(), value_graphics->GetUI<PortProxy>(BernsenNodeGraphics::WINDOW_SIZE_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetUI<PortProxy>(BernsenNodeGraphics::OUTPUT_PORT));
            auto wind_size_proxy = value_graphics->GetUI<Int64SpinBoxProxy>(BernsenNodeGraphics::WINDOW_SIZE_BOX);
            auto wind_size_box = wind_size_proxy->GetWidget<Int64SpinBox>();
            QObject::connect(wind_size_box, &Int64SpinBox::ValueChanged, [=](long long value){
                if(this->IsBusy())return;
                this->SetBusy(true);
                value_node->GetInputPort2()->UpdateData(&value);
                this->SetBusy(false);
            });

            value_node->GetInputPort2()->AddUpdateDataListener([=](PObject data){
                if(this->IsBusy())return;
                this->SetBusy(true);
                wind_size_box->SetValue(*static_cast<long long*>(data));
                this->SetBusy(false);
            });
        }
    };
}
