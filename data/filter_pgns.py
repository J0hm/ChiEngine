import chess
import chess.pgn
import glob

SRC_DIR = "raw/ccrl/overall/"
OUT_FILE = "raw/ccrl/ccrl_over_3000.pgn"
CUTOFF = 3000

found = 0
count = 0
out = open(OUT_FILE, "w")
for file in glob.glob(SRC_DIR + '*.pgn'):
    print(file)
    pgn = open(file)

    game = chess.pgn.read_game(pgn)
    while(game is not None):
        count = count + 1

        try:
            if(int(game.headers['WhiteElo']) >= CUTOFF and int(game.headers['BlackElo']) >= CUTOFF and game.headers['Result'] != '1/2-1/2'):
                print(game, file=out, end="\n\n")
                found = found + 1
        except:
            print("Error reading headrs.")

        if(count % 2000 == 0):
            print("Found %d games after searching %d." % (found, count))
        game = chess.pgn.read_game(pgn)

print("Found %d games after searchging %d." % (found, count))
