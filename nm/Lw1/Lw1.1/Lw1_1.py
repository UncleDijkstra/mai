import argparse
import numpy as np
from pprint import pformat


class Matrix:
    def __init__(self, input_name, output_name, log_name):
        self.log_file = log_name
        self.answer_file = output_name
        self.shape, self.matrix, self.b = self.get_matrix(input_name)
        self.l_matrix, self.u_matrix, self.p = self.lu_decomposition()
        self.x = self.solve_by_lu(self.create_p_matrix(self.b, self.p))
        self.inverse_matrix = self.inverse()
        self.det_matrix = self.det()

    @staticmethod
    def get_matrix(filename):
        with open(filename) as f:
            shape = int(f.readline())
            matrix = np.array([[int(num) for num in line.split()]
                              for _, line in zip(range(shape), f)])
            b = np.array([int(num) for num in f.readline().split()])
            return shape, matrix, b

    @staticmethod
    def swap_lines(matrix, l1, l2):
        matrix[l1], matrix[l2] = matrix[l2].copy(), matrix[l1].copy()

    def pivot(self):
        p = []
        mtrx = self.matrix.copy()
        for j in range(self.shape - 1):
            tmp = [(mtrx[i][j], i) for i in range(j, self.shape)]
            idx = max(tmp, key=lambda x: abs(x[0]))[1]
            if idx != j:
                p.append((j, idx))
                self.swap_lines(mtrx, j, idx)
        return p, mtrx

    def create_p_matrix(self, matrix, p):
        p_matrix = matrix.copy()
        for i, j in p:
            self.swap_lines(p_matrix, i, j)
        return p_matrix

    def lu_decomposition(self):
        l_matrix = np.zeros((self.shape, self.shape))
        u_matrix = np.zeros((self.shape, self.shape))
        p, p_matrix = self.pivot()
        for j in range(self.shape):
            l_matrix[j][j] = 1.0
            for i in range(j + 1):
                s1 = sum(u_matrix[k][j] * l_matrix[i][k] for k in range(i))
                u_matrix[i][j] = p_matrix[i][j] - s1
            for i in range(j, self.shape):
                s2 = sum(u_matrix[k][j] * l_matrix[i][k] for k in range(j))
                l_matrix[i][j] = (p_matrix[i][j] - s2) / u_matrix[j][j]
        return l_matrix, u_matrix, p

    def solve_by_lu(self, b):
        z = np.zeros(self.shape)
        x = np.zeros(self.shape)
        z[0] = b[0]
        for i in range(1, self.shape):
            s1 = sum([self.l_matrix[i][j] * z[j] for j in range(i)])
            z[i] = b[i] - s1
        x[-1] = z[-1] / self.u_matrix[-1][-1]
        for i in reversed(range(self.shape - 1)):
            s2 = sum([self.u_matrix[i][j] * x[j]
                      for j in range(i + 1, self.shape)])
            x[i] = (z[i] - s2) / self.u_matrix[i][i]
        return x

    def inverse(self):
        return np.transpose(np.array([self.solve_by_lu(col)
                                     for col in np.eye(self.shape)]))

    def det(self):
        return (-1)**len(self.p) * np.prod(np.diag(self.u_matrix))

    def print_answer(self):
        if self.log_file:
            with open(self.log_file, 'w') as fl:
                fl.write(f'Shape = {self.shape}\nMatrix:\n')
                fl.write(pformat(self.matrix.round(2)))
                fl.write(f'\nVector = {self.b}\nL-matrix:\n')
                fl.write(pformat(self.l_matrix.round(2)))
                fl.write('\nU-matrix:\n')
                fl.write(pformat(self.u_matrix.round(2)) + '\n')

        with open(self.answer_file, 'w') as fo:
            fo.write('Answer:\n')
            fo.write(f'x = {self.x.round(2)}\n')
            fo.write(f'inverse_matrix PA:\n{pformat(self.inverse_matrix)}\n')
            fo.write(f'det = {round(self.det_matrix)}\n')
            fo.write(f'\nCheck by NumPy:\nx = ')
            fo.write(f'{np.linalg.solve(self.matrix, self.b).round(2)}\n')
            fo.write(f'inverse_matrix A:\n')
            fo.write(f'{pformat(np.linalg.inv(self.matrix))}\n')
            fo.write(f'det = {round(np.linalg.det(self.matrix))}\n')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', required=True, help='Input test file')
    parser.add_argument('--output', required=True, help='File for answer')
    parser.add_argument('--log', help='Logging')
    args = parser.parse_args()

    matrix = Matrix(args.input, args.output, args.log)
    matrix.print_answer()

if __name__ == "__main__":
    main()
