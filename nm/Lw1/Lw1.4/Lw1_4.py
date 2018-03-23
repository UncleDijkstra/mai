import argparse
import numpy as np
from numpy.linalg import eig


def get_matrix(filename):
    with open(filename) as f:
        shape = int(f.readline())
        matrix = np.array([[float(num) for num in line.split()]
                           for _, line in zip(range(shape), f)])
        eps = float(f.readline())
        return shape, matrix, eps


class Matrix:
    def __init__(self, input_name, output_name, log_name):
        self.out_file = output_name
        self.log_file = log_name
        if log_name:
            open(log_name, 'w').close()
        self.k_iter = 0
        self.shape, self.matrix, self.eps = get_matrix(input_name)
        self.eigenvalues, self.eigenvectors = self.jacobi_eigenvalue()
        self.eig_np = eig(self.matrix)

    def find_max(self, matrix):
        i_of_max = None
        j_of_max = None
        max_elem = -np.inf
        for i in range(self.shape):
            for j in range(i + 1, self.shape):
                if abs(matrix[i, j]) > max_elem:
                    max_elem = abs(matrix[i, j])
                    i_of_max = i
                    j_of_max = j
        if self.log_file:
            with open(self.log_file, 'a') as fl:
                fl.write('Max elem on {0} step: a[{1}][{2}] = {3}\n'.format(
                    self.k_iter, i_of_max, j_of_max, max_elem))
        return i_of_max, j_of_max

    def t(self, matrix):
        tmp = np.sqrt(sum([matrix[i, j] ** 2 for i in range(self.shape)
                          for j in range(i + 1, self.shape)]))
        if self.log_file:
            with open(self.log_file, 'a') as fl:
                fl.write(f't(A{self.k_iter}) = {tmp}\n')
        return tmp

    def jacobi_eigenvalue(self):
        iter_matrix = self.matrix.copy()
        u = np.eye(self.shape)
        while True:
            u_matrix = np.eye(self.shape)
            i, j = self.find_max(iter_matrix)
            num1 = iter_matrix[i, i]
            num2 = iter_matrix[j, j]
            if num1 != num2:
                phi = np.arctan(2 * iter_matrix[i, j] / (num1 - num2)) / 2
            else:
                phi = np.pi / 4
            u_matrix[i, j] = -np.sin(phi)
            u_matrix[j, i] = np.sin(phi)
            u_matrix[i, i] = np.cos(phi)
            u_matrix[j, j] = np.cos(phi)
            u = u @ u_matrix
            iter_matrix = np.transpose(u_matrix) @ iter_matrix @ u_matrix
            self.k_iter += 1
            if self.log_file:
                with open(self.log_file, 'a') as fl:
                    fl.write(f'Step {self.k_iter - 1}:\n')
                    fl.write(f'Phi = {phi}\n')
                    fl.write(f'U matrix:\n{u_matrix}\n')
                    fl.write(f'Iter matrix:\n{iter_matrix}\n')
            if self.t(iter_matrix) < self.eps:
                break
        l = np.diag(iter_matrix)
        return l, u

    def print_solution(self):
        if self.log_file:
            with open(self.log_file, 'a') as f_log:
                f_log.write(f'General EPS = {self.eps}\nMatrix info:\n')
                f_log.write(f'Shape = {self.shape}\n')
                f_log.write(f'Matrix:\n{self.matrix}\n')
        with open(self.out_file, 'w') as f_out:
            f_out.write(f'Solution:\nSteps = {self.k_iter}\n')
            f_out.write(f'Eigenvalues:\n{self.eigenvalues.round(3)}\n')
            f_out.write(f'Eigenvectors:\n{self.eigenvectors.round(3)}\n')
            f_out.write(f'\nCheck by NumPy:\n')
            f_out.write(f'Eigenvalues:\n{self.eig_np[0].round(3)}\n')
            f_out.write(f'Eigenvectors:\n{self.eig_np[1].round(3)}\n')


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
