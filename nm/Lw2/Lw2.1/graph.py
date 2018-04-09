import matplotlib.pyplot as plt
import numpy as np
import Lw2_1


def draw(x, y, name):
    plt.plot(x, y)
    plt.grid(True)
    plt.savefig(name)
    plt.cla()


def main():
    a, b = (1, 3)

    x = np.linspace(-5, 5, 1000)
    y = [Lw2_1.Solver.f(i) for i in x]
    draw(x, y, 'func')

    x = np.linspace(a, b, 100)
    y = [Lw2_1.Solver.f_derivative(i) for i in x]
    draw(x, y, 'first_derv_of_func')

    y = [Lw2_1.Solver.f_2derivative(i) for i in x]
    draw(x, y, 'second_derv_of_func')


if __name__ == "__main__":
    main()
