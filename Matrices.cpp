#include <iostream>
#include <ctime> 
#include "Matrix.h"
using namespace std;

matrix Declaration(matrix M)
{
    M.value = new double* [M.lines];// объявление двумерного динамического массива на lines элементов
    for (int count = 0; count < M.lines; count++)
        M.value[count] = new double[M.columns];
    return M;
}
matrix Input()
{
    matrix M;
    cout << "Enter the matrix dimention(lxc):";
    cin >> M.lines;
    cin >> M.columns;
    M = Declaration(M);
    if (M.lines > 0 && M.columns > 0) {
        cout << "Enter the elements:" << endl;
        for (int count_row = 0; count_row < M.lines; count_row++) {
            for (int count_column = 0; count_column < M.columns; count_column++)
            {
                cin >> M.value[count_row][count_column];
            }
        }
        cout << endl;
        return M;
    }
    else {
        cout << "Input:Parameters are incorrect." << endl;
        return M = { 0 };
    }

}

matrix InputRandom()
{
    matrix M;
    int a, b;
    cout << "Enter the matrix dimention(lxc):";
    cin >> M.lines;
    cin >> M.columns;
    M = Declaration(M);
    cout << "Enter the number interval:";
    cin >> a;
    cin >> b;
    srand(time(NULL));
    if (M.lines > 0 && M.columns > 0) {
        for (int count_row = 0; count_row < M.lines; count_row++) {
            for (int count_column = 0; count_column < M.columns; count_column++)
            {
                M.value[count_row][count_column] = 1.0 * (rand() % (abs(a - b) + 1) + a);//(a ... b);
            }
        }
        cout << endl;
        return M;
    }
    else {
        cout << "Input:Parameters are incorrect." << endl;
        return M = { 0 };
    }

}
void Output(matrix A)
{

    if (A.lines > 0 && A.columns > 0) {
        cout << "M[" << A.lines << " " << A.columns << "]:" << endl;
        for (int count_row = 0; count_row < A.lines; count_row++)
        {
            cout << "\335";
            for (int count_column = 0; count_column < A.columns; count_column++)
                cout << "\t" << A.value[count_row][count_column];
            cout << "\t\335" << endl;
        }
        cout << endl;
    }
    else {
        if (A.lines == 0 && A.columns == 0) {}
        else cout << "Output:Parameters are incorrect." << endl;
    }
}
double GetValue(matrix M, int i, int j) {
    if (i <= M.lines - 1 && j <= M.columns - 1)
    {
        return M.value[i][j];
        cout << endl;
    }
    cout << "Wrong index of an element." << endl;
    return NULL;
}
matrix GetColumn(matrix M, int i)
{
    if (M.columns >= i && i > 0) {
        matrix answer;
        answer.lines = M.lines;
        answer.columns = 1;
        answer = Declaration(answer);
        for (int j = 0; j < M.lines; j++) {
            answer.value[j][0] = M.value[j][i - 1];
        }
        cout << "Column " << i << " :" << endl;
        return answer;
    }
    else
    {
        cout << "Parameters are incorrect." << endl;
        return M = { 0 };
    }
}
matrix GetLine(matrix M, int j) {
    if (M.lines >= j && j > 0) {
        matrix answer;
        answer.lines = 1;
        answer.columns = M.columns;
        answer = Declaration(answer);
        for (int i = 0; i < M.columns; i++) {
            answer.value[0][i] = M.value[j - 1][i];
        }
        cout << "Line " << j << " :" << endl;
        return answer;
    }
    else
    {
        cout << "Parameters are incorrect." << endl;
        return M = { 0 };
    }

}
matrix Minor(matrix M, int i, int j) {
    if (M.lines > 1 && M.columns > 1) {
        matrix answer;
        int l = 0, c = 0;
        answer.lines = M.lines - 1;
        answer.columns = M.columns - 1;
        answer = Declaration(answer);
        for (int k = 0; k < M.lines; k++) {
            c = 0;
            for (int p = 0; p < M.columns; p++) {
                if (k != i && p != j)
                {
                    answer.value[l][c] = M.value[k][p];
                    c++;

                }
            }if (k != i) {
                l++;
            }
        }
        return answer;
    }
    else {
        cout << "Parameters are incorrect. Minor does not exist." << endl;
        return M = { 0 };
    }
}
double Determinant(matrix M) {
    double answer = 0;
    if (M.lines != M.columns)
    {
        cout << "Matrix is not quadratic form." << endl;
        return NULL;
    }
    if (M.columns == 1) {
        answer = M.value[0][0];
    }
    else if (M.columns == 2) {
        answer = M.value[0][0] * M.value[1][1] - M.value[0][1] * M.value[1][0];
    }
    else {
        for (int i = 0; i < M.columns; i++) {
            answer += pow(-1, i) * GetValue(M, 0, i) * Determinant(Minor(M, 0, i));
        }
    }
    return answer;
}
matrix Adding(matrix A, matrix B)
{
    if (A.lines == B.lines && A.columns == B.columns) {
        matrix answer;
        answer.lines = A.lines;
        answer.columns = A.columns;
        answer = Declaration(answer);
        for (int i = 0; i < A.lines; i++)
            for (int j = 0; j < A.columns; j++)
            {
                answer.value[i][j] = A.value[i][j] + B.value[i][j];
            }
        return answer;
    }
    else cout << "Matrix dimentions do not match." << endl;
    return A = { 0 };
}
matrix Subtraction(matrix A, matrix B)
{
    if (A.lines == B.lines && A.columns == B.columns) {
        matrix answer;
        answer.lines = A.lines;
        answer.columns = A.columns;
        answer = Declaration(answer);
        for (int i = 0; i < A.lines; i++)
            for (int j = 0; j < A.columns; j++)
            {
                answer.value[i][j] = A.value[i][j] - B.value[i][j];
            }
        return answer;
    }
    else cout << "Matrix dimentions do not match." << endl;
    return A = { 0 };
}
matrix MatrixMultiplication(matrix A, matrix B) {
    if (A.columns == B.lines) {
        matrix answer;
        answer.lines = A.lines;
        answer.columns = B.columns;
        answer = Declaration(answer);
        for (int count_lines1 = 0; count_lines1 < A.lines; count_lines1++) {
            answer.value[A.lines] = new double[B.columns];
            for (int count_columns2 = 0; count_columns2 < B.columns; count_columns2++) {
                answer.value[count_lines1][count_columns2] = 0;
                for (int count_columns1 = 0; count_columns1 < A.columns; count_columns1++) {

                    {
                        answer.value[count_lines1][count_columns2] += A.value[count_lines1][count_columns1] * B.value[count_columns1][count_columns2];
                    }
                }
            }
        }

        return answer;
    }
    else
    {
        cout << "These matrix can not be multiplicate.The dimentions do not match." << endl;
        return A = { 0 };
    }
}
matrix NumberMultiplication(matrix A, double k)
{
    matrix answer;
    answer.lines = A.lines;
    answer.columns = A.columns;
    answer = Declaration(answer);
    for (int j = 0; j < A.lines; j++) {
        for (int i = 0; i < A.columns; i++) {
            answer.value[j][i] = k * A.value[j][i];
        }
    }
    return answer;

}
matrix TransposeMatrix(matrix A)
{
    matrix answer;
    answer.lines = A.columns;
    answer.columns = A.lines;
    answer = Declaration(answer);
    for (int i = 0; i < A.columns; i++) {
        for (int j = 0; j < A.lines; j++) {
            answer.value[i][j] = A.value[j][i];
        }
    }
    return answer;

}

matrix IdentityMatrix(matrix A)
{
    if (A.lines == A.columns) {

        matrix answer;
        answer.lines = A.lines;
        answer.columns = A.columns;
        answer = Declaration(answer);
        for (int j = 0; j < A.lines; j++) {
            for (int i = 0; i < A.columns; i++) {
                if (i == j) {
                    answer.value[j][i] = 1;
                }
                else {
                    answer.value[j][i] = 0;
                }
            }

        }
        return answer;
    }
    else
    {
        cout << "Matrix is not quadratic form." << endl;
        return A = { 0 };
    }
}

matrix MatrixOfCofactors(matrix A)//транспонированная матрица алгебраических дополнений
{
    if (A.lines == A.columns && Determinant(A) != 0) {
        matrix answer;
        answer.lines = A.lines;
        answer.columns = A.columns;
        answer = Declaration(answer);
        for (int j = 0; j < A.lines; j++) {
            for (int i = 0; i < A.columns; i++) {
                answer.value[j][i] = pow(-1, i + j) * Determinant(Minor(A, i, j));
            }
        }

        return answer;
    }
    if (A.lines == A.columns && Determinant(A) == 0) {
        cout << "Determinant is 0. Infinite number Of solutions." << endl;
        return A = { 0 };
    }
    else
    {
        cout << "Matrix is not quadratic form." << endl;
        return A = { 0 };
    }
}
matrix MatrixDegree(matrix A, int a)
{
    matrix answer;
    answer.lines = A.lines;
    answer.columns = A.columns;
    answer = Declaration(answer);
    if (a == -1 && A.lines == A.columns && Determinant(A) != 0)//inverse matrix
    {
        answer = NumberMultiplication(MatrixOfCofactors(A), (1.0 / Determinant(A)));
        return answer;
    }
    if (a == -1 && A.lines == A.columns && Determinant(A) == 0)
    {
        cout << "Operation can not be realised. Determinant is 0." << endl;
        return A = { 0 };
    }
    if (a == 0 && A.lines == A.columns)//identity matrix
    {
        return answer = IdentityMatrix(A);
    }
    if (a == 1) {
        answer = A;
    }
    if (a >= 1 && A.lines == A.columns)//raising to a power
    {
        answer = A;
        for (int i = 1; i < a; i++) {
            answer = MatrixMultiplication(answer, A);
        }
        return answer;
    }
    else {
        cout << "Error. Matrix is not quadratic form or power is less than -1." << endl;
        return A = { 0 };
    }
}
