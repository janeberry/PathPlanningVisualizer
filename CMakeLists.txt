cmake_minimum_required(VERSION 3.16...4.0)
project(PathplanningVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(PathplanningVisualizer
    main.cpp
    mainwindow.cpp
    mainwindow.h
    grid/cell.cpp
    grid/cell.h
    toolbar/toolbar.cpp
    toolbar/toolbar.h
    toolbar/placingmode.h
    algorithms/bfs.cpp
    algorithms/bfs.h
)

target_link_libraries(PathplanningVisualizer
    Qt6::Core
    Qt6::Widgets
)