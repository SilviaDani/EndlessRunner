# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(GoogleTests)
find_package(GTest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/cmake-build-debug)

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(runAllTests main.cpp test1.cpp)
target_link_libraries(runAllTests gtest  gtest_main core)