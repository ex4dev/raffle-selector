cmake_minimum_required(VERSION 3.28)
project(Raffle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        REQUIRED)

add_executable(Raffle src/main.cpp
        src/ui/mainwindow.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.ui
        src/datastorage.cpp
        src/datastorage.h)
target_link_libraries(Raffle
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
)

