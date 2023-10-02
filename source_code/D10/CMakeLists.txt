cmake_minimum_required(VERSION 3.21)
project(D10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

qt_add_executable(D10
    main.cpp
)

target_link_libraries(D10 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
