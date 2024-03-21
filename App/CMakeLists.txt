cmake_minimum_required(VERSION 3.24)

project(App)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOGEN_PARALLEL AUTO)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt6 REQUIRED COMPONENTS Core Quick)

set(QT_LIBS Qt::Core Qt::Quick)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    qml.qrc
)

target_link_libraries(${PROJECT_NAME} ${QT_LIBS} QuteUIKit)
