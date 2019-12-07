#pragma once
#include"../../../core/view/connection_graphics.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../view/op_node_graphics.hpp"
#include"../view/histogram_value_node_graphics.hpp"
#include"Noder/src/applications/mather/value_node.hpp"
namespace Mather {
    class HistogramValueNodeController: public NoderGraphics::NodeController<HistogramNode, HistogramValueNodeGraphics>{
    private:
        using Node = Noder::Node;
        using NodeGraphics = NoderGraphics::NodeGraphics;

        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        HistogramValueNodeController(PObject graphics_arg = nullptr,
                                     PObject node_arg = nullptr)
            :NoderGraphics::NodeController<HistogramNode, HistogramValueNodeGraphics>(graphics_arg, node_arg){
            auto value_graphics = this->node_graphics;
            auto value_node = this->node;
            value_node->GetInputPort()->FlushData(Pointer<Data>(new VectorData<int>()));
            value_node->GetOutputPort()->FlushData(Pointer<Data>(new VectorData<int>()));
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort(), value_graphics->GetUI<PortProxy>(HistogramValueNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort(), value_graphics->GetUI<PortProxy>(HistogramValueNodeGraphics::OUTPUT_PORT));
            auto histogram_proxy = value_graphics->GetUI<HistogramProxy>(HistogramValueNodeGraphics::HISTOGRAM_VIEW);
            auto histogram_view = histogram_proxy->GetWidget<HistogramView>();
            value_node->GetInputPort()->AddUpdateDataListener([=](PObject data){
                if(this->IsBusy())return;
                this->SetBusy(true);
                printf("before set data\n");
                histogram_view->SetData(*static_cast<std::vector<int>*>(data));
                histogram_proxy->setWidget(nullptr);
                histogram_proxy->setWidget(histogram_view);
                printf("end set data\n");
                this->SetBusy(false);
            });
        }
    };
}
