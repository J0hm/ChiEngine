import tensorflow as tf
import pandas as pd
import numpy as np
import math
import random
from loader import *

from tensorflow.python.keras import layers, losses
from tensorflow.python.keras.models import Model

TRAIN_AUTOENCODER = 1
TRAIN_NET = 0

TOTAL_AE = 250000
TOTAL_MLP = 750000

# TOTAL_AE = 25000
# TOTAL_MLP = 50000

BS_AE = 20
BS_MLP = 50
EPOCHS_AE = 50 
EPOCHS_MLP = 201 
RATE_AE = 0.005
DECAY_AE = 0.98
RATE_MLP = 0.005
DECAY_MLP = 0.98

BIAS = 0.15

N_INPUT = 773
ENCODING_1 = 600 
ENCODING_2 = 400 
ENCODING_3 = 200
ENCODING_4 = 100

HIDDEN_1 = 200
HIDDEN_2 = 400 
HIDDEN_3 = 200
HIDDEN_4 = 100 
N_OUT = 2

VOLUME_SIZE = 50000

EXPORT_PATH = 'net/'

#Get the data from the game files
white_wins, black_wins = getTrain(N_INPUT, TOTAL_MLP, VOLUME_SIZE)

def getBatchMLP(start, size):
	global white_wins 
	global black_wins 

	xR = []
	lR = []
	
	for i in range(math.floor(start), math.ceil(start+size)):
		if random.random() > 0.5:
			elem = [white_wins[i], black_wins[i]]
			elem_l = [1,0]
		else:
			elem = [black_wins[i], white_wins[i]]
			elem_l = [0,1]
		xR.append(elem)
		lR.append(elem_l)
	return (xR, lR)

def getBatchAE(size):
	global black_wins
	global white_wins

	random.shuffle(black_wins)
	random.shuffle(white_wins)
	
	res = np.zeros((size, N_INPUT))

	for i in range(size):
		if(random.random() > 0.5):
			res[i] = black_wins[i]
		else:
			res[i] = white_wins[i]
		
	random.shuffle(res)

	return res


#full model
# y = model(x, weights, biases)

# cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(y,y_))
# mlp_train_step = tf.keras.optimizers.Adam(learning_rate=learning_rate).minimize(cross_entropy)

# TODO weights??
class Pos2Vec(Model):
	def __init__(self):
		super(Pos2Vec, self).__init__()
		self.encoder = tf.keras.Sequential([
			layers.Dense(N_INPUT, activation='relu'),
			layers.Dense(ENCODING_1, activation='relu'),
			layers.Dense(ENCODING_2, activation='relu'),
			layers.Dense(ENCODING_3, activation='relu'),
			layers.Dense(ENCODING_4, activation='relu')
		])
		self.decoder = tf.keras.Sequential([
			layers.Dense(ENCODING_4, activation='relu'),
			layers.Dense(ENCODING_3, activation='relu'),
			layers.Dense(ENCODING_2, activation='relu'),
			layers.Dense(ENCODING_1, activation='relu'),
			layers.Dense(N_INPUT, activation='sigmoid')])
		
	def call(self, x):
		encoded = self.encoder(x)
		decoded = self.decoder(encoded)
		return decoded

autoencoder = Pos2Vec()
autoencoder.compile(optimizer='SGD', loss=losses.MeanSquaredError()) # mean squared error?

print("Getting auto-encoder data...")
ae_train = getBatchAE(TOTAL_AE)

print("Beginning auto-encoder training...")
autoencoder.fit(ae_train, ae_train,
                epochs=EPOCHS_AE,
				steps_per_epoch=int(TOTAL_AE/EPOCHS_AE),
                shuffle=True,
				verbose=2)

autoencoder.summary()
autoencoder.save(EXPORT_PATH + 'autoencoder')

# test_data = getBatchAE(100000)

# # Evaluate the model on the test data using `evaluate`
# print("Evaluate on test data")
# results = autoencoder.evaluate(test_data, test_data, batch_size=128)
# print("test loss, test acc:", results)