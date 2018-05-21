import numpy as np


def f(x):
    return x / (2 * x + 5)


def simpson(a, b, h, n):
    s = f(a) + f(b)
    for i in range(1, n, 2):
        s += 4 * f(a + i * h)
    for i in range(2, n-1, 2):
        s += 2 * f(a + i * h)
    return s * h / 3


def main():
    a = -1
    b = 1
    h1 = 0.5
    h2 = 0.25

    x1 = np.linspace(a, b, int((b - a) / h1 + 1))
    x2 = np.linspace(a, b, int((b - a) / h2 + 1))

    y_trap1 = [f(i) for i in x1]
    y_trap2 = [f(i) for i in x2]

    rect1 = h1 * sum([f((i + j) / 2) for i, j in zip(x1, x1[1:])])
    rect2 = h2 * sum([f((i + j) / 2) for i, j in zip(x2, x2[1:])])

    trap1 = h1/2 * sum([i + j for i, j in zip(y_trap1[1:], y_trap1)])
    trap2 = h2/2 * sum([i + j for i, j in zip(y_trap2[1:], y_trap2)])

    simps1 = simpson(a, b, h1, int((b - a) / h1))
    simps2 = simpson(a, b, h2, int((b - a) / h2))

    print(f'Method of rectangles = {rect1}\tStep = {h1}')
    print(f'Method of rectangles = {rect2}\tStep = {h2}')
    print(f'Error: {round(abs(rect1 - rect2) / 3, 5)}')
    print('='*10)
    print(f'Method of trapeziums = {trap1}\tStep = {h1}')
    print(f'Method of trapeziums = {trap2}\tStep = {h2}')
    print(f'Error: {round(abs(trap1 - trap2) / 3, 5)}')
    print('='*10)
    print(f"Simpson's method  = {simps1}\tStep = {h1}")
    print(f"Simpson's method  = {simps2}\tStep = {h2}")
    print(f'Error: {round(abs(simps1 - simps2) / 15, 5)}')

if __name__ == "__main__":
    main()
