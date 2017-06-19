#include <iostream>
#include "Vector.h"
#include "Triangle.h"

using std::cin;
using std::cout;
using std::endl;

void menu();

int main() {
    int key;
    int index;
    int a = 0;
    int b = 0;
    int c = 0;
    Triangle tmp; // через объект
    // Triangle *tmp;
    TVector vector(5);
    do {
        menu();
        cin >> key;
        switch(key) {
            case 1:
                cout << "Enter sides of triangle, pls" << endl;
                // tmp = new Triangle(cin); // через указатель
                cin >> a >> b >> c;
                tmp.SetSides(a, b, c);
                vector.Push(tmp);
                break;
            case 2:
                cout << "Enter index of triangle, pls" << endl;
                cin >> index;
                if(index >= vector.GetSize()) {
                    cout << "Triangle not found" << endl;
                } else {
                    cout << vector.Get(index) << endl;
                    cout << vector.Get(index).Square() << endl;
                }
                break;
            case 3:
                cout << "Enter index, pls" << endl;
                cin >> index;
                vector.Delete(index);
                break;
            case 4:
                vector.~TVector();
                key = 0;
                break;
            case 5:
                cout << vector;
                break;
            case 0:
                break;
            default:
                cout << "Unknown comman" << endl;
                break;
        }
    } while(key);
    return 0;
}

void menu() {
    cout << "Enter:" << endl;
    cout << "1)For add triangle." << endl;
    cout << "2)For get triangle and his square." << endl;
    cout << "3)For delete triangle." << endl;
    cout << "4)For delete all triangles." << endl;
    cout << "5)Print all triangles." << endl;
    cout << "0)Exit" << endl;
}