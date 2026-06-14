cmake_minimum_required(VERSION 3.16...4.0)
project(PathplanningVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt path
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(PathplanningVisualizer
    main.cpp
)

target_link_libraries(PathplanningVisualizer
    Qt6::Core
    Qt6::Widgets
)