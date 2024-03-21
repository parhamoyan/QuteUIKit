cmake_minimum_required(VERSION 3.23.0)
project(QuteUIKit VERSION 0.1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_library(QuteUIKit STATIC)
qt_add_qml_module(QuteUIKit
    URI "QuteUIKit"
    VERSION 1.0
    SOURCES
        qutecheckbox.h qutecheckbox.cpp trimmablepainterpath.h trimmablepainterpath.cpp
)


target_compile_definitions(QuteUIKit
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(QuteUIKit PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

target_include_directories(QuteUIKit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
