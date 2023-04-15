import chess
import chess.svg
import chess.pgn
import numpy as np
import h5py
import torch
from torch.utils.data import TensorDataset
from sklearn.model_selection import train_test_split


DATA_PATH = "processed/data_3000wins_1Mpositions_ccrl.h5"
NET_PATH = "net/"
TRAINING = False
TEST = False
EXPORT = True

# Load Data and Compute Train/Test Splits
hf = h5py.File(DATA_PATH, 'r')
X_win_train, X_win_val, Y_win_train, Y_win_val = train_test_split(np.array(hf.get('X_win')),
                                                                  np.array(
                                                                      hf.get('Y_win')),
                                                                  test_size=0.1, random_state=3)
X_lose_train, X_lose_val, Y_lose_train, Y_lose_val = train_test_split(np.array(hf.get('X_lose')),
                                                                      np.array(
                                                                          hf.get('Y_lose')),
                                                                      test_size=0.1, random_state=3)

hf.close()

# Convert Data To Tensors

# Train
X_win_train = torch.tensor(X_win_train).float()
Y_win_train = torch.tensor(Y_win_train)
winData_train = TensorDataset(X_win_train, Y_win_train)

X_lose_train = torch.tensor(X_lose_train).float()
Y_lose_train = torch.tensor(Y_lose_train)
loseData_train = TensorDataset(X_lose_train, Y_lose_train)

# Val
X_win_val = torch.tensor(X_win_val).float()
Y_win_val = torch.tensor(Y_win_val)
winData_val = TensorDataset(X_win_val, Y_win_val)

X_lose_val = torch.tensor(X_lose_val).float()
Y_lose_val = torch.tensor(Y_lose_val)
loseData_val = TensorDataset(X_lose_val, Y_lose_val)

a = winData_train[0][0]
b = loseData_train[0][0]

main_input = torch.cat([a.unsqueeze(0), b.unsqueeze(0)])

a_s = main_input[0]
b_s = main_input[1]

print(torch.equal(a, a_s))
print(torch.equal(b, b_s))