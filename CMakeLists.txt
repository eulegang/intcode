cmake_minimum_required(VERSION 3.10)
project(intcode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/intcode/)

file(GLOB INTCODE_SRC "src/intcode/*.cpp")
add_library(libintcode STATIC ${INTCODE_SRC})

add_executable(intcode src/run/main.cpp)
target_link_libraries(intcode PRIVATE libintcode)

# TESTING

file(GLOB TEST_SRC "tests/*.cpp")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  tests
  ${TEST_SRC}
)
target_link_libraries(
  tests
  GTest::gtest_main
  libintcode
)

include(GoogleTest)
gtest_discover_tests(tests)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/.build/_deps/googletest-src/googletest/include)
