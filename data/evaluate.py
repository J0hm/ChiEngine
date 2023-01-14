import tensorflow as tf
import numpy as np
import random
from loader import *

white_wins, black_wins = getTrain(773, 100000, 50000)

def getBatchAE(size):
	global black_wins
	global white_wins

	random.shuffle(black_wins)
	random.shuffle(white_wins)
	
	res = np.zeros((size, 773))

	for i in range(size):
		if(random.random() > 0.5):
			res[i] = black_wins[i]
		else:
			res[i] = white_wins[i]
		
	random.shuffle(res)

	return res


autoencoder = tf.keras.models.load_model('net/autoencoder')

test_data = getBatchAE(100000)

# Evaluate the model on the test data using `evaluate`
print("Evaluate on test data")
results = autoencoder.evaluate(test_data, test_data, batch_size=128)
print("Test loss: ", results)