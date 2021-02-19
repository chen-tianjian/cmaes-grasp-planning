cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(cmaes_grasp_planning)

option(build_tests "Build tests" OFF)
option(debug "Build in debug mode to use gdb" OFF)



if(debug)
    set(CMAKE_BUILD_TYPE debug)
endif(debug)

add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/libcmaes)

if(build_tests)
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif(build_tests)



FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui Qt3Support)
INCLUDE(${QT_USE_FILE})

QT4_WRAP_UI(UISrcs_me 
  ${CMAKE_SOURCE_DIR}/ui/dialog.ui
)
QT4_WRAP_CPP(MOCSrcs_me
  ${CMAKE_SOURCE_DIR}/include/cmaes_grasp_planning/dialog.h
)

file(GLOB SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB TINYXML_SRC "$ENV{GRASPIT}/tinyxml/*.cpp")

add_library(cmaesgraspplanning SHARED 
  ${SRC} ${TINYXML_SRC} ${MOCSrcs_me} ${UISrcs_me})

target_include_directories(cmaesgraspplanning PUBLIC
  ${QT_INCLUDES}
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/dependencies/libcmaes/include/libcmaes
  $ENV{GRASPIT}/include
  $ENV{GRASPIT}/tinyxml
  ${PROJECT_BINARY_DIR}
  )

target_link_libraries(cmaesgraspplanning ${EIGEN_LIBRARIES} ${QT_LIBRARIES} cmaes pthread )
