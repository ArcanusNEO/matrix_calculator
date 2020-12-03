#include <cstring>
#include <cmath>
#include <iostream>
#include "matrix.h"

Matrix::Matrix(unsigned row, unsigned col, double num) {
    if (row > maxSize_ || col > maxSize_) {
        std::cerr << "Row size or col size is too big.";
        std::exit(EXIT_FAILURE);
    }
    unsigned i;

    row_ = row;
    col_ = col;
    a = new double[row_ + 1][maxSize_ + 1]();
    if (std::fabs(num) > _MATRIX_EPS) {
        for (i = 1; i <= row_ && i <= col_; ++i) {
            a[i][i] = num;
        }
    }
}

Matrix::Matrix(const Matrix& y) {
    row_ = y.row_;
    col_ = y.col_;
    a = new double[row_ + 1][maxSize_ + 1];
    std::memcpy(a, y.a, (row_ + 1) * (maxSize_ + 1) * sizeof(double));
}

Matrix::~Matrix() {
    delete[] a;
    a = NULL;
}

Matrix& Matrix::operator =(const Matrix& y) {
    if (row_ != y.row_) {
        if (a != NULL) {
            delete[] a;
        }
        a = new double[y.row_ + 1][maxSize_ + 1];
    }
    row_ = y.row_;
    col_ = y.col_; 
    std::memcpy(a, y.a, (row_ + 1) * (maxSize_ + 1) * sizeof(double));
    return *this;
}

Matrix Matrix::operator *(double k) const {
    Matrix tmp(*this);
    unsigned i, j;

    for (i = 1; i <= row_; ++i) {
        for (j = 1; j <= col_; ++j) {
            tmp.a[i][j] *= k;
        }
    }
    return tmp;
}

Matrix Matrix::operator +(const Matrix& y) const {
    if (row_ != y.row_ || col_ != y.col_) {
        std::cerr << "The matrices do not match.";
        std::exit(EXIT_FAILURE);
    }
    Matrix tmp(*this);
    unsigned i, j;

    for (i = 1; i <= row_; ++i) {
        for (j = 1; j <= col_; ++j) {
            tmp.a[i][j] += y.a[i][j];
        }
    }
    return tmp;
}

Matrix Matrix::operator -(const Matrix& y) const {
    if (row_ != y.row_ || col_ != y.col_) {
        std::cerr << "The matrices do not match.";
        std::exit(EXIT_FAILURE);
    }
    Matrix tmp(*this);
    unsigned i, j;

    for (i = 1; i <= row_; ++i) {
        for (j = 1; j <= col_; ++j) {
            tmp.a[i][j] -= y.a[i][j];
        }
    }
    return tmp;
}

Matrix Matrix::operator *(const Matrix& y) const {
    if (col_ != y.row_) {
        std::cerr << "The matrices do not match.";
        std::exit(EXIT_FAILURE);
    }
    Matrix tmp(row_, y.col_);
    unsigned i, j, k;

    for (i = 1; i <= tmp.row_; ++i) {
        for (j = 1; j <= tmp.col_; ++j) {
            for (k = 1; k <= col_ ; ++k) {
                tmp.a[i][j] += a[i][k] * y.a[k][j];
            }
        }
    }
    return tmp;
}

double Matrix::determinant() const {
    if (row_ != col_) {
        std::cerr << "The matrix is not a square matrix.";
        std::exit(EXIT_FAILURE);
    }
    unsigned i, j, k;
    double rate, res = 1.0;
    Matrix tmp(*this);

    for (i = 1; i <= row_; ++i) {
        if (std::fabs(tmp.a[i][i]) <= _MATRIX_EPS) {
            for (j = i + 1; j <= row_; ++j) {
                if (std::fabs(tmp.a[j][i]) > _MATRIX_EPS) {
                    break;
                }
            }
            if (j > row_) {
                return 0;
            }
            for (k = i; k <= col_; ++k) {
                std::swap(tmp.a[i][k], tmp.a[j][k]);
            }
        }
        for (j = i + 1; j <= row_; ++j) {
            rate = tmp.a[j][i] / tmp.a[i][i];
            for (k = i; k <= col_; ++k) {
                tmp.a[j][k] -= tmp.a[i][k] * rate;
            }
        }
    }
    for (i = 1; i <= row_; ++i) {
        res *= tmp.a[i][i];
    }
    return res;
}

Matrix& Matrix::self_inverse() {
    if (row_ != col_) {
        std::cerr << "The matrix is not a square matrix.";
        std::exit(EXIT_FAILURE);
    }
    Matrix tmp(row_, col_, 1.0);
    unsigned i, j, k;
    double rate;

    for (i = 1; i <= row_; ++i) {
        if (std::fabs(a[i][i]) <= _MATRIX_EPS) {
            for (j = i + 1; j <= row_; ++j) {
                if (std::fabs(a[j][i]) > _MATRIX_EPS) {
                    break;
                }
            }
            if (j > row_) {
                std::cerr << "The matrix is a singular matrix.";
                std::exit(EXIT_FAILURE);
            }
            for (k = 1; k <= col_; ++k) {
                std::swap(a[i][k], a[j][k]);
                std::swap(tmp.a[i][k], tmp.a[j][k]);
            }
        }
        rate = a[i][i];
        for (j = 1; j <= col_; ++j) {
            a[i][j] /= rate;
            tmp.a[i][j] /= rate;
        }
        for (j = i + 1; j <= row_; ++j) {
            rate = a[j][i];
            for (k = 1; k <= col_; ++k) {
                a[j][k] -= a[i][k] * rate;
                tmp.a[j][k] -= tmp.a[i][k] * rate;
            }
        }
    }
    for (i = 1; i <= row_; ++i) {
        for (j = 1; j <= row_ - i; ++j) {
            rate = a[j][col_ + 1 - i];
            for (k = 1; k <= col_; ++k) {
                tmp.a[j][k] -= tmp.a[row_ + 1 - i][k] * rate;
            }
        }
    }
    for (i = 1; i <= row_; ++i) {
        for (j = 1; j <= col_; ++j) {
            a[i][j] = tmp.a[i][j];
        }
    }
    return *this;
}

Matrix Matrix::inverse() const {
    Matrix tmp(*this);
    tmp.self_inverse();
    return tmp;
}

Matrix Matrix::transpose() const {
    unsigned i, j;
    Matrix tmp(col_, row_);

    for (i = 1; i <= row_; ++i) {
        for (j = 1; j <= col_; ++j) {
            tmp.a[j][i] = a[i][j];
        }
    }
    return tmp;
}

void Matrix::print() const {
    unsigned i, j;

    std::cout << row_ << " " << col_ << std::endl;
    for (i = 1; i <= row_; ++i) {
        for (j = 1; j <= col_; ++j) {
            std::cout << std::round(a[i][j] /_MATRIX_EPS / 10) * _MATRIX_EPS * 10 << " ";
            //std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::reset(unsigned row, unsigned col, double num) {
    if (row > maxSize_ || col > maxSize_) {
        std::cerr << "Row size or col size is too big.";
        std::exit(EXIT_FAILURE);
    }
    unsigned i;

    if (row != row_) {
        if (a != NULL) {
            delete[] a;
        }
        a = new double[row + 1][maxSize_ + 1]();
    }
    else {
        std::memset(a, 0, (row + 1) * (maxSize_ + 1) * sizeof(double));
    }
    row_ = row;
    col_ = col;
    if (std::fabs(num) > _MATRIX_EPS) {
        for (i = 1; i <= row_ && i <= col_; ++i) {
            a[i][i] = num;
        }
    }
}

void Matrix::read() {
    unsigned row, col, i, j;
    if (!(std::cin >> row >> col)) {
        std::cerr << "Invalid Input.";
        std::exit(EXIT_FAILURE);
    }
    this -> reset(row, col);
    for (i = 1; i <= row_; ++i) {
        for (j = 1; j <= col_; ++j) {
            if (!(std::cin >> a[i][j])) {
                std::cerr << "Invalid Input.";
                std::exit(EXIT_FAILURE);
            }
        }
    }
}
