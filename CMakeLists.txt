cmake_minimum_required(VERSION 3.9)
project(EmiROOT VERSION 1.0.1 DESCRIPTION "EmiROOT: Evolutionary minimizer for ROOT")
include(GNUInstallDirs)

include_directories(include)
set(CMAKE_CXX_FLAGS "-std=c++17 -Werror -g -O3")

# ls -1 src/*.cc
# list of headers
file(GLOB EmiROOT_SRC ${PROJECT_SOURCE_DIR}/src/*.cc)
add_library(EmiROOT SHARED ${EmiROOT_SRC})

# list of headers
file(GLOB EmiROOT_INCLUDE ${PROJECT_SOURCE_DIR}/include/*.h)

set_target_properties(
    EmiROOT PROPERTIES
    PUBLIC_HEADER "${EmiROOT_INCLUDE}"
)

configure_file(macros/EmiROOT.pc.in EmiROOT.pc @ONLY)
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
