project(ChiEngine)

set(HEADER_FILES
        Algorithms.h
        Board.h
        Engine.h
        InputThread.h
        Types.h
        )

set(SOURCE_FILES
        Board.cpp
        Engine.cpp
        InputThread.cpp
        Move.cpp Move.h)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})