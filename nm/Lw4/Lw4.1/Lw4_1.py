import argparse
import numpy as np
from prettytable import PrettyTable


def foo(x, y, y1):
    return np.sin(3 * x) - y


def orig_foo(x):
    return np.cos(x) + 11/8 * np.sin(x) - np.sin(3*x)/8


def euler(f, xa, xb, ya, y1a, h):
    n = int((xb - xa) / h)
    x = xa
    y = ya
    x_res = [x]
    y_res = [y]
    y1 = y1a
    for i in range(n):
        y1 += h * f(x, y, y1)
        y += h * y1
        x += h
        x_res.append(x)
        y_res.append(y)
    return x_res, y_res


def runge_kutta(f, xa, xb, ya, y1a, h):
    n = int((xb - xa) / h)
    x = xa
    y = ya
    z = y1a
    x_res = [x]
    y_res = [y]
    z_res = [z]
    for i in range(1, n + 1):
        k1 = h * z
        l1 = h * f(x, y, z)
        k2 = h * (z + 0.5 * l1)
        l2 = h * f(x + 0.5 * h, y + 0.5 * k1, z + 0.5 * l1)
        k3 = h * (z + 0.5 * l2)
        l3 = h * f(x + 0.5 * h, y + 0.5 * k2,  z + 0.5 * l2)
        k4 = h * (z + l3)
        l4 = h * f(x + h, y + k3, z + l3)
        x = xa + i * h
        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6
        z += (l1 + 2 * l2 + 2 * l3 + l4) / 6
        x_res.append(x)
        y_res.append(y)
        z_res.append(z)
    return (x_res, y_res), z_res


def adams(f, x, y, h, n, z):
    z = z[:4] + [0] * (len(z) - 4)
    for i in range(3, n):
        z[i + 1] = z[i] + h/24 * (55*f(x[i], y[i], z[i]) - \
                             59*f(x[i - 1], y[i - 1], z[i - 1]) + \
                             37*f(x[i - 2], y[i - 2], z[i - 2]) - \
                             9*f(x[i - 3], y[i - 3], z[i - 3]))
        tmp = y[i] + h/24 * (55*z[i] - 59*z[i - 1] + \
                                  37*z[i - 2] - 9*z[i - 3])
        x.append(x[-1] + h)
        y.append(tmp)
    return x, y


def print_result_table(f, name, res, runge_y, p):
    f.write(f'\n{name}\n')
    table = PrettyTable(['X', 'Y', 'Accurate Y', '|Y - Accurate Y|',
                         'Runge eps'])
    for x, y, yr in zip(*res, runge_y):
        tmp = orig_foo(x)
        table.add_row([round(x, 2), round(y, 3), round(tmp, 3), abs(y - tmp),
                       abs(y - yr) / (2**p - 1)])
    f.write(f'\n{str(table)}\n')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--output', required=True, help='File for answer')
    parser.add_argument('--h', required=True, help='Step', type=float)
    args = parser.parse_args()

    a = 0
    b = 1
    y0 = 1
    y10 = 1
    step = args.h
    f = open(args.output, 'w')

    res1 = euler(foo, a, b, y0, y10, step)
    res1_half_h = euler(foo, a, b, y0, y10, step / 2)
    print_result_table(f, 'Euler', res1, res1_half_h[1], 1)

    res2, z = runge_kutta(foo, a, b, y0, y10, step)
    res2_half_h, z_half_h = runge_kutta(foo, a, b, y0, y10, step / 2)
    print_result_table(f, 'Runge-Kutta', res2, res2_half_h[1], 4)

    res3 = adams(foo, res2[0][:4], res2[1][:4], step, int((b - a) / step), z)
    res3_half_h = adams(foo, res2[0][:4], res2[1][:4], step / 2,
                        int((b - a) / step), z_half_h)
    print_result_table(f, 'Adams', res3, res3_half_h[1], 4)

    f.close()

if __name__ == "__main__":
    main()
