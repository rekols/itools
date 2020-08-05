cmake_minimum_required(VERSION 3.5)
project(itools)

set(TARGET itools)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    src/sidebar.h
    src/sidebar.cpp
)

set(RESOURCES "")

set(QT Core Gui Widgets DBus X11Extras)
find_package(Qt5 REQUIRED ${QT})

add_executable(${TARGET} ${SRCS} ${RESOURCES})
target_link_libraries(${TARGET}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::DBus
        Qt5::X11Extras
)

install(TARGETS ${TARGET} DESTINATION /usr/bin)
