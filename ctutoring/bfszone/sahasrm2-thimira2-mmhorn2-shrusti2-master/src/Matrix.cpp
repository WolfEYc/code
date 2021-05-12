#include "Matrix.h"
namespace fin {


    Matrix::Matrix() {
        rows_ = 0;
        cols_ = 0;
        matrix_ = NULL;
    }


    Matrix::Matrix(const int rows, const int cols) {
        rows_ = (uint32_t)rows;
        cols_ = (uint32_t)cols;
        matrix_ = new double* [rows];
        for (unsigned i = 0; i < rows_; i++) {
            matrix_[i] = new double[cols];
            for (unsigned j = 0; j < cols_; j++) {
                matrix_[i][j] = 0;
            }
        }
    }

    Matrix::Matrix(const int rows, const int cols, double val) {
        rows_ = (uint32_t)rows;
        cols_ = (uint32_t)cols;
        matrix_ = new double* [rows];
        for (unsigned i = 0; i < rows_; i++) {
            matrix_[i] = new double[cols];
            for (unsigned j = 0; j < cols_; j++) {
                matrix_[i][j] = val;
            }
        }
    }


    Matrix::~Matrix() {
        _destroy();
    }

    template<size_t rows, size_t cols>
    Matrix::Matrix(double(&matrix)[rows][cols]) {
        if (!matrix) {
            std::cout << "Cannot construct matrix from NULL" << std::endl;
            exit(0);
        }
        rows_ = (uint32_t)sizeof(matrix) / sizeof(matrix[0]);
        cols_ = (uint32_t)sizeof(matrix[0]) / sizeof(matrix[0][0]);

        matrix_ = new double* [rows_];
        for (unsigned i = 0; i < rows_; i++) {
            matrix_[i] = new double[cols_];
            for (unsigned j = 0; j < cols_; j++) {
                matrix_[i][j] = matrix[i][j];
            }
        }
    }


    Matrix::Matrix(const Matrix& other) {
        _copy(other);
    }


    void Matrix::_copy(const Matrix& other) {
        rows_ = other.rows_;
        cols_ = other.cols_;

        if (other.matrix_) {
            matrix_ = new double* [rows_];
            for (unsigned i = 0; i < rows_; i++) {
                matrix_[i] = new double[cols_];
                for (unsigned j = 0; j < cols_; j++)
                    matrix_[i][j] = other.matrix_[i][j];
            }
        }
        else {
            matrix_ = NULL;
        }
    }


    void Matrix::_destroy() {
        if (matrix_) {
            for (unsigned i = 0; i < rows_; i++)
                delete[] matrix_[i];
            delete[] matrix_;
        }
    }


    int Matrix::getRows() { return rows_; }


    int Matrix::getCols() { return cols_; }


    bool Matrix::empty() {
        return (rows_ == 0 || cols_ == 0);
    }


    Matrix Matrix::operator=(const Matrix& other) {
        _copy(other);
        return *this;
    }



    double* Matrix::operator[](int index) {
        if (!matrix_ || (unsigned)index >= rows_) {
            std::cout << "ERROR: Index is out of bounds" << std::endl;
            exit(0);
        }

        return matrix_[index];
    }


    bool Matrix::operator==(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) return false;

        for (unsigned i = 0; i < rows_; i++) {
            for (unsigned j = 0; j < cols_; j++) {
                if (matrix_[i][j] != other.matrix_[i][j])
                    return false;
            }
        }

        return true;
    }


    Matrix Matrix::operator+=(const int c) {
        if (!matrix_) {
            std::cout << "ERROR: cannot add to empty matrix" << std::endl;
        }

        for (unsigned i = 0; i < rows_; i++) {
            for (unsigned j = 0; j < cols_; j++) {
                matrix_[i][j] = (matrix_[i][j]) ? matrix_[i][j] + c : c;
            }
        }

        return *this;
    }


    Matrix Matrix::operator+=(const Matrix m) {
        if (!matrix_ || !m.matrix_ || (rows_ != m.rows_ && cols_ != m.cols_)) {
            std::cout << "ERROR: cannot add mismatched matrices" << std::endl;
        }
        for (unsigned i = 0; i < rows_; i++) {
            for (unsigned j = 0; j < cols_; j++) {
                matrix_[i][j] = (matrix_[i][j]) ? matrix_[i][j] + m.matrix_[i][j] : m.matrix_[i][j];
            }
        }

        return *this;
    }


    Matrix Matrix::operator*=(const int c) {
        if (empty()) {
            std::cout << "ERROR: cannot scalar multiply a NULL matrix" << std::endl;
            exit(0);
        }

        for (unsigned i = 0; i < rows_; i++) {
            for (unsigned j = 0; j < cols_; j++) {
                matrix_[i][j] = (matrix_[i][j]) ? matrix_[i][j] * c : 0;
            }
        }

        return *this;
    }


    Matrix operator*(Matrix lhs, const int rhs) {
        lhs *= rhs;
        return lhs;
    }


    Matrix operator*(const int lhs, Matrix rhs) {
        rhs *= lhs;
        return rhs;
    }


    Matrix operator+(Matrix m1, const Matrix& m2) {
        return m1 += m2;
    }

    Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
        if (lhs.rows_ == 0 || lhs.cols_ == 0 || rhs.rows_ == 0 || rhs.cols_ == 0) {
            std::cout << "cannot multiply empty matrices" << std::endl;
            exit(0);
        }

        if (lhs.cols_ != rhs.rows_) {
            std::cout << "incompatible matrices" << std::endl;
            exit(0);
        }

        uint32_t new_rows = lhs.rows_;
        uint32_t new_cols = rhs.cols_;
        uint32_t inner_dim = lhs.cols_;
        Matrix newmatrix = Matrix(lhs.rows_, rhs.cols_);

        for (unsigned i = 0; i < new_rows; i++) {
            for (unsigned j = 0; j < new_cols; j++) {
                double& curr = newmatrix.matrix_[i][j];
                for (unsigned k = 0; k < inner_dim; k++) {
                    curr += lhs.matrix_[i][k] * rhs.matrix_[k][j];
                }
            }
        }

        return newmatrix;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        if (!m.matrix_ || !m.rows_ || !m.cols_) {
            os << "empty matrix";
            return os;
        }

        os << "[";
        for (unsigned i = 0; i < m.rows_; i++) {
            os << "[";
            for (unsigned j = 0; j < m.cols_; j++) {
                if (j != 0)
                    os << ", ";
                os << m.matrix_[i][j];
            }
            os << "]";
            if (i != m.rows_ - 1)
                os << "\n";
        }
        os << "]";
        return os;
    }

    void Matrix::makeInfectedMarkov(int sum, unsigned infectedCol) {
        if (infectedCol >= cols_ || infectedCol < 0) {
            infectedCol = 0;
        }
        for (unsigned x = 0; x < cols_; x++) {
            if (x == infectedCol) {
                for (unsigned y = 0; y < rows_; y++) {
                    matrix_[y][x] = 0;
                }
                matrix_[x][x] = 1;
            }
            else {
                double s = 0;
                for (unsigned y = 0; y < rows_; y++) {
                    s += matrix_[y][x];
                    matrix_[y][x] = matrix_[y][x] / sum;
                }
                s = sum - s;
                if (s >= 0) {
                    matrix_[x][x] = s / sum;
                }
                else {
                    std::cout << "sum is less than actual number of interactions" << std::endl;
                    exit(0);
                }
            }
        }
    }

    void Matrix::makeGoogleMatrix(double alpha, unsigned infectedCol) {
        for (unsigned x = 0; x < cols_; x++) {
            if (x != infectedCol) {
                for (unsigned y = 0; y < rows_; y++) {
                    matrix_[y][x] = (matrix_[y][x] * (1.0 - alpha)) + (alpha / rows_);
                }
            }
        }
    }
}
