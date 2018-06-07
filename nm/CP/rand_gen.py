import argparse
import numpy as np
from random import randint
from scipy.sparse import rand


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--shape', required=True, type=int,
                        help='Shape of matrix')
    parser.add_argument('--output', required=True, help='Output file')
    args = parser.parse_args()

    if args.shape < 3:
        exit()
    shape = args.shape

    matrix = rand(shape, shape, density=0.4, random_state=randint(112, 154))

    with open(args.output, 'w') as f:
        f.write(f'{shape}\n')
        for i in matrix.toarray().round(3):
            for j in i:
                f.write(f'{j} ')
            f.write('\n')
        d = np.random.randint(5, 53, shape)
        for i in d:
            f.write(f'{i} ')
        f.write('\n')


if __name__ == "__main__":
    main()
