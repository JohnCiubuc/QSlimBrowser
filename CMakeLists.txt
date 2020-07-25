project(QSlimBrowser) 

set(CMAKE_CXX_STANDARD 11) 
cmake_minimum_required(VERSION 3.18)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5WebEngineWidgets REQUIRED)
find_package(Qt5WebKitWidgets REQUIRED)

set(SOURCES
    main.cpp
    loginparser.cpp
    mainwindow.cpp
    scriptparser.cpp
    userstyleparser.cpp
)
set(HEADERS
    loginparser.h
    mainwindow.h
    scriptparser.h
    userstyleparser.h
)
set(UI mainwindow.ui)

file(COPY Scripts DESTINATION .)
file(COPY Userstyles DESTINATION .)

add_executable(QSlimBrowser ${SOURCES} ${HEADERS} ${UI})
target_link_libraries(QSlimBrowser Qt5::Widgets Qt5::WebEngineWidgets Qt5::WebKitWidgets)
