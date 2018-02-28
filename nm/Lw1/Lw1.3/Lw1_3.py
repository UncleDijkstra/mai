import argparse
import numpy as np
from numpy.linalg import norm, solve, inv


def get_matrix(filename):
    with open(filename) as f:
        shape = int(f.readline())
        matrix = np.array([[float(num) for num in line.split()]
                           for _, line in zip(range(shape), f)])
        b = np.array([int(num) for num in f.readline().split()])
        eps = float(f.readline())
        return shape, matrix, b, eps


class Matrix:
    def __init__(self, input_name, output_name, log_name):
        self.out_file = output_name
        self.log_file = log_name
        with open(log_name, 'w'):
            pass
        self.shape, self.matrix, self.b, self.eps = get_matrix(input_name)
        self.alpha, self.beta = self.equivalent_form()
        self.k_iter, self.x_iter = self.iter_solve()
        self.k_sdl, self.x_sdl = self.seidel_solve()

    def equivalent_form(self):
        alpha = np.zeros((self.shape, self.shape))
        beta = []
        for i in range(self.shape):
            beta.append(self.b[i] / self.matrix[i][i])
            for j in range(self.shape):
                if i != j:
                    alpha[i][j] = -self.matrix[i][j] / self.matrix[i][i]
        return alpha, np.array(beta)

    def iter_solve(self):
        x = self.beta
        k = 0
        nec_norm = self.get_norm()
        if self.log_file:
            f_log = open(self.log_file, 'a')
            f_log.write('Iter:\n')
        while True:
            x_next = self.beta + self.alpha @ x
            k += 1
            if self.log_file:
                f_log.write(f'eps{k} = {nec_norm(x_next, x):.4f}\n')
                f_log.write(f'x{k} = {x_next.round(4)}\n')
            if nec_norm(x_next, x) <= self.eps:
                break
            x = x_next
        if self.log_file:
            f_log.close()
        return k, x_next

    def seidel_solve(self):
        k = 0
        b = np.tril(self.alpha, -1)
        c = self.alpha - b
        tmp1 = inv(np.eye(self.shape, self.shape) - b) @ c
        tmp2 = inv(np.eye(self.shape, self.shape) - b) @ self.beta
        x = tmp2
        nec_norm = self.get_norm(tmp1, c)
        if self.log_file:
            f_log = open(self.log_file, 'a')
            f_log.write('Seidel:\n')
        while True:
            x_next = tmp2 + tmp1 @ x
            k += 1
            if self.log_file:
                f_log.write(f'eps{k} = {nec_norm(x_next, x):.4f}\n')
                f_log.write(f'x{k} = {x_next}\n')
            if nec_norm(x_next, x) <= self.eps:
                break
            x = x_next
        if self.log_file:
            f_log.close()
        return k, x_next

    def get_norm(self, s_alpha=None, c=None):
        for i in range(self.shape):
            tmp = 0
            for j in range(self.shape):
                if i != j:
                    tmp += abs(self.matrix[i][j])
            if abs(self.matrix[i][i]) <= tmp:
                return lambda x, y: norm(x - y, np.inf)
        if c is not None:
            method1 = s_alpha
            method2 = c
        else:
            method1 = self.alpha
            method2 = self.alpha
        coef = norm(method2, np.inf) / (1 - norm(method1, np.inf))
        return lambda x, y: coef * norm(x - y, np.inf)

    def print_solution(self):
        if self.log_file:
            with open(self.log_file, 'a') as f_log:
                f_log.write(f'General EPS = {self.eps}\nMatrix info:\n')
                f_log.write(f'Shape = {self.shape}\n')
                f_log.write(f'Matrix:\n{self.matrix}\n')
                f_log.write(f'Alpha:\n{self.alpha}\n')
                f_log.write(f'Beta:\n{self.beta}\n')
        with open(self.out_file, 'w') as f_out:
            f_out.write(f'Iter:\nSteps = {self.k_iter}\nx = {self.x_iter}\n')
            f_out.write(f'Seidel:\nSteps = {self.k_sdl}\nx = {self.x_sdl}\n')
            f_out.write(f'Check by NumPy:\n')
            f_out.write(f'x = {solve(self.matrix, self.b)}\n')


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
