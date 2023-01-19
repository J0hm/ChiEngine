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
        Engine.cpp
        Board.cpp
        InputThread.cpp
        Move.cpp
        MoveGen.cpp
        MagicMoves.cpp
        ZobristHasher.cpp
        Evaluate.cpp)

set(DEBUG 1)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})

list(APPEND CMAKE_PREFIX_PATH C:/Users/johnk/Documents/Programming/C++/_lib/libtorch/share/cmake/Torch)
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 14)

target_link_libraries(src ${TORCH_LIBRARIES})

add_executable(ChiEngine_run main.cpp)
add_executable(Debug_run debug.cpp)
target_link_libraries(ChiEngine_run src)
target_link_libraries(Debug_run src)

set_property(TARGET Debug_run PROPERTY CXX_STANDARD 14)
# set_property(TARGET ChiEngine_run PROPERTY CXX_STANDARD 14)

target_compile_definitions(Debug_run PRIVATE
        $<$<CONFIG:Debug>:
        Debug_run_DEBUG=1
        >
        )

if (MSVC)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET Debug_run
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${TORCH_DLLS}
            $<TARGET_FILE_DIR:Debug_run>)
endif (MSVC)

#if (MSVC)
#    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
#    add_custom_command(TARGET ChiEngine_run
#            POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            ${TORCH_DLLS}
#            $<TARGET_FILE_DIR:ChiEngine_run>)
#endif (MSVC)