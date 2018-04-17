import argparse
import numpy as np


def lagrange(points):
    def inner(x):
        cnt_points = len(points)
        l = []
        for i in range(cnt_points):
            l.append(np.prod([(x - points[j][0]) / (points[i][0] - points[j][0])
                              for j in range(cnt_points) if i != j]))
        return sum([points[idx][1] * i for idx, i in enumerate(l)])
    return inner


def newton(points):
    def inner(x):
        cnt_points = len(points)
        x_point, y_point = zip(*points)
        coef = [y_point[0]]
        for j, shift in zip(reversed(range(1, cnt_points)), range(cnt_points)):
            tmp = []
            for l, r in zip(range(j), range(1, j + 1)):
                num1 = y_point[l] - y_point[r]
                num2 = x_point[l] - x_point[r + shift]
                tmp.append(num1 / num2)
            y_point = tmp
            coef.append(y_point[0])

        res = 0
        for i in range(cnt_points):
            res += coef[i] * np.prod([x - x_point[j] for j in range(i)])
        return res
    return inner


def get_points(file_name):
    with open(file_name) as f:
        x = [float(num) * np.pi for num in f.readline().split()]
        points = [(i, np.sin(i)) for i in x]
        x_test = float(f.readline()) * np.pi
    return points, x_test


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', required=True, help='Input test file')
    parser.add_argument('--output', required=True, help='File for answer')
    args = parser.parse_args()

    points, x_test = get_points(args.input)
    lg = lagrange(points)
    nt = newton(points)

    with open(args.output, 'w') as f:
        tmp = round(x_test, 3)
        res1 = lg(tmp)
        res2 = nt(tmp)
        res3 = np.sin(tmp)
        eps1 = abs(res1 - res3)
        eps2 = abs(res2 - res3)
        f.write(f'Lagrange:\nL({tmp}) = {res1}\nEps = {round(eps1, 5)}\n')
        f.write(f'Newton:\nN({tmp}) = {res2}\nEps = {round(eps2, 5)}\n')
        f.write(f'Orig:\nSin({tmp}) = {res3}\n')

if __name__ == "__main__":
    main()
