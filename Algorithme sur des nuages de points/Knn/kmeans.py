import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs

n_samples = 1500
random_state = 170

X, y = make_blobs(n_samples=n_samples, random_state=random_state)

#Affichage


plt.scatter(X[:, 0], X[:, 1], c=y)
plt.suptitle("Résultat de Kmeans").set_y(0.95)
plt.show()