# ChiEngine
A basic UCI chess engine written in C++.

The game board is represented with a bitboard, more about its structure can be seen in Board.h

Magic moves are used for move generation.

Search uses alpha-beta pruning with a transposition table of Zobrist hashes and MVV-LVA. Eval uses a basic PESTO table with game-phase weighting by amount of total material.

Currently plays at ~1500-1800 elo (I think), but this is hard to test with such a weak engine. Future improvements will focus on an overall refactor and implementing a time manager based on iterative deepening, so true timed games can be played. 
