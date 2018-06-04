import argparse


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--shape', required=True, type=int,
                        help='Shape of matrix')
    parser.add_argument('--output', required=True, help='Output file')
    args = parser.parse_args()

    if args.shape < 3:
        exit()

    with open(args.output, 'w') as f:
        f.write(f'{args.shape}\n')
        f.write('-2 1\n')
        for _ in range(args.shape - 2):
            f.write('1 -2 1\n')
        f.write('1 -2\n')
        f.write('-1 ')
        for _ in range(args.shape - 2):
            f.write('0 ')
        f.write('-1\n')

if __name__ == "__main__":
    main()
