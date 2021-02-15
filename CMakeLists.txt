cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(cmaes_grasp_planning)

option(BUILD_TESTS "Build tests" ON)
option(DEBUG "Build in debug mode to use gdb" OFF)



if(DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
endif(DEBUG)

add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/libcmaes)

if(BUILD_TESTS)
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif(BUILD_TESTS)



FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui Qt3Support)
INCLUDE(${QT_USE_FILE})

QT4_WRAP_UI(UISrcs_me 
  ui/cmaes_grasp_planning_dialog.ui
)
QT4_WRAP_CPP(MOCSrcs_me
  include/cmaes_grasp_planning/cmaes_grasp_planning_dialog.h
)

include_directories(
  include
  $ENV{GRASPIT}
  $ENV{GRASPIT}/include
  ${PROJECT_BINARY_DIR}
)

add_library(cmaesgraspplanning SHARED 
  src/cmaes_grasp_planning_dialog.cc 
  src/cmaes_grasp_planning_plugin.cc 
  ${MOCSrcs_me} ${UISrcs_me})

