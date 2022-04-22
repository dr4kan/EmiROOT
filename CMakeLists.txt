cmake_minimum_required(VERSION 3.9)
project(EmiROOT VERSION 1.0.1 DESCRIPTION "EmiROOT: Evolutionary minimizer for ROOT")
include(GNUInstallDirs)

find_package(ROOT)

include_directories(include)
set(CMAKE_CXX_FLAGS "-std=c++17 -Werror -g -O3")

# list of source files
file(GLOB_RECURSE EmiROOT_SRC ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB EmiROOT_SRC_ROOT ${PROJECT_SOURCE_DIR}/ROOT/*.cc)

# list of headers
file(GLOB_RECURSE EmiROOT_INCLUDE ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE EmiROOT_INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/ROOT/*.h)

if(ROOT_FOUND)
  ###########################################
  #### Compile EmiROOT with ROOT support ####
  ###########################################
  message(STATUS "EmiROOT will be compiled with ROOT support")
  add_library(EmiROOT SHARED ${EmiROOT_SRC} ${EmiROOT_SRC_ROOT})
  include(${ROOT_USE_FILE})
  target_link_libraries(EmiROOT ${ROOT_LIBRARIES})
  set_target_properties(
      EmiROOT PROPERTIES
      PUBLIC_HEADER "${EmiROOT_INCLUDE};${EmiROOT_INCLUDE_ROOT}"
  )
else()
  ##############################################
  #### Compile EmiROOT without ROOT support ####
  ##############################################
  message(WARNING "EmiROOT will be compiled without ROOT support")
  add_library(EmiROOT SHARED ${EmiROOT_SRC})
  set_target_properties(
      EmiROOT PROPERTIES
      PUBLIC_HEADER "${EmiROOT_INCLUDE}"
  )
endif()

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
