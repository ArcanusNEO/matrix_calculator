#ifndef _MATRIX_H
#define _MATRIX_H
#define _MATRIX_EPS 1e-8

class Matrix {
    private:
        enum property_ {maxSize_ = 500};
        unsigned row_, col_;
        double (*a)[maxSize_ + 1];

    public:
        Matrix(unsigned row = 0, unsigned col = 0, double num = 0);
        Matrix(const Matrix& y);
        ~Matrix();

        Matrix operator +(const Matrix& y) const;
        Matrix operator -(const Matrix& y) const;
        Matrix operator *(const Matrix& y) const;
        Matrix operator *(double k) const;
        Matrix inverse() const;
        Matrix transpose() const;

        Matrix& operator =(const Matrix& y);
        Matrix& self_inverse();

        double determinant() const;

        double& operator ()(unsigned i, unsigned j) {
            if (i > row_ || j > col_ || !i || !j) {
                return a[0][0] = 0;
            }
            return a[i][j];
        }
        double operator ()(unsigned i, unsigned j) const{
            if (i > row_ || j > col_ || !i || !j) {
                return 0;
            }
            return a[i][j];
        }
        
        unsigned row_size() const {return row_;} 
        unsigned col_size() const {return col_;}

        void print() const;
        void read();
        void reset(unsigned row = 0, unsigned col = 0, double num = 0);
};

inline Matrix operator *(double k, const Matrix& x) {return x * k;}

#endif
