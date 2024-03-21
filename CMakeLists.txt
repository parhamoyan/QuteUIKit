cmake_minimum_required(VERSION 3.24)
project(QuteUIKit)


add_subdirectory(${CMAKE_SOURCE_DIR}/App/)
add_subdirectory(${CMAKE_SOURCE_DIR}/UIKit/)


file( GLOB QML_DIRS LIST_DIRECTORIES true "${CMAKE_BINARY_DIR}/qml/*" )
set( QML_IMPORT_PATH "${QML_DIRS}" CACHE STRING "My extra qml import paths" FORCE )
