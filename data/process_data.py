import chess
import chess.pgn
import random
import pickle
from fenUtils import *

# process the raw data (PGN files)
# takes games from a PGN file and splits it into PPG random positions in that game
# turn these positions into a bit string and store that in a file, one position per line

PPG = 10 # positions to get per game
IGNORE_FIRST = 6 # ignore the first few moves
VOLUME_SIZE = 50000
VOLUME_COUNT = 20
OUT_FILE_PREFIX = "processed/white_wins/2500_v" # path to output file
PGN_FILE = "raw/white_wins2500.pgn" # path to PGN input file

def getRandomNonCapturePositions(game):
    nonCapturePositions = []
    total = 0
    while not game.is_end():
        next_game = game.variation(0)
        move = (game.board().san(next_game.move))
        total = total + 1
        if 'x' not in move: 
            if total > IGNORE_FIRST:
                nonCapturePositions.append(game.board().fen())
        game = next_game

    randomPositions = []
    
    for i in range(PPG):
        if len(nonCapturePositions) == 0:
            break
        p = random.choice(nonCapturePositions)
        randomPositions.append(p)
        nonCapturePositions.remove(p)

    return randomPositions

def createVolume(pgn, volumeNumber):
    totalPositions = VOLUME_SIZE
    out = []
    count = 0
    print_when = 1000
    while count < totalPositions:
        game = chess.pgn.read_game(pgn)
        positions = getRandomNonCapturePositions(game)
        for p in positions:
            out.append(bitifyFEN(p))
            count += 1
            print_when -= 1

        if(print_when < 0):
            print(count)
            print_when = 1000
    
    print("saving %d positions" % len(out))

    name = OUT_FILE_PREFIX + str(volumeNumber) + ".p"
    dbfile = open(name, 'ab')
    pickle.dump(out, dbfile)                     
    dbfile.close()

def processPGN(pgn):
    for v in range(1, VOLUME_COUNT + 1):
        createVolume(pgn, v)

print("processing PGN file...")
pgn = open(PGN_FILE)
processPGN(pgn)