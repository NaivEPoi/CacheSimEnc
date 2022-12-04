from random import SystemRandom
import numpy as np

# Generate 56*28 S-boxes
def gen_sbox():
    sbox = []
    for _ in range(28):
        line = [0] * 28 + [1] * 28
        SystemRandom().shuffle(line)
        # print(line)
        sbox.append(line)
    # check if the generated sbox is full rank
    if (np.linalg.matrix_rank(sbox) != 28):
        print("S-box is not full rank, generating again...")
        return gen_sbox()
    else:
        print("S-Box: ")
        print_matrix(sbox)

# Generate 28*28 P-boxes
def gen_pbox():
    index = list(range(0, 28))
    SystemRandom().shuffle(index)
    # print(index)
    out = np.zeros((28, 28), dtype=int)
    for i in range(28):
        out[i][index[i]] = 1
    print("P-Box: ")
    print_matrix(out)

# print matrix
def print_matrix(matrix):
    print("[", end='')
    for i in range(len(matrix)):
        print("[", end='')
        for j in range(len(matrix[i])):
            print(matrix[i][j], end='')
            if j != len(matrix[i]) - 1:
                print(", ", end='')
        print("]", end='')
        if i != len(matrix) - 1:
            print(",")
    print("]")

gen_pbox()
gen_sbox()