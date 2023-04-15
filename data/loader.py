import numpy as np
import math
import pickle

WHITE_WINS_DIR = "processed/white_wins/"
BLACK_WINS_DIR = "processed/black_wins/"
PREFIX = "2500_v"
SUFFIX = ".p"

# get total positions of each black and white
# input_size is bits in each position,
# volume_size is size of each volume
def getTrain(input_size, total, volume_size):
    whiteWins = np.zeros((total, input_size))
    blackWins = np.zeros((total, input_size))

    for i in range(math.ceil(total/volume_size)): # for each volume...
        print("Loading white batch number " + str(i+1))
        f = open(WHITE_WINS_DIR + PREFIX + str(i+1) + SUFFIX, 'rb')
        white_data = pickle.load(f)
        white_positions = np.array(white_data)
        f.close()

        print("Loading black batch number " + str(i+1))
        f = open(BLACK_WINS_DIR + PREFIX + str(i+1) + SUFFIX, 'rb')
        black_data = pickle.load(f)
        black_positions = np.array(white_data)
        f.close()
        
        for j in range(volume_size): # for each pos in volume...
            whiteWins[i*volume_size+j] = white_data[j]
            blackWins[i*volume_size+j] = black_data[j]
	
    return (whiteWins, blackWins)