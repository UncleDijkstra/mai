#include <iostream>
#include "Figure.h"
#include "Vector.h"
#include <memory>
#include <cstdlib>

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
    std::shared_ptr<Figure> tri;
    TMyVector <Figure> vector(5);
    do {
        menu();
        cin >> key;
        switch(key) {
            case 1:
                cout << "Enter sides of triangle, pls" << endl;
                cin >> a >> b >> c;
                tri = std::shared_ptr<Figure>(new Triangle(a, b ,c));
                vector.Push(tri);
                break;
            case 2:
                cout << "Enter sides of rectangle, pls" << endl;
                cin >> a >> b;
                tri = std::shared_ptr<Figure>(new Rectangle(a, b));
                vector.Push(tri);
                break;
            case 3:
                cout << "Enter sides of foursquare, pls" << endl;
                cin >> a;
                tri = std::shared_ptr<Figure>(new Foursquare(a));
                vector.Push(tri);
                break;
            case 4:
                cout << "Enter index of figure, pls" << endl;
                cin >> index;
                if(index >= vector.GetSize()) {
                    cout << "Figure not found" << endl;
                } else {
                        vector.Get(index);
                }
                break;
            case 5:
                if(vector.GetSize() > 0) {
                    vector.Delete();
                } else {
                    cout << "Figure not found" << endl;
                }
                break;
            case 6:
                vector.~TMyVector();
                key = 0;
                break;
            case 7:
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
    cout << "1)For add Triangle." << endl;
    cout << "2)For add Rectangle." << endl;
    cout << "3)For add Foursquare." << endl;
    cout << "4)For get figure." << endl;
    cout << "5)For delete figure." << endl;
    cout << "6)For delete all figures." << endl;
    cout << "7)Print vector." << endl;
    cout << "0)Exit" << endl;
}