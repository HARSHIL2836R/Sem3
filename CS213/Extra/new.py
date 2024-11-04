import numpy as np

# Define the matrix
matrix = np.array([
    [3/5, -np.sqrt(3)/5, 0, 0, 0, 0],
    [-np.sqrt(3)/5, 1/5, 0, 0, 0, 0],
    [0, 0, 1/5, 0, 0, 0],
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0]
])

# Calculate the eigenvalues
eigenvalues = np.linalg.eigvals(matrix)
print(eigenvalues)