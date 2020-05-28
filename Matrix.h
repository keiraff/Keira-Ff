#pragma once
#define Matrix_h

struct matrix
{
    int lines;
    int columns;
    double** value;
};


matrix Declaration(matrix M);
matrix Input();
matrix InputRandom();
void Output(matrix A);
double GetValue(matrix M, int i, int j);
matrix GetLine(matrix M, int j);
matrix GetColumn(matrix M, int i);
matrix Minor(matrix M, int i, int j);
double Determinant(matrix M);
matrix Adding(matrix A, matrix B);
matrix Subtraction(matrix A, matrix B);
matrix MatrixMultiplication(matrix A, matrix B);
matrix NumberMultiplication(matrix A, double k);
matrix TransposeMatrix(matrix A);
matrix IdentityMatrix(matrix A);
matrix MatrixOfCofactors(matrix A);
matrix MatrixDegree(matrix A, int a);
