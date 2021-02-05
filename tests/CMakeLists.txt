cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(cmaes_grasp_planning_test)

find_package(GTest REQUIRED)

file(GLOB TEST_SRC "*.cc")
add_executable(run_all_tests ${TEST_SRC})

target_include_directories(run_all_tests PUBLIC
    ${GTEST_INCLUDE_DIRS}
    )

target_link_libraries(run_all_tests ${GTEST_LIBRARIES} pthread)

enable_testing()
add_test(NAME run_all_tests COMMAND run_all_tests)