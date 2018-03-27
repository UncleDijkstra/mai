import argparse
import numpy as np
from numpy.linalg import eig, norm
from enum import Enum


def get_matrix(filename):
    with open(filename) as f:
        shape = int(f.readline())
        matrix = np.array([[float(num) for num in line.split()]
                           for _, line in zip(range(shape), f)])
        eps = float(f.readline())
        return shape, matrix, eps


class Matrix:
    class TypeOfEig(Enum):
        real = 0
        img = 1

    def __init__(self, input_name, output_name, log_name):
        self.out_file = output_name
        self.log_file = log_name
        if log_name:
            open(log_name, 'w').close()
        self.k_iter = 0
        self.shape, self.matrix, self.eps = get_matrix(input_name)
        self.eigenvalues = self.qr_algorithm()
        self.eig_np = eig(self.matrix)[0]

    def qr_decomposition(self, r):
        q = np.eye(self.shape)
        for i in range(self.shape - 1):
            h = self.make_householder(r[:, i], i)
            q = q @ h
            r = h @ r
            if self.log_file:
                with open(self.log_file, 'a') as f_log:
                    f_log.write(f'=============\n')
                    f_log.write(f'For i = {i}\n')
                    f_log.write(f'H:\n{h}\n')
                    f_log.write(f'Q:\n{h}\n')
                    f_log.write(f'R:\n{h}\n')
        return q, r

    def make_householder(self, a, k):
        v = np.zeros(self.shape)
        v[k] = a[k] + np.sign(a[k]) * norm(a[k:])
        for i in range(k + 1, self.shape):
            v[i] = a[i]
        h = np.eye(self.shape) - (2 / (v @ v)) * (v[:, None] @ v[None, :])
        return h

    def qr_algorithm(self):
        a = self.matrix.copy()
        flag = True
        while True:
            q, r = self.qr_decomposition(a)
            a = r @ q
            is_eig, type_eig = zip(*self.check(a))
            if self.log_file:
                with open(self.log_file, 'a') as f_log:
                    f_log.write(f'=============\n')
                    f_log.write(f'{self.k_iter} th:\n')
                    f_log.write(f'Q:\n{q}\n')
                    f_log.write(f'R:\n{r}\n')
                    f_log.write(f'New A = R * Q:\n{a}\n')
                    f_log.write(f'Is eig:\n{is_eig}\n')
                    f_log.write(f'Type eig:\n{type_eig}\n')
            if all(is_eig):
                if flag:
                    flag = False
                else:
                    return self.take_eig(a, type_eig)
            self.k_iter += 1

    def take_eig(self, matrix, type_eig):
        sol = []
        idx = 0
        for i in type_eig:
            if i == self.TypeOfEig.real:
                sol.append(matrix[idx, idx])
            else:
                a11 = matrix[idx, idx]
                a12 = matrix[idx, idx + 1]
                a21 = matrix[idx + 1, idx]
                a22 = matrix[idx + 1, idx + 1]
                sol.extend(np.roots((1, -a11 - a22, a11 * a22 - a12 * a21)))
                idx += 1
            idx += 1
        return np.array(sol)

    def check(self, matrix):
        check_eig = []
        j = 0
        while j < self.shape:
            if norm(matrix[j + 1:, j]) <= self.eps:
                check_eig.append((True, self.TypeOfEig.real))
            elif norm(matrix[j + 2:, j]) <= self.eps:
                check_eig.append((True, self.TypeOfEig.img))
                j += 1
            else:
                check_eig.append((False, None))
            j += 1
        return check_eig

    def print_solution(self):
        if self.log_file:
            with open(self.log_file, 'a') as f_log:
                f_log.write(f'=============\n')
                f_log.write(f'General EPS = {self.eps}\nMatrix info:\n')
                f_log.write(f'Shape = {self.shape}\n')
                f_log.write(f'Matrix:\n{self.matrix}\n')
        with open(self.out_file, 'w') as f_out:
            f_out.write(f'Solution:\nSteps = {self.k_iter}\n')
            f_out.write(f'Eigenvalues:\n{self.eigenvalues.round(3)}\n')
            f_out.write(f'\nCheck by NumPy:\n')
            f_out.write(f'Eigenvalues:\n{self.eig_np.round(3)}\n')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', required=True, help='Input test file')
    parser.add_argument('--output', required=True, help='File for answer')
    parser.add_argument('--log', help='Logging')
    args = parser.parse_args()

    matrix = Matrix(args.input, args.output, args.log)
    matrix.print_solution()

if __name__ == "__main__":
    main()
