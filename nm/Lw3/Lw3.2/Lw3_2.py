import argparse
import numpy as np
import matplotlib.pyplot as plt


def tma(matrix, d, shape):
    a, b, c = zip(*matrix)
    p = [-c[0] / b[0]]
    q = [d[0] / b[0]]
    x = [0] * (shape + 1)
    for i in range(1, shape):
        p.append(-c[i] / (b[i] + a[i] * p[i - 1]))
        q.append((d[i] - a[i] * q[i - 1]) / (b[i] + a[i] * p[i - 1]))
    for i in reversed(range(shape)):
        x[i] = p[i] * x[i + 1] + q[i]
    return x[:-1]


def spline(x, y):
    size = len(x)
    h = [x[i] - x[i - 1] for i in range(1, size)]
    mtrx = [[0, 2 * (h[0] + h[1]), h[1]]]
    b = [3 * ((y[2] - y[1]) / h[1] - (y[1] - y[0]) / h[0])]
    for i in range(1, size - 3):
        tmp = [h[i], 2 * (h[i] + h[i + 1]), h[i + 1]]
        mtrx.append(tmp)
        b.append(3 * ((y[i + 2] - y[i + 1]) / h[i + 1] - (y[i + 1] - y[i]) / h[i]))
    mtrx.append([h[-2], 2 * (h[-2] + h[-1]), 0])
    b.append(3 * ((y[-1] - y[-2]) / h[-1] - (y[-2] - y[-3]) / h[-2]))
    c = tma(mtrx, b, size - 2)
    a = []
    b = []
    d = []
    c.insert(0, 0)
    for i in range(1, size):
        a.append(y[i - 1])
        if i < size - 1:
            d.append((c[i] - c[i - 1]) / (3 * h[i - 1]))
            b.append((y[i] - y[i - 1]) / h[i - 1] -
                     h[i - 1] * (c[i] + 2 * c[i - 1]) / 3)
    b.append((y[-1] - y[-2]) / h[-1] - 2 * h[-1] * c[-1] / 3)
    d.append(-c[-1] / (3 * h[-1]))
    return a, b, c, d


def get_points(file_name):
    with open(file_name) as f:
        x = [float(num) for num in f.readline().split()]
        y = [float(num) for num in f.readline().split()]
        x_test = float(f.readline())
    return x, y, x_test


def polyval(x0, x, k, coef):
    a, b, c, d = coef
    tmp = (x0 - x[k])
    return a[k] + b[k] * tmp + c[k] * tmp**2 + d[k] * tmp**3


def pol(x, x_test, coef):
    k = 0
    for i, j in zip(x, x[1:]):
        if i <= x_test <= j:
            break
        k += 1
    return polyval(x_test, x, k, coef)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', required=True, help='Input test file')
    parser.add_argument('--output', required=True, help='File for answer')
    args = parser.parse_args()

    x, y, x_test = get_points(args.input)

    '''
    Test Runge's phenomenon
    f = lambda x: 1 / (1 + 25*x**2)
    x_test = 1
    x = list(range(6))
    y = [f(i) for i in x]
    # '''

    coef = spline(x, y)

    x1 = np.linspace(x[0], x[-1], 50)
    y1 = [pol(x, i, coef) for i in x1]

    plt.plot(x1, y1, color='b')
    plt.scatter(x, y, color='r')
    plt.show()

    res = pol(x, x_test, coef)

    for i in x:
        print(pol(x, i, coef))

    with open(args.output, 'w') as f:
        f.write(f'x = {x}\ny = {y}\n\n')
        f.write(f'a = {coef[0]}\nb = {coef[1]}\nc = {coef[2]}\nd = {coef[3]}\n')
        f.write(f'\nf({x_test}) = {round(res, 4)}\n')

if __name__ == "__main__":
    main()
