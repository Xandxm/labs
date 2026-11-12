
cmake_minimum_required(VERSION 3.16)

project(Lab4Variant2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 5.14 REQUIRED COMPONENTS Widgets)

add_executable(Lab4Variant2
    main.cpp
    graph_core.h
)

target_link_libraries(Lab4Variant2 PRIVATE Qt5::Widgets)

configure_file(map.png map.png COPYONLY)
