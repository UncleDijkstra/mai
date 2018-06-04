import argparse
import numpy as np
from numpy.linalg import norm
from scipy.sparse import diags, csc_matrix
from scipy.sparse.linalg import bicgstab, spilu
from time import time


def get_matrix(filename, is_diag):
    with open(filename) as f:
        shape = int(f.readline())
        matrix = [[float(num) for num in line.split()]
                  for _, line in zip(range(shape), f)]
        if is_diag:
            matrix[0].insert(0, 0)
            matrix[-1].append(0)
            a, b, c = zip(*matrix)
            matrix = diags([a[1:], b, c[:-1]], [-1, 0, 1])
            matrix = csc_matrix(matrix)
        else:
            matrix = csc_matrix(matrix)
        b = np.array([float(num) for num in f.readline().split()])
        return matrix, b


class BiCGStab:
    def __init__(self, matrix, b, output_file, log_file,
                 x0=None, eps=1e-5):
        self.output = 'res_default' if output_file is None else output_file
        self.log = 'log_default' if log_file is None else log_file
        self.matrix = matrix
        self.b = b
        self.eps = eps
        self.shape = matrix.shape[0]
        self.x0 = np.array([0] * self.shape) if x0 is None else x0
        self.k = 0

    def solve(self):
        r0 = self.b - self.matrix @ self.x0
        x0 = self.x0
        r2 = r0
        rho0 = 1
        alpha0 = 1
        omega0 = 1
        v0 = np.array([0] * self.shape)
        p0 = np.array([0] * self.shape)
        while True:
            rho = r2 @ r0
            beta = (rho * alpha0) / (rho0 * omega0)
            p = r0 + beta * (p0 - omega0 * v0)
            v = self.matrix @ p
            alpha = rho / (r2 @ v)
            s = r0 - alpha * v
            t = self.matrix @ s
            omega = (t @ s) / (t @ t)
            x = x0 + omega * s + alpha * p
            r = s - omega * t
            self.k += 1
            if norm(r) < self.eps:
                break
            r0 = r
            rho0 = rho
            alpha0 = alpha
            omega0 = omega
            v0 = v
            p0 = p
            x0 = x
        return x

    def print_solution(self):
        start = time()
        x = self.solve()
        end = time()
        start2 = time()
        x2 = bicgstab(self.matrix, self.b, tol=1e-5, x0=self.x0)[0]
        end2 = time()
        with open(self.output, 'w') as f:
            f.write('My solve:\n')
            f.write(f'{x.round(5)}\n')
            f.write(f'EPS = {self.eps}\n')
            f.write(f'Count of iterations = {self.k}\n')
            f.write(f'Mean = {np.mean(x)}\n')
            f.write(f'Time = {round(end - start, 5)} sec\n')
            f.write('\nNumPy solve:\n')
            f.write(f'{x2.round(5)}\n')
            f.write(f'Mean = {np.mean(x2)}\n')
            f.write(f'Time = {round(end2 - start2, 5)} sec\n')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', required=True, help='Input file')
    parser.add_argument('--output', required=True, help='Output file')
    parser.add_argument('--log', help='Log file')
    parser.add_argument('--eps', type=float, help='Epsilon')
    parser.add_argument('--diag', help='Matrix is diagonal?', \
                        action='store_true')
    args = parser.parse_args()

    matrix, b = get_matrix(args.input, args.diag)

    kek = spilu(matrix)

    print(kek)

    # solver = BiCGStab(matrix, b, output_file=args.output,
                      # log_file=args.log)
    # solver.print_solution()

if __name__ == "__main__":
    main()
