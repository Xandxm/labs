cmake_minimum_required(VERSION 3.10)
project(ClockLab)

set(CMAKE_CXX_STANDARD 11)   # используем C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Список всех исходных файлов (включая main)
set(SOURCES
    Battery.cpp
    Clock.cpp
    Workshop.cpp
    main.cpp
)

# Создаём исполняемый файл
add_executable(ClockApp ${SOURCES})

# Указываем, где искать заголовочные файлы (текущая директория)
target_include_directories(ClockApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})