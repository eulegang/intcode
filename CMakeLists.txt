cmake_minimum_required(VERSION 3.10)
project(intcode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_library(intcode STATIC src/intcode/lib.cxx)
add_executable(day2a src/day2/main.a.cxx)

target_link_libraries(day2a PRIVATE intcode)

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
