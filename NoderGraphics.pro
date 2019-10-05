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

INCLUDEPATH += C:\Users\35974\source\repos\Noder\Noder\src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/applications/mather/controller/application_controller.hpp \
    src/applications/mather/controller/connection_controller.hpp \
    src/applications/mather/model/application.hpp \
    src/applications/mather/view/connection_graphics.hpp \
    src/applications/mather/view/main_view.hpp \
    src/applications/mather/view/op_node_graphics.hpp \
    src/applications/mather/view/value_node_graphics.hpp \
    src/controls/double_spin_box.hpp \
    src/controls/int64_spin_box.hpp \
    src/controls/port_widget.hpp \
    src/controls/spin_box_base.hpp \
    src/core/node_graphics_base.hpp


