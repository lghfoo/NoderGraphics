#pragma once
#include"../../../core/view/connection_graphics.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../view/op_node_graphics.hpp"
#include"../view/histogram_value_node_graphics.hpp"
#include"Noder/src/applications/mather/value_node.hpp"
namespace Mather {
    class HistogramValueNodeController: public NoderGraphics::NodeController{
    private:
        using Node = Noder::Node;
        using NodeGraphics = NoderGraphics::NodeGraphics;
        using NodeController = NoderGraphics::NodeController;

        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        HistogramValueNodeController(Node* node,
                             NodeGraphics* graphics)
                            :NodeController(node, graphics){
            auto value_graphics = dynamic_cast<HistogramValueNodeGraphics*>(graphics);
            if(!value_graphics)return;
            auto value_node = dynamic_cast<HistogramNode*>(node);
            if(!value_node)return;
            value_node->GetInputPort()->FlushData(new VectorData<int>());
            value_node->GetOutputPort()->FlushData(new VectorData<int>());
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort().get(), value_graphics->GetUI<PortProxy>(HistogramValueNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort().get(), value_graphics->GetUI<PortProxy>(HistogramValueNodeGraphics::OUTPUT_PORT));
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
