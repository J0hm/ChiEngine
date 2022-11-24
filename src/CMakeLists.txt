project(ChiEngine)

set(HEADER_FILES
        Types.h
        Algorithms.h
        Board.h
        InputThread.h
        Move.h
        Engine.h
        )

set(SOURCE_FILES
        Main.cpp
        Engine.cpp
        Board.cpp
        InputThread.cpp
        Move.cpp
        Algorithms.cpp)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})