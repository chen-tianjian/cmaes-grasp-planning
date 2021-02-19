cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(cmaes_grasp_planning_test)

find_package(GTest REQUIRED)
find_package (Eigen3 REQUIRED NO_MODULE)
find_package(Qt4 REQUIRED QtCore QtGui Qt3Support)
include(${QT_USE_FILE})

# QT4_WRAP_UI(UISrcs_me 
#   ${CMAKE_SOURCE_DIR}/ui/dialog.ui
# )
# QT4_WRAP_CPP(MOCSrcs_me
#   ${CMAKE_SOURCE_DIR}/include/cmaes_grasp_planning/dialog.h
# )

# file(GLOB SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB TEST_SRC "${CMAKE_SOURCE_DIR}/tests/*.cpp")
file(GLOB TINYXML_SRC "$ENV{GRASPIT}/tinyxml/*.cpp")

add_executable(run_all_tests ${TEST_SRC} ${TINYXML_SRC})

target_include_directories(run_all_tests PUBLIC
    ${GTEST_INCLUDE_DIRS}
    ${QT_INCLUDES}
    ${CMAKE_SOURCE_DIR}/dependencies/libcmaes/include/libcmaes
    # ${CMAKE_SOURCE_DIR}/include
    $ENV{GRASPIT}/include
    $ENV{GRASPIT}/tinyxml
    ${PROJECT_BINARY_DIR}
    )

target_link_libraries(run_all_tests ${GTEST_LIBRARIES} ${QT_LIBRARIES} ${EIGEN_LIBRARIES} cmaes pthread )

enable_testing()
add_test(NAME run_all_tests COMMAND run_all_tests)