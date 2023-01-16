import chess
import chess.pgn
import random
import numpy as np
import h5py

# process the raw data (PGN files)
# takes games from a PGN file and splits it into PPG random positions in that game
# turn these positions into a bit string and store that in a file, one position per line

PPG = 10  # positions to get per game
IGNORE_FIRST = 6  # ignore the first few moves
VOLUME_SIZE = 50000
VOLUME_COUNT = 20
OUT_FILE = "processed/data_3000wins_1Mpositions_ccrl.h5"  # path to output file
PGN_FILE = "raw/CCRL2020-2022/3000wins_ccrl2020-22.pgn"  # path to PGN input file


def get_positions(game, num_pos=10):
    legal_positions = []
    board = game.board()
    for i, move in enumerate(game.mainline_moves()):
        if board.is_capture(move) or i < 5:
            board.push(move)
        else:  # legal
            board.push(move)
            legal_positions.append(board)
    return random.sample(legal_positions, num_pos) if len(legal_positions) >= num_pos else []


def to_bitboard(board):
    bb = np.zeros((2, 6, 64), dtype=np.uint8)  # players x pieces x board-size
    for colour in range(2):
        for piece in range(6):
            for square in range(64):
                cur_piece = board.piece_at(square)
                if cur_piece is not None:
                    if cur_piece.piece_type == piece+1 and cur_piece.color == bool(colour):
                        bb[colour][piece][square] = 1

    flags = np.zeros(5, dtype=np.uint8)
    flags[0] = board.has_kingside_castling_rights(chess.WHITE)
    flags[1] = board.has_kingside_castling_rights(chess.BLACK)
    flags[2] = board.has_queenside_castling_rights(chess.WHITE)
    flags[3] = board.has_queenside_castling_rights(chess.BLACK)
    flags[4] = board.turn

    bb = bb.flatten()
    bb = np.concatenate((bb, flags))
    return bb


def preprocess(num_samples, fn=PGN_FILE):
    X_win, Y_win, X_lose, Y_lose = [], [], [], []
    n, m = 0, 0
    all_games = open(fn)
    while n < num_samples or m < num_samples:
        game = chess.pgn.read_game(all_games)
        total = n + m
        if(total%5000 == 0):
            print(total, ": ", (total/(2*num_samples))*100, "%")

        if game == None:  # EOF
            print("EOF:", n, "games obtained")
        if game.headers['Result'] != '1-1':  # not a draw, shouldnt be possible with the right dataset
            boards = get_positions(game)
            for board in boards:
                if game.headers['Result'] == '1-0' and n < num_samples:
                    n += 1
                    X_win.append(to_bitboard(board))  # white win
                    Y_win.append(1)
                elif m < num_samples:
                    m += 1
                    X_lose.append(to_bitboard(board))  # white lose
                    Y_lose.append(0)
    return X_win, Y_win, X_lose, Y_lose


# process data
X_win, Y_win, X_lose, Y_lose = preprocess(1000000)
assert len(X_win) == len(Y_win) and len(X_win) == len(Y_win)
print("# of winning positions for white:", len(X_win))
print("# of winning positions for black:", len(X_lose))

# save data
hf = h5py.File(OUT_FILE, 'w')
hf.create_dataset('X_win', data=X_win)
hf.create_dataset('Y_win', data=Y_win)
hf.create_dataset('X_lose', data=X_lose)
hf.create_dataset('Y_lose', data=Y_lose)
hf.close()