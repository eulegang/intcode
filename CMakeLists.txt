cmake_minimum_required(VERSION 3.10)
project(intcode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TRACE_OPERATIONS "Adding tracing for operations" OFF)

if(TRACE_OPERATIONS)
  add_definitions(-DTRACE_OPS)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/intcode/)

add_library(intcode STATIC src/intcode/prog.cpp src/intcode/interp.cpp)

add_executable(day2a src/day2/main.a.cpp)
target_link_libraries(day2a PRIVATE intcode)

add_executable(day2b src/day2/main.b.cpp)
target_link_libraries(day2b PRIVATE intcode)

enable_testing()

add_executable(
  tests
  tests/intcode.cpp
)
target_link_libraries(
  tests
  GTest::gtest_main
  intcode
)

include(GoogleTest)
gtest_discover_tests(tests)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/.build/_deps/googletest-src/googletest/include)
