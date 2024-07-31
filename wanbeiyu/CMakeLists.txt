cmake_minimum_required(VERSION 3.10)

project(wanbeiyu VERSION 0.1.0)
set(CMAKE_C_STANDARD 90)

file(GLOB_RECURSE SRC_FILES src/*.c)
add_library(wanbeiyu STATIC ${SRC_FILES})
target_include_directories(wanbeiyu PUBLIC include)

enable_testing()

add_executable(wanbeiyu_test test/test.c)
target_link_libraries(wanbeiyu_test wanbeiyu)
add_test(NAME wanbeiyu_test COMMAND wanbeiyu_test)
