cmake_minimum_required(VERSION 3.0.0)
project(pathFinder VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

include(CTest)
enable_testing()

include_directories("include")

add_executable(pathFinder src/main.cpp src/Map.cpp src/Point.cpp src/Path.cpp src/CmdLineTool.cpp src/CmdLineTool.h)

# use Catch2 unit test suite
find_package(Catch2 3 REQUIRED)
add_executable(tests test/test.cpp src/Map.cpp src/Path.cpp src/Point.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
