#include <bits/stdc++.h>
#include "matrix.h"
using namespace std;

char guide[] = 
"NAME\n\
        matrix_calculator - a demo launcher of a simple matrix library.\n\
OPTIONS\n\
        -A\n\
            Reads two matrices from stdin, prints their sum to stdout.\n\
        -S\n\
            Reads two matrices from stdin, prints their difference to stdout.\n\
        -M\n\
            Reads two matrices from stdin, prints their outer product to stdout.\n\
        -m\n\
            Reads a matrix and a number from stdin, prints their product to stdout.\n\
            NOTE: The matrix MUST be in front of the number.\n\
        -I\n\
            Reads a matrix from stdin, prints its inverse matrix to stdout.\n\
        -T\n\
            Reads a matrix from stdin, prints its tanspose matrix to stdout.\n\
        -D\n\
            Reads a matrix from stdin, prints its determinant to stdout.\n\
FORMAT\n\
        matrix:\n\
        row_size column_size\n\
        ...(matrix here)\n";


void print_guide() {
    cout << guide;
    //system("pause");
    exit(EXIT_FAILURE);
}

bool cmd(char opt[]) {
    if (opt[0] != '-' || strlen(opt) != 2) {
        return false;
    }
    Matrix a, b;
    int k;

    switch(opt[1]) {
        case 'A' :
            a.read();
            b.read();
            (a + b).print();
            return true;
        case 'S' :
            a.read();
            b.read();
            (a - b).print();
            return true;
        case 'M' :
            a.read();
            b.read();
            (a * b).print();
            return true;
        case 'm' :
            a.read();
            if (!(cin >> k)) {
                cerr << "Invalid input.";
                exit(EXIT_FAILURE);
            }
            (a * k).print();
            return true;
        case 'I' :
            a.read();
            a.inverse().print();
            return true;
        case 'T' :
            a.read();
            a.transpose().print();
            return true;
        case 'D' :
            a.read();
            cout << round(a.determinant() / _MATRIX_EPS / 10) * _MATRIX_EPS * 10 << endl;
            //cout << a.determinant() << endl;
            return true;
        default :
            return false;
    }
    return false;
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    if (argc == 2 && cmd(argv[1])){ 
        //system("pause");
    }
    else {
        print_guide();
    }
    return 0;
}
