import numpy as np
import matplotlib.pyplot as plt

from sklearn.preprocessing import StandardScaler
from neupy import algorithms
from neupy.layers import Input, Tanh, Linear

h = 0.02
t = np.linspace(0, 4, int(4/0.02), endpoint=True)
x = np.sin(t**2)

train_size = int(t.shape[0] * 0.9)
train_size

X_train = t[:train_size]
y_train = x[:train_size]

X_test = t[train_size:]
y_test = x[train_size:]

scaler_x = StandardScaler()
scaler_y = StandardScaler()
tmp_train_scaled_x = scaler_x.fit_transform(X_train[:, np.newaxis])
tmp_test_scaled_x = scaler_x.transform(X_test[:, np.newaxis])
tmp_train_scaled_y = scaler_y.fit_transform(y_train[:, np.newaxis])

lmnet = algorithms.LevenbergMarquardt((Input(1), Tanh(20), Linear(1)), verbose=True)

lmnet.train(X_train, y_train, epochs=500)

pred_x = lmnet.predict(X_train)
pred_x = scaler_y.inverse_transform(pred_x)
mse = mean_squared_error(y_train, pred_x.flatten())
print(f'RMSE = {np.sqrt(mse)}')

plt.plot(X_train, y_train, label='train')
plt.plot(X_train, pred_x, label='predict')
plt.legend()
plt.show()
