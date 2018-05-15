import argparse


def get_points(file_name):
    with open(file_name) as f:
        x = [float(num) for num in f.readline().split()]
        y = [float(num) for num in f.readline().split()]
        x_test = float(f.readline())
    return x, y, x_test


def first_der(x, y, x0, k):
    num1 = (y[k + 1] - y[k]) / (x[k + 1] - x[k])
    num2 = (y[k + 2] - y[k + 1]) / (x[k + 2] - x[k + 1]) - num1
    num2 = num2 / (x[k + 2] - x[k])
    return num1 + num2 * (2 * x0 - x[k] - x[k + 1])


def second_der(x, y, k):
    num1 = (y[k + 2] - y[k + 1]) / (x[k + 2] - x[k + 1])
    num2 = (y[k + 1] - y[k]) / (x[k + 1] - x[k])
    return 2 * (num1 - num2) / (x[k + 2] - x[k])


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', required=True, help='Input test file')
    parser.add_argument('--output', required=True, help='File for answer')
    args = parser.parse_args()

    x, y, x_test = get_points(args.input)

    k = 0
    for i, j in zip(x, x[1:]):
        if i <= x_test <= j:
            break
        k += 1

    res1 = first_der(x, y, x_test, k)
    res2 = second_der(x, y, k)
    with open(args.output, 'w') as f:
        f.write(f"f'({x_test}) = {round(res1, 5)}\n")
        f.write(f"f''({x_test}) = {round(res2, 5)}\n")

if __name__ == "__main__":
    main()
