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
        ZobristHasher.h Eval.h Search.h InputTest.h TTable.h)

set(SOURCE_FILES
        Main.cpp
        Engine.cpp
        Board.cpp
        InputThread.cpp
        Move.cpp
        MoveGen.cpp
        MagicMoves.cpp
        ZobristHasher.cpp Eval.cpp Search.cpp InputTest.cpp InputTest.h TTable.cpp)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(ChiEngine_run main.cpp)
target_link_libraries(ChiEngine_run src)