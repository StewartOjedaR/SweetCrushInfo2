cmake_minimum_required(VERSION 3.16)

project(SweetCrush LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SweetCrush main.cpp
    funciones.h)

include(GNUInstallDirs)
install(TARGETS SweetCrush
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
