#ifndef MATRIX_CPP
#define MATRIX_CPP

#include <stddef.h>
#include <stdint.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

namespace fin {

class Matrix {

private:
  // number of rows in the matrix
  uint32_t rows_;

  //number of columns in the matrix
  uint32_t cols_;

  // the matrix is represented as a one dimensional immutable array.
  double** matrix_;


  void _copy(const Matrix & other);
  void _destroy();

public:

  // default constructor
  Matrix();

  // destructor
  ~Matrix();

  // initialize empty matrix. 
  Matrix(int rows, int cols);
  Matrix(int rows, int cols, double val);
  // define matrix from constructor 
  template<size_t rows, size_t cols>
  Matrix(double (&matrix)[rows][cols]);

  // copy constructor
  Matrix(const Matrix & other);

  // getters
  int getRows();
  int getCols();

  bool empty();

  // access a row from the matrix;
  double* operator[](int index);

  Matrix operator=(const Matrix & other);
  bool operator==(const Matrix& other) const;
  Matrix operator+=(const int c);
  Matrix operator+=(const Matrix m);
  Matrix operator*=(const int c);
  void makeInfectedMarkov(int sum, unsigned infectedCol);
  void makeGoogleMatrix(double alpha, unsigned infectedCol);

  friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

  friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
};

}


#endif
