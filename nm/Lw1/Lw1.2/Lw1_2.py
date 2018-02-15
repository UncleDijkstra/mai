import argparse
from copy import deepcopy
from numpy.linalg import solve
from pprint import pformat


def get_matrix(filename):
    with open(filename) as f:
        shape = int(f.readline())
        matrix = [[int(num) for num in line.split()]
                  for _, line in zip(range(shape), f)]
        matrix[0].insert(0, 0)
        matrix[-1].append(0)
        d = [int(num) for num in f.readline().split()]
        return shape, matrix, d


def tma(matrix, d, shape, fl):
    a, b, c = zip(*matrix)
    p = [-c[0] / b[0]]
    q = [d[0] / b[0]]
    x = [0] * (shape + 1)
    for i in range(1, shape):
        p.append(-c[i] / (b[i] + a[i] * p[i - 1]))
        q.append((d[i] - a[i] * q[i - 1]) / (b[i] + a[i] * p[i - 1]))
    for i in reversed(range(shape)):
        x[i] = p[i] * x[i + 1] + q[i]
    if fl:
        fl.write(f'a = {a}\nb = {b}\nc = {c}\nP = {p}\nQ = {q}\n')
        fl.write(f'x = {x[:-1]} (from n to 1)\n')
    return x[:-1]


def full_matrix(matrix):
    new_matrix = deepcopy(matrix)
    new_matrix[0].pop(0)
    new_matrix[-1].pop()
    return [[0] * (idx - 1) + line + [0] * (3 - idx)
            for idx, line in enumerate(new_matrix)]


def print_answer(x, fo):
    for idx, val in enumerate(x):
        fo.write(f'x{idx + 1} = {val:.2}\n')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', required=True, help='Input test file')
    parser.add_argument('--output', required=True, help='File for answer')
    parser.add_argument('--log', help='Logging')
    args = parser.parse_args()
    shape, matrix, d = get_matrix(args.input)
    fl = None
    fo = open(args.output, 'w')
    if args.log:
        fl = open(args.log, 'w')
        fl.write(f'Shape = {shape}\nMatrix:\n')
        fl.write(pformat(full_matrix(matrix)))
        fl.write(f'\nVector d = {d}\n')
    x = tma(matrix, d, shape, fl)
    fo.write('Answer:\n')
    print_answer(x, fo)
    fo.write('\nCheck by NumPy:\n')
    num_x = solve(full_matrix(matrix), d)
    print_answer(num_x, fo)
    if fl:
        fl.close()
    fo.close()

if __name__ == "__main__":
    main()
