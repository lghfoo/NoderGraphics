#pragma once
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../view/node_graphicses.hpp"
#include"Noder/src/applications/filer/nodes.hpp"
namespace Filer {
    using namespace NoderGraphics;
    class FilelenNodeController : public NodeController{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        FilelenNodeController(Noder::Node* node,
                                 NoderGraphics::NodeGraphics* graphics)
                                :NoderGraphics::NodeController(node, graphics){
            auto filelen_graphics = dynamic_cast<FilelenNodeGraphics*>(graphics);
            if(!filelen_graphics)return;
            auto filelen_node = dynamic_cast<FilelenNode*>(node);
            if(!filelen_node)return;
            // todo: use shared_ptr?
            input_port_controller = new PortController(filelen_node->GetInputPort(FilelenNode::FILENAME_INPUT).get(), filelen_graphics->GetUI<PortProxy>(FilelenNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(filelen_node->GetOutputPort(FilelenNode::FILELEN_OUTPUT).get(), filelen_graphics->GetUI<PortProxy>(FilelenNodeGraphics::OUTPUT_PORT));
            auto text_graphics = filelen_graphics->GetUI<FileBoxProxy>(FilelenNodeGraphics::FILE_BOX);
            QObject::connect(text_graphics->GetWidget<QLineEdit>(), &QLineEdit::textChanged, [=](const QString& text){
                if(this->IsBusy())return;
                this->SetBusy(true);
                auto str = text.toLocal8Bit().toStdString();
                filelen_node->GetInputPort(FilelenNode::FILENAME_INPUT)->UpdateData(&str);
                this->SetBusy(false);
            });

            filelen_node->GetInputPort(FilelenNode::FILENAME_INPUT)->AddUpdateDataListener([=](PObject data){
                if(this->IsBusy())return;
                this->SetBusy(true);
                auto text_edit = text_graphics->GetWidget<QLineEdit>();
                auto str = *static_cast<string*>(data);
                text_edit->setText(QString(str.c_str()));
                this->SetBusy(false);
            });
        }
    };

    class PickBufferFromFileNodeController : public NodeController{
    public:
        PickBufferFromFileNodeController(Noder::Node* node,
                                 NoderGraphics::NodeGraphics* graphics)
                                :NoderGraphics::NodeController(node, graphics){
            printf("BEFORE CREATE PBFF CONTROLLER\n");
            auto pick_node = dynamic_cast<PickBufferFromFileNode*>(node);
            if(!pick_node)return;
            auto pick_graphics = dynamic_cast<PickBufferFromFileNodeGraphics*>(graphics);
            if(!pick_graphics)return;
            printf("END CREATE PBFF CONTROLLER\n");
        }
    };

    class PickNumberFromBufferNodeController : public NodeController{
    public:
        PickNumberFromBufferNodeController(Noder::Node* node,
                                 NoderGraphics::NodeGraphics* graphics)
                                :NoderGraphics::NodeController(node, graphics){
            printf("BEFORE CREATE PNFB CONTROLLER\n");
            auto pick_node = dynamic_cast<PickNumberFromBufferNode*>(node);
            if(!pick_node)return;
            auto pick_graphics = dynamic_cast<PickNumberFromBufferNodeGraphics*>(graphics);
            if(!pick_graphics)return;
#define PNFBN PickNumberFromBufferNode
#define PNFBG PickNumberFromBufferNodeGraphics
            {
                auto number_type_proxy = pick_graphics->GetUI<ComboBoxProxy>(PNFBG::NUMBER_TYPE_BOX);
                auto number_type_box = number_type_proxy->GetWidget<QComboBox>();
                QMap<Mather::NumberType, const char*>& number_type_map = GetNumberTypeMap();
                QMapIterator<Mather::NumberType, const char*> i(number_type_map);
                while (i.hasNext()) {
                    i.next();
                    number_type_box->insertItem(i.key(), i.value());
                }
            }
            {
                auto format_type_proxy = pick_graphics->GetUI<ComboBoxProxy>(PNFBG::FORMAT_TYPE_BOX);
                auto format_type_box = format_type_proxy->GetWidget<QComboBox>();
                QMap<BufferInputStream::Mode, const char*>& format_type_map = GetFormatTypeMap();
                QMapIterator<BufferInputStream::Mode, const char*> i(format_type_map);
                while (i.hasNext()) {
                    i.next();
                    format_type_box->insertItem(i.key(), i.value());
                }
            }
            {
                auto endian_type_proxy = pick_graphics->GetUI<ComboBoxProxy>(PNFBG::ENDIAN_TYPE_BOX);
                auto endian_type_box = endian_type_proxy->GetWidget<QComboBox>();
                QMap<BufferInputStream::Endian, const char*>& endian_type_map = GetEndianTypeMap();
                QMapIterator<BufferInputStream::Endian, const char*> i(endian_type_map);
                while (i.hasNext()) {
                    i.next();
                    endian_type_box->insertItem(i.key(), i.value());
                }
            }
#undef PNFBN
#undef PNFBG
            printf("END CREATE PNFB CONTROLLER\n");

        }
        static QMap<Mather::NumberType, const char*>& GetNumberTypeMap(){
            using NT = Mather::NumberType;
            static QMap<Mather::NumberType, const char*>number_type_map = {
                {NT::INT8, "int8"},
                {NT::UINT8, "uint8"},
                {NT::INT16, "int16"},
                {NT::UINT16, "uint16"},
                {NT::INT32, "int32"},
                {NT::UINT32, "uint32"},
                {NT::INT64, "int64"},
                {NT::UINT64, "uint64"},
                {NT::FLOAT32, "float32"},
                {NT::FLOAT64, "float64"}
            };
            return number_type_map;
        }
        static QMap<BufferInputStream::Mode, const char*>& GetFormatTypeMap(){
            using Mode = BufferInputStream::Mode;
            static QMap<Mode, const char*>format_type_map = {
                {Mode::Binary, "binary"},
                {Mode::Text, "text"},
            };
            return format_type_map;
        }
        static QMap<BufferInputStream::Endian, const char*>& GetEndianTypeMap(){
            using Endian = BufferInputStream::Endian;
            static QMap<Endian, const char*>endian_type_map = {
                {Endian::LittleEndian, "little endian"},
                {Endian::BigEndian, "big endian"},
            };
            return endian_type_map;
        }
    };
}
