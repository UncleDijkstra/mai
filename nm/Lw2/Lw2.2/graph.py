import matplotlib.pyplot as plt
import numpy as np


def f1(x):
    return 8 / (x**2 + 4)


def f2(x):
    return (4 - (x - 1)**2)**0.5 + 1


def main():
    x = np.linspace(-5, 5, 10000)
    y = [f1(i) for i in x]
    y1 = [f2(i) for i in x]
    y2 = [-f2(i) + 2 for i in x]

    fig, ax = plt.subplots()
    ax.axhline(y=0, color='k')
    ax.axvline(x=0, color='k')

    plt.plot(x, y, color='b')
    plt.plot(x, y1, color='g')
    plt.plot(x, y2, color='g')
    plt.grid(True)
    plt.savefig('pic')

if __name__ == "__main__":
    main()
