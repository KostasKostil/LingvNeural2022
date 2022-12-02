import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

news = pd.read_csv("news.csv", header=None, names=['cat', 'title', 'descr'])
news = news.dropna()

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Embedding, MaxPooling1D, Conv1D, GlobalMaxPooling1D, Dropout, LSTM, GRU
from tensorflow.keras.preprocessing.sequence import pad_sequences
from tensorflow.keras.preprocessing.text import Tokenizer
from tensorflow.keras import utils

words = 10000
inplen = 50
D = 5

data = news['title'] + ' ' + news['descr']
tok = Tokenizer(num_words=words)
tok.fit_on_texts(data)
seqs = tok.texts_to_sequences(data)

train_args = pad_sequences(seqs, maxlen=inplen)
train_res = utils.to_categorical(news['cat'], D)

model = Sequential()
model.add(Embedding(words, 32, input_length=inplen))
model.add(Conv1D(250, 5, padding='valid', activation='relu'))
model.add(GlobalMaxPooling1D())
model.add(Dense(128, activation='relu'))
model.add(Dense(D, activation='softmax'))

model.compile(loss='categorical_crossentropy', metrics=['accuracy'])

his = model.fit(train_args, train_res, epochs=5, batch_size=128, validation_split=0.1)
plt.plot(his.history['accuracy'], label='Точність при навчанні')
plt.plot(his.history['val_accuracy'], label='Точність при перевірці')
plt.xlabel('Епоха')
plt.ylabel('Точність')
plt.legend()
plt.show()
