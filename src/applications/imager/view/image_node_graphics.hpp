#pragma once
#include"../../../core/view/node_graphics.hpp"
#include"../../../controls/custom_label.hpp"
#include"../../../controls/file_box.hpp"
#include"../../../controls/image_view.hpp"
#include"../../../core/view/port_view.hpp"
namespace Imager {
    using namespace NoderGraphics;
    class ImageNodeGraphics : public NodeGraphics{
    public:
        enum {NAME_LABEL, INPUT_PORT, IMAGE_VIEW, OUTPUT_PORT, UI_COUNT};
        ImageNodeGraphics(PObject arg = nullptr){
            this->setLayout(NodeLayoutBuilder(&(this->uis), UI_COUNT)
                            .Add(NAME_LABEL, new LabelProxy("Image"), 0, 0, 1, 3).NextRow()
                            .Add(INPUT_PORT, new PortProxy).Add(IMAGE_VIEW, new ImageViewProxy).Add(OUTPUT_PORT, new PortProxy)
                            .Layout());
            auto layout = static_cast<QGraphicsGridLayout*>(this->layout());
            auto label_proxy = this->GetUI<LabelProxy>(NAME_LABEL);
            auto label = label_proxy->GetWidget<Label>();
//            printf("label height: %d %d %d\n", label->minimumHeight(), label->maximumHeight(), label->sizeHint().height());
            layout->setRowFixedHeight(0, label->sizeHint().height());
            auto image_view_proxy = this->GetUI<ImageViewProxy>(IMAGE_VIEW);
            auto image_view = image_view_proxy->GetWidget<ImageView>();
            auto input_port_proxy = this->GetUI<PortProxy>(INPUT_PORT);
            auto input_port = input_port_proxy->GetWidget<PortWidget>();
            auto output_port_proxy = this->GetUI<PortProxy>(OUTPUT_PORT);
            auto output_port = output_port_proxy->GetWidget<PortWidget>();
            image_view->SetResizeListener([=](int w, int h){
                image_view_proxy->setWidget(nullptr);
                image_view_proxy->setWidget(image_view);
                this->scene()->update(this->mapToScene(this->boundingRect()).boundingRect());
            });
        }
    };
}
