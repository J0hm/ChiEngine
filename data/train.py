import chess
import chess.svg
import chess.pgn
import numpy as np
import h5py
import random
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import TensorDataset
from sklearn.model_selection import train_test_split
import torch.nn.functional as F

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

class EvalNN(nn.Module):
    def __init__(self):
        super(EvalNN, self).__init__()
        self.p2v = nn.Sequential(
            nn.Conv2d(2, 32, 3),
            nn.ReLU(inplace=True),

            nn.Conv2d(32, 64, 3),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(2, 2)
        )
        self.p2v_last = nn.Linear(1920, 100)
        self.comp_pos = nn.Sequential(
            nn.Linear(210, 400),
            nn.ReLU(inplace=True),
            nn.Linear(400, 200),
            nn.ReLU(inplace=True),
            nn.Linear(200, 100),
            nn.ReLU(inplace=True),
            nn.Linear(100, 2)
        )

    def forward(self, x1, x2):
        x1_b, x1_i = x1[:768], x1[768:]
        x2_b, x2_i = x2[:768], x2[768:]

        x1_b = self.p2v(x1_b.view(1, 2, 6, 64))
        x1_b = self.p2v_last(x1_b.view(1, 1920))

        x2_b = self.p2v(x2_b.view(1, 2, 6, 64))
        x2_b = self.p2v_last(x2_b.view(1, 1920))

        x1 = torch.cat((x1_b, x1_i.unsqueeze(0)), 1)
        x2 = torch.cat((x2_b, x2_i.unsqueeze(0)), 1)

        x = torch.cat((x1, x2), 1)
        x = self.comp_pos(x)
        return F.softmax(x, dim=1)

def test_on_validation(model,winData=winData_val,loseData=loseData_val):
    model.eval()
    correct = 0
    with torch.no_grad():
        for (data1,data2) in zip(winData,loseData):   
            input_w,_ = data1
            input_l,_ = data2

            if random.randint(1,2) == 1:
                # Reverse wins and losses
                output = model(input_l,input_w)
                if torch.argmax(output) == torch.tensor(1):
                    correct += 1
            else:    
                output = model(input_w,input_l)
                if torch.argmax(output) == torch.tensor(0):
                    correct += 1
            
        acc = 100 * correct / len(winData_val)
        print('Accuracy on Validation Set:', acc,'%')
        return acc

evalNN = EvalNN()

if(TRAINING):
    #lr_h = 1e-5
    lr_h =  0.00005
    criterion = nn.MSELoss()
    optimizer = optim.Adam(evalNN.parameters(), lr=lr_h)
    MAX_EPOCHS = 50
    accuracy = []
    DATASET_RANGE_W = range(len(winData_train))
    DATASET_RANGE_L = range(len(loseData_train))
    k = 25000

    print("Starting training...")
    for epoch in range(MAX_EPOCHS):  # loop over the dataset multiple times
        running_loss = 0.0
        evalNN.train()

        # Selects k Random Samples
        idx_w = random.sample(DATASET_RANGE_W, k)
        idx_l = random.sample(DATASET_RANGE_L, k)

        for i in range(k):
            input_w, _ = winData_train[idx_w[i]]
            input_l, _ = loseData_train[idx_l[i]]
            # zero the parameter gradients
            optimizer.zero_grad()
            # forward + backward + optimize
            if random.randint(1, 2) == 1:
                # Reverse wins and losses
                output = evalNN(input_l, input_w)
                loss = criterion(output, torch.tensor([[0, 1]]).float())
            else:
                output = evalNN(input_w, input_l)
                loss = criterion(output, torch.tensor([[1, 0]]).float())

            loss.backward()
            optimizer.step()

            running_loss += loss.item()

        # Print Statistics
        print('Epoch: %d of %d, loss: %.4f' %
            (epoch + 1, MAX_EPOCHS, running_loss / k))

        # Decrease Learning Rate
        lr_h = lr_h * 0.98
        for g in optimizer.param_groups:
            g['lr'] = lr_h


    print('Finished training.')
    torch.save(evalNN.state_dict(), NET_PATH + 'ccrl3000evalNN' + str(MAX_EPOCHS) + 'epoch.pth')
    test_on_validation(evalNN)

if(TEST):
    evalNN.load_state_dict(torch.load('net/ccrl3000evalNN50epoch.pth'))
    test_on_validation(evalNN)

if(EXPORT):
    evalNN.load_state_dict(torch.load('net\ccrl3000evalNN50epoch.pth'))

    b1 = "r1bqkb1r/pppp1ppp/2n5/1B2p3/2P1n3/5N2/PP1PKPPP/RNBQ3R b kq - 0 5"
    b2 = "r1bqkb1r/pppp1ppp/2n5/1B2p3/4n3/5N2/PPPPKPPP/RNBQR3 b kq - 1 5"

    evalNN_scripted = torch.jit.script(evalNN)         # *** This is the TorchScript export
    x1 = torch.tensor(to_bitboard(chess.Board(b1))).float()
    x2 = torch.tensor(to_bitboard(chess.Board(b2))).float()

    unscripted_output = evalNN(x1, x2)         # Get the unscripted model's prediction...
    #scripted_output = evalNN_scripted(x1, x2)  # ...and do the same for the scripted version
    scripted_output = torch.jit.script(evalNN)

    # print('Python model result:')
    # if torch.argmax(unscripted_output) == torch.tensor(0):
    #     print((b1,b2))
    # else:
    #     print((b2,b1))

    # print('TorchScript model result:')
    # if torch.argmax(scripted_output) == torch.tensor(0):
    #     print((b1,b2))
    # else:
    #     print((b2,b1))

    torch.jit.save(scripted_output, 'net\ccrl3000eval.p')
    #evalNN_scripted.save('evalNN200epoch_scripted.pt')