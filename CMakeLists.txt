cmake_minimum_required(VERSION 3.9)
project(EmiROOT VERSION 1.0.1 DESCRIPTION "EmiROOT description")
include(GNUInstallDirs)

include_directories(include)

# ls -1 src/*.cc
add_library(EmiROOT SHARED
src/Random.cc
)
set_target_properties(
        EmiROOT PROPERTIES
        PUBLIC_HEADER
include/Random.h
)

configure_file(EmiROOT.pc.in EmiROOT.pc @ONLY)
target_include_directories(EmiROOT PRIVATE .)

install(
    TARGETS EmiROOT
    EXPORT EmiROOTTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/EmiROOT
)

install(
    FILES ${CMAKE_BINARY_DIR}/EmiROOT.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)

install(
    EXPORT EmiROOTTargets
    FILE EmiROOTTargets.cmake
    DESTINATION "${CMAKE_INSTALL_DATADIR}/EmiROOT/cmake"
    NAMESPACE EmiROOT::
)
