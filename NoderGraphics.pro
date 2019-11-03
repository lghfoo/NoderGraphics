QT += gui widgets

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    test/main.cpp

INCLUDEPATH += C:\Users\35974\source\repos\Noder

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/applications/filer/controller/application_controller.hpp \
    src/applications/filer/controller/node_controller_factory.hpp \
    src/applications/filer/controller/select_file_node_controller.hpp \
    src/applications/filer/view/select_file_node_graphics.hpp \
    src/applications/imager/controller/application_controller.hpp \
    src/applications/imager/controller/binaryzation_bernsen_node_controller.hpp \
    src/applications/imager/controller/binaryzation_otsu_node_controller.hpp \
    src/applications/imager/controller/grayen_node_controller.hpp \
    src/applications/imager/controller/image_node_controller.hpp \
    src/applications/imager/controller/node_controller_factory.hpp \
    src/applications/imager/controller/ppm_fimage_node_controller.hpp \
    src/applications/imager/view/bernsen_node_graphics.hpp \
    src/applications/imager/view/grayen_node_graphics.hpp \
    src/applications/imager/view/image_node_graphics - 副本.hpp \
    src/applications/imager/view/image_node_graphics - 副本.hpp \
    src/applications/imager/view/image_node_graphics.hpp \
    src/applications/imager/view/ppm_fimage_node_graphics.hpp \
    src/applications/mather/controller/application_controller.hpp \
    src/applications/mather/controller/node_controller_factory.hpp \
    src/applications/mather/controller/op_node_controller.hpp \
    src/applications/mather/controller/value_node_controller.hpp \
    src/applications/mather/model/application.hpp \
    src/applications/mather/view/node_graphics_factory.hpp \
    src/applications/mather/view/op_node_graphics.hpp \
    src/applications/mather/view/value_node_graphics.hpp \
    src/applications/texter/controller/application_controller.hpp \
    src/applications/texter/controller/node_controller_factory.hpp \
    src/applications/texter/controller/text_value_node_controller.hpp \
    src/applications/texter/view/text_value_node_graphics.hpp \
    src/controls/custom_label.hpp \
    src/controls/custom_text_edit.hpp \
    src/controls/double_spin_box.hpp \
    src/controls/file_box.hpp \
    src/controls/image_view.hpp \
    src/controls/int64_spin_box.hpp \
    src/controls/spin_box_base.hpp \
    src/core/controller/application_controller.hpp \
    src/core/controller/connection_controller.hpp \
    src/core/controller/graphics_controller.hpp \
    src/core/controller/node_controller.hpp \
    src/core/controller/port_controller.hpp \
    src/core/view/connection_graphics.hpp \
    src/core/view/main_view.hpp \
    src/core/view/node_graphics.hpp \
    src/core/view/node_graphics_presets/node_graphics_presets.hpp \
    src/core/view/port_view.hpp

RESOURCES += \
    resources.qrc


