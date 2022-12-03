import random
import pdb
import argparse
import os
import math
import numpy as np
from scipy import sparse

parser = argparse.ArgumentParser(description='Input Matrix generator')
parser.add_argument('--seed', type=int, default=0, help='Seed Value')
parser.add_argument('--n', type=int, default=3, help='Matrix order(nxn)')
parser.add_argument('--sparsity', type=int, default=0, help='Sparisty of matrix in %')
parser.add_argument('--dump', type=str, default='input_matrix.in', help='File name')


def createRandomMatrix(n):
    maxVal = 1000  # I don't want to get Java / C++ into trouble
    matrix = []
    for i in range(n):
        matrix.append([random.randint(0, maxVal) for el in range(n)])
    return matrix


def saveMatrix(matrix, filename):
    if os.path.exists(filename): 
        os.remove(filename)
    else:   
        print("New file created: ",filename)
    f = open(filename, "w")
    for line in matrix:
        #pdb.set_trace()
        f.write("\t".join(map(str, line)) + "\n")


def saveCSRMatrix(CSR_matrix, filename):
    if os.path.exists(filename): 
        os.remove(filename)
    else:   
        print("New file created: ",filename)

    f = open(filename,"w")
    f.write(str(args.n))
    f.write("\n")
    for row, col in zip(*CSR_matrix.nonzero()):
        val = CSR_matrix[row,col]
        f.write("Row: "+str(row)+", Col: ")
        f.write(str(col)+", ")
        f.write("Val: "+str(val)+".")
        f.write("\n")
    f.close()

def main():
    global args
    args = parser.parse_args()
    print(40*"="+"\nArgs:{}\n".format(args)+40*"=")
    random.seed(args.seed)
    n = args.n
    outpath = args.dump
    #Create dense matrix
    matrix = createRandomMatrix(n)
    #print(matrix)
    #Convert to sparse matrix by replacing value below threshold to 0
    if (args.sparsity):
        #Replace random x %element to 0 in matrix
        matrix = np.asarray(matrix)
        indices = np.random.choice(np.arange(matrix.size), replace=False,
                            size=int(matrix.size * (args.sparsity/100)))
        flat  = matrix.flatten()
        flat[indices] = 0

        #Reshape it back to square matrix    
        flat = flat.reshape(n,n)
        #print(flat)
        # matrix_csr = sparse.csr_matrix(flat)
        #print(matrix_csr)
        matrix = flat.tolist()
        # csr_matrix = "csr_"+args.dump
        # saveCSRMatrix(matrix_csr, csr_matrix)
        #print(matrix)
    saveMatrix(matrix, args.dump)

if __name__ == '__main__':
    main()
