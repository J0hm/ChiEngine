cmake_minimum_required(VERSION 3.23)
project(ChiEngine)

set(HEADER_FILES
        Types.h
        Algorithms.h
        Board.h
        InputThread.h
        Move.h
        Engine.h
        MoveGen.h
        MagicMoves.h
        ZobristHasher.h
        Evaluate.h)

set(SOURCE_FILES
        Main.cpp
        Engine.cpp
        Board.cpp
        InputThread.cpp
        Move.cpp
        MoveGen.cpp
        MagicMoves.cpp
        ZobristHasher.cpp
        Evaluate.cpp)

set(REQUIRE_TORCH Evaluate.cpp Evaluate.h)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})

list(APPEND CMAKE_PREFIX_PATH C:/Users/johnk/Documents/Programming/C++/_lib/libtorch/share/cmake/Torch)
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
add_executable(ChiEngine_run main.cpp)

target_link_libraries(src ${TORCH_LIBRARIES})
target_link_libraries(ChiEngine_run src)
set_property(TARGET ChiEngine_run PROPERTY CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD 14)

#add_subdirectory(googletests)