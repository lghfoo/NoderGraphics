#pragma once
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/port_controller.hpp"
#include"../view/node_graphicses.hpp"
#include"Noder/src/applications/filer/nodes.hpp"
namespace Filer {
    using namespace NoderGraphics;
    class FilelenNodeController : public NodeController<FilelenNode, FilelenNodeGraphics>{
        PortController* input_port_controller = nullptr;
        PortController* output_port_controller = nullptr;
    public:
        FilelenNodeController(PObject graphics_arg = nullptr,
                              PObject node_arg = nullptr)
            :NodeController<FilelenNode, FilelenNodeGraphics> (graphics_arg, node_arg){
            this->node_graphics = new FilelenNodeGraphics;
            this->node = new FilelenNode;
            auto filelen_node = static_cast<FilelenNode*>(this->node);
            auto filelen_graphics = static_cast<FilelenNodeGraphics*>(this->node_graphics);
            // todo: use shared_ptr?
            input_port_controller = new PortController(filelen_node->GetInputPort(FilelenNode::FILENAME_INPUT), filelen_graphics->GetUI<PortProxy>(FilelenNodeGraphics::INPUT_PORT));
            output_port_controller = new PortController(filelen_node->GetOutputPort(FilelenNode::FILELEN_OUTPUT), filelen_graphics->GetUI<PortProxy>(FilelenNodeGraphics::OUTPUT_PORT));
            auto text_graphics = filelen_graphics->GetUI<FileBoxProxy>(FilelenNodeGraphics::FILE_BOX);
            BindingHelper().Bind(text_graphics,
                                 filelen_node->GetInputPort(FilelenNode::FILENAME_INPUT));
        }
    };

    class PickBufferFromFileNodeController : public NodeController<PickBufferFromFileNode, PickBufferFromFileNodeGraphics>{
    public:
        PickBufferFromFileNodeController(PObject graphics_arg = nullptr,
                                         PObject node_arg = nullptr)
            :NodeController<PickBufferFromFileNode, PickBufferFromFileNodeGraphics> (graphics_arg, node_arg){
            printf("BEFORE CREATE PBFF CONTROLLER\n");
            BindingHelper binding_helper;
#define PBFFN PickBufferFromFileNode
#define PBFFG PickBufferFromFileNodeGraphics
            {
                auto file_name_port_proxy = node_graphics->GetUI<PortProxy>(PBFFG::FILE_INPUT_PORT);
                auto file_name_box_proxy = node_graphics->GetUI<FileBoxProxy>(PBFFG::FILE_BOX);
                auto file_name_port = node->GetInputPort(PBFFN::FILENAME_INPUT);
                auto file_name_port_controller = new PortController(file_name_port, file_name_port_proxy);
                binding_helper.Bind(file_name_box_proxy, file_name_port);
            }
            {
                auto begin_addr_port_proxy = node_graphics->GetUI<PortProxy>(PBFFG::BEGIN_ADDRESS_INPUT_PORT);
                auto begin_addr_port = node->GetInputPort(PBFFN::BEGIN_ADDRESS_INPUT);
                auto begin_addr_box_proxy = node_graphics->GetUI<Int64SpinBoxProxy>(PBFFG::BEGIN_ADDRESS_BOX);
                auto begin_addr_port_controller = new PortController(begin_addr_port, begin_addr_port_proxy);
                binding_helper.Bind(begin_addr_box_proxy, begin_addr_port);
            }
            {
                auto size_port_proxy = node_graphics->GetUI<PortProxy>(PBFFG::BUFFER_SIZE_INPUT_PORT);
                auto size_port = node->GetInputPort(PBFFN::BUFFER_SIZE_INPUT);
                auto size_box_proxy = node_graphics->GetUI<Int64SpinBoxProxy>(PBFFG::BUFFER_SIZE_BOX);
                auto size_port_controller = new PortController(size_port, size_port_proxy);
                binding_helper.Bind(size_box_proxy, size_port);
            }
            {
                auto end_addr_port_proxy = node_graphics->GetUI<PortProxy>(PBFFG::END_ADDRESS_OUTPUT_PORT);
                auto end_addr_port = node->GetOutputPort(PBFFN::END_ADDRESS_OUTPUT);
                auto end_addr_port_controller = new PortController(end_addr_port, end_addr_port_proxy);
            }
            {
                auto buffer_out_port_proxy = node_graphics->GetUI<PortProxy>(PBFFG::BUFFER_OUTPUT_PORT);
                auto buffer_out_port = node->GetOutputPort(PBFFN::BUFFER_OUTPUT);
                auto buffer_out_port_controller = new PortController(buffer_out_port, buffer_out_port_proxy);
            }
#undef PBFFN
#undef PBFFG
            printf("END CREATE PBFF CONTROLLER\n");
        }
    };

    class PickNumberFromBufferNodeController
            : public NodeController<PickNumberFromBufferNode, PickNumberFromBufferNodeGraphics>{
    public:
        PickNumberFromBufferNodeController(PObject graphics_arg = nullptr,
                                           PObject node_arg = nullptr)
            :NodeController<PickNumberFromBufferNode, PickNumberFromBufferNodeGraphics>(graphics_arg, node_arg){
            printf("BEFORE CREATE PNFB CONTROLLER\n");
            auto pick_node = this->node;
            auto pick_graphics = this->node_graphics;
#define PNFBN PickNumberFromBufferNode
#define PNFBG PickNumberFromBufferNodeGraphics
            BindingHelper binding_helper;
            {
                auto buffer_port_proxy = pick_graphics->GetUI<PortProxy>(PNFBG::BUFFER_INPUT_PORT);
                auto buffer_port = node->GetInputPort(PNFBN::BUFFER_INPUT);
                auto buffer_port_controller = new PortController(buffer_port, buffer_port_proxy);
            }
            {
                auto begin_addr_port_proxy = node_graphics->GetUI<PortProxy>(PNFBG::BEGIN_ADDRESS_PORT);
                auto begin_addr_port = node->GetInputPort(PNFBN::BEGIN_ADDRESS_INPUT);
                auto begin_addr_box_proxy = node_graphics->GetUI<Int64SpinBoxProxy>(PNFBG::BEGIN_ADDRESS_BOX);
                auto begin_addr_port_controller = new PortController(begin_addr_port, begin_addr_port_proxy);
                binding_helper.Bind(begin_addr_box_proxy, begin_addr_port);
            }
            {
                auto end_addr_proxy = node_graphics->GetUI<PortProxy>(PNFBG::END_ADDRESS_OUTPUT_PORT);
                auto end_addr_port = node->GetOutputPort(PNFBN::END_ADDRESS_OUTPUT);
                auto end_addr_port_controller = new PortController(end_addr_port, end_addr_proxy);
            }
            {
                auto number_out_proxy = node_graphics->GetUI<PortProxy>(PNFBG::NUMBER_OUTPUT_PORT);
                auto number_out_port = node->GetOutputPort(PNFBN::NUMBER_OUTPUT);
                auto number_out_port_controller = new PortController(number_out_port, number_out_proxy);
            }
            {
                auto number_type_proxy = pick_graphics->GetUI<ComboBoxProxy>(PNFBG::NUMBER_TYPE_BOX);
                auto number_type_input = node->GetInputPort(PNFBN::NUMBER_TYPE_INPUT);
                auto number_type_box = number_type_proxy->GetWidget<QComboBox>();
                QMap<Mather::NumberType, const char*>& number_type_map = GetNumberTypeMap();
                QMapIterator<Mather::NumberType, const char*> i(number_type_map);
                while (i.hasNext()) {
                    i.next();
                    number_type_box->insertItem(i.key(), i.value());
                }
                PortController* NumberTypePortController = new PortController(
                            number_type_input,
                            node_graphics->GetUI<PortProxy>(PNFBG::NUMBER_TYPE_PORT)
                            );
                binding_helper.Bind(number_type_proxy, number_type_input);
            }
            {
                auto format_type_proxy = pick_graphics->GetUI<ComboBoxProxy>(PNFBG::FORMAT_TYPE_BOX);
                auto format_type_input = node->GetInputPort(PNFBN::FORMAT_INPUT);
                auto format_type_box = format_type_proxy->GetWidget<QComboBox>();
                QMap<BufferInputStream::Mode, const char*>& format_type_map = GetFormatTypeMap();
                QMapIterator<BufferInputStream::Mode, const char*> i(format_type_map);
                while (i.hasNext()) {
                    i.next();
                    format_type_box->insertItem(i.key(), i.value());
                }
                PortController* FormatTypeController = new PortController(
                            format_type_input,
                            node_graphics->GetUI<PortProxy>(PNFBG::FORMAT_TYPE_PORT)
                            );
                binding_helper.Bind(format_type_proxy, format_type_input);
            }
            {
                auto endian_type_proxy = pick_graphics->GetUI<ComboBoxProxy>(PNFBG::ENDIAN_TYPE_BOX);
                auto endian_type_input = node->GetInputPort(PNFBN::ENDIAN_INPUT);
                auto endian_type_box = endian_type_proxy->GetWidget<QComboBox>();
                QMap<BufferInputStream::Endian, const char*>& endian_type_map = GetEndianTypeMap();
                QMapIterator<BufferInputStream::Endian, const char*> i(endian_type_map);
                while (i.hasNext()) {
                    i.next();
                    endian_type_box->insertItem(i.key(), i.value());
                }
                PortController* FormatTypeController = new PortController(
                            endian_type_input,
                            node_graphics->GetUI<PortProxy>(PNFBG::ENDIAN_TYPE_PORT)
                            );
                binding_helper.Bind(endian_type_proxy, endian_type_input);
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
