import argparse
import numpy as np


class Solver:
    def __init__(self, eps, output_name, log_name):
        self.eps = eps
        self.out_file = output_name
        self.log_file = log_name
        if self.log_file:
            open(self.log_file, 'w').close()
        self.area = (1, 3)
        self.x0 = 1.25
        self.lmbd = self.calc_lambda()
        self.q = self.calc_q()
        self.k_iter = 0
        self.k_newton = 0
        self.check()
        self.iter_x = self.iter_method()
        self.newtons_x = self.newtons_method()

    def check(self):
        with open(self.log_file, 'a') as f_log:
            f_log.write(f'q = {self.q}\n')
            f_log.write(f'lambda = {self.lmbd}\n')
            x = np.linspace(self.area[0], self.area[1], 10000)
            y = [self.phi_derivative(i) for i in x]
            if all([i < 1 for i in y]):
                f_log.write('phi\' < 1\n')
            else:
                f_log.write('phi\' >= 1\n')
            if self.q < 1:
                f_log.write('q < 1\n')
            else:
                f_log.write('q >= 1\n')

    @staticmethod
    def f(x):
        return 2**x - x**2 - 0.5

    def phi(self, x):
        return x - self.lmbd * self.f(x)

    def phi_derivative(self, x):
        return 1 - self.lmbd * self.f_derivative(x)

    @staticmethod
    def f_derivative(x):
        return 2**x * np.log(2) - 2*x

    @staticmethod
    def f_2derivative(x):
        return 2**x * np.log(2)**2 + 2**x * 0.5 - 2

    def calc_q(self):
        x = np.linspace(self.area[0], self.area[1], 10000)
        y = [abs(self.phi_derivative(i)) for i in x]
        q = np.max(y)
        return q

    def calc_lambda(self):
        flag = None
        x = np.linspace(self.area[0], self.area[1], 10000)
        y = [self.f_derivative(i) for i in x]

        if all([np.sign(i) == -1 for i in y]):
            flag = -1
        elif all([np.sign(i) == 1 for i in y]):
            flag = 1
        else:
            if self.log_file:
                with open(self.log_file, 'a') as fl:
                    fl.write('Error: Derivative change sign\n')
            exit(-1)

        y = [abs(self.f_derivative(i)) for i in x]
        return flag / np.max(y)

    def iter_method(self):
        x_old = self.x0
        if self.log_file:
            with open(self.log_file, 'a') as fl:
                fl.write(f'Iter:\nx{self.k_iter} = {x_old}\n')
        while True:
            self.k_iter += 1
            x_new = self.phi(x_old)
            if self.log_file:
                with open(self.log_file, 'a') as fl:
                    fl.write(f'x{self.k_iter} = {x_new}\n')
            if abs(x_new - x_old) * self.q / (1 - self.q) < self.eps:
                return x_new
            else:
                x_old = x_new

    def newtons_method(self):
        x_old = self.x0
        if self.log_file:
            with open(self.log_file, 'a') as fl:
                fl.write(f'Newton\'s:\nx{self.k_iter} = {x_old}\n')
        while True:
            self.k_newton += 1
            x_new = x_old - self.f(x_old) / self.f_derivative(x_old)
            if self.log_file:
                with open(self.log_file, 'a') as fl:
                    fl.write(f'x{self.k_newton} = {x_new}\n')
            if abs(x_new - x_old) < self.eps:
                return x_new
            else:
                x_old = x_new

    def print_solution(self):
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
