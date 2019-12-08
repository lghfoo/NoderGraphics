#pragma once
#include"Noder/src/core/noder/node.hpp"
#include"Noder/src/applications/imager/image_node.hpp"
#include"../view/image_node_graphics.hpp"
#include"../view/ppm_fimage_node_graphics.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
namespace Imager {
    using namespace NoderGraphics;
    using namespace Noder;
    class ImageNodeController : public NodeController<ImageNode, ImageNodeGraphics>{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        ImageNodeController(PObject graphics_arg = nullptr,
                            PObject node_arg = nullptr)
            :NodeController<ImageNode, ImageNodeGraphics> (graphics_arg, node_arg){
            auto value_graphics = this->node_graphics;
            auto value_node = this->node;
            value_node->GetInputPort()->FlushData(Pointer<Data>(new ImageData));
            value_node->GetOutputPort()->FlushData(Pointer<Data>(new ImageData));
            // todo: use shared_ptr?
            input_port_controller = new PortController(value_node->GetInputPort(), value_graphics->GetUI<PortProxy>(ImageNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(value_node->GetOutputPort(), value_graphics->GetUI<PortProxy>(ImageNodeGraphics::OUTPUT_PORT));
            value_node->GetInputPort()->AddUpdateDataListener([=](PObject data){
               if(this->IsBusy())return;
               this->SetBusy(true);
               Image* p_image = static_cast<Image*>(data);
               if(p_image != nullptr){
                   auto image_view_proxy = value_graphics->GetUI<ImageViewProxy>(ImageNodeGraphics::IMAGE_VIEW);
                   auto image_view = image_view_proxy->GetWidget<ImageView>();
//                   printf("w: %d, h: %d\n", p_image->GetWidth(), p_image->GetHeight());
                   QImage image(p_image->GetWidth(), p_image->GetHeight(), QImage::Format_ARGB32);
                   for(int i = 0; i < image.width(); i++){
                       for(int j = 0; j < image.height(); j++){
                            auto pixel = p_image->GetPixel(i, j);
                            image.setPixelColor(i, j, QColor(pixel.GetRed(), pixel.GetGreen(), pixel.GetBlue(), pixel.GetAlpha()));
                       }
                   }
//                   image_view->setFixedSize(image.width(), image.height());
                   image_view->SetImage(image);
               }
               else{
               }

               this->SetBusy(false);
            });
//            auto text_graphics = value_graphics->GetUI<TextEditProxy>(TextValueNodeGraphics::TEXT_EDIT);
//            QObject::connect(text_graphics->GetWidget<QTextEdit>(), &QTextEdit::textChanged, [=](){
//                if(this->IsBusy())return;
//                this->SetBusy(true);
//                auto text = text_graphics->GetWidget<QTextEdit>()->toPlainText();
//                auto str = text.toStdString();
//                value_node->GetInputPort()->UpdateData(&str);
//                this->SetBusy(false);
//            });

//            value_node->GetInputPort()->AddUpdateDataListener([=](PObject data){
//                if(this->IsBusy())return;
//                this->SetBusy(true);
//                auto text_edit = text_graphics->GetWidget<QTextEdit>();
//                auto str = *static_cast<string*>(data);
//                text_edit->setText(QString(str.c_str()));
//                this->SetBusy(false);
//            });
        }
    };
}
