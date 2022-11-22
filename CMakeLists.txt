cmake_minimum_required(VERSION 3.23)
project(ChiEngine)

set(CMAKE_CXX_STANDARD 14)

add_executable(ChiEngine
        src/main.cpp)

include_directories(src)
add_subdirectory(src)

#target_link_libraries(DateConverter_run DateConverter_lib)

add_subdirectory(test)