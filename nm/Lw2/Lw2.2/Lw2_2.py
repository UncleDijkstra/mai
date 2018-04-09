import argparse
import numpy as np
from numpy.linalg import norm, solve, det
from itertools import product


class Solver:
    def __init__(self, eps, output_name, log_name):
        self.eps = eps
        self.out_file = output_name
        self.log_file = log_name
        if self.log_file:
            open(self.log_file, 'w').close()
        self.area = ((2.5, 3.25), (0.5, 0.75))
        self.x0 = [2.5, 0.5]
        self.k_iter = 0
        self.k_newton = 0
        self.lmbd = self.calc_lambda()
        self.q = self.calc_q()
        self.iter_x = self.iter_method()
        self.newtons_x = self.newtons_method()

    @staticmethod
    def f1(x1, x2):
        return (x1**2 + 4) * x2 - 8

    @staticmethod
    def f2(x1, x2):
        return (x1 - 1)**2 + (x2 - 1)**2 - 4

    @staticmethod
    def f11(x1, x2):
        return 2 * x1 * x2

    @staticmethod
    def f12(x1):
        return x1**2 + 4

    @staticmethod
    def f21(x1):
        return 2 * x1 - 2

    @staticmethod
    def f22(x2):
        return 2 * x2 - 2

    def phi1(self, x1, x2):
        return x1 - (self.f1(x1, x2) * self.lmbd[0, 0] + self.f2(x1, x2) *
                     self.lmbd[0, 1])

    def phi2(self, x1, x2):
        return x2 - (self.f1(x1, x2) * self.lmbd[1, 0] + self.f2(x1, x2) *
                     self.lmbd[1, 1])

    def phi11(self, x1, x2):
        return 1 - (self.f11(x1, x2) * self.lmbd[0, 0] + self.f21(x1) *
                    self.lmbd[0, 1])

    def phi12(self, x1, x2):
        return -(self.f12(x1) * self.lmbd[0, 0] + self.f22(x2) *
                 self.lmbd[0, 1])

    def phi21(self, x1, x2):
        return -(self.f11(x1, x2) * self.lmbd[1, 0] + self.f21(x1) *
                 self.lmbd[1, 1])

    def phi22(self, x1, x2):
        return 1 - (self.f12(x1) * self.lmbd[1, 0] + self.f22(x2) *
                    self.lmbd[1, 1])

    def phi_derivative(self, x):
        return np.array([[self.phi11(*x), self.phi12(*x)],
                        [self.phi21(*x), self.phi22(*x)]])

    def j(self, x1, x2):
        return [[self.f11(x1, x2), self.f12(x1)], [self.f21(x1), self.f22(x2)]]

    def calc_lambda(self):
        shape = len(self.area)
        current_j = self.j(*self.x0)
        inv_j = np.array([solve(current_j, i) for i in np.eye(shape)])
        return np.transpose(inv_j)

    def calc_q(self):
        x1 = np.linspace(self.area[0][0], self.area[0][1], 100)
        x2 = np.linspace(self.area[1][0], self.area[1][1], 100)
        points = list(product(x1, x2))
        vals = [norm(self.phi_derivative(point), np.inf) for point in points]
        q = np.max(vals)
        return q

    def iter_method(self):
        x_old = self.x0
        if self.log_file:
            with open(self.log_file, 'a') as fl:
                fl.write(f'Iter:\nx{self.k_iter} = {x_old}\n')
        while True:
            self.k_iter += 1
            x_new = np.array([self.phi1(*x_old), self.phi2(*x_old)])
            if self.log_file:
                with open(self.log_file, 'a') as fl:
                    fl.write(f'x{self.k_iter} = {x_new}\n')
            if norm(x_new - x_old, np.inf) * self.q / (1 - self.q) <= self.eps:
                return x_new
            else:
                x_old = x_new

    def newtons_method(self):
        shape = len(self.area)
        x_old = self.x0
        if self.log_file:
            with open(self.log_file, 'a') as fl:
                fl.write(f'Newton\'s:\nx{self.k_iter} = {x_old}\n')
        while True:
            current_j = self.j(*x_old)
            if det(current_j) == 0:
                if self.log_file:
                    with open(self.log_file, 'a') as fl:
                        fl.write(f'Error: detJ({self.k_newton} == 0)\n')
                exit(-1)
            self.k_newton += 1
            inv_j = np.array([solve(current_j, i) for i in np.eye(shape)])
            x_new = x_old - np.transpose(inv_j) @ np.array([self.f1(*x_old),
                                                            self.f2(*x_old)])
            if self.log_file:
                with open(self.log_file, 'a') as fl:
                    fl.write(f'x{self.k_newton} = {x_new}\n')
            if norm(x_new - x_old, np.inf) <= self.eps:
                return x_new
            else:
                x_old = x_new

    def print_solution(self):
        if self.log_file:
            with open(self.log_file, 'a') as f_log:
                f_log.write(f'q = {self.q}\n')
                f_log.write(f'Lambda:\n{self.lmbd}\n')
        with open(self.out_file, 'w') as f_out:
            f_out.write(f'EPS = {self.eps}\n')
            f_out.write(f'Iter: x = {self.iter_x}\n')
            f_out.write(f'Steps = {self.k_iter}\n')
            f_out.write(f'Newton: x = {self.newtons_x}\n')
            f_out.write(f'Steps = {self.k_newton}\n')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--eps', type=float, required=True, help='Accuracy')
    parser.add_argument('--output', required=True, help='File for answer')
    parser.add_argument('--log', help='Logging')
    args = parser.parse_args()

    sol = Solver(args.eps, args.output, args.log)
    sol.print_solution()

if __name__ == "__main__":
    main()
