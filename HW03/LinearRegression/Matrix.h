#pragma once

/* Your code here */
#include <string>
#include <vector>
using namespace std; 

class Matrix{
    public:
        vector<vector<double>> data;
        Matrix operator+(const Matrix&);
        Matrix operator-(const Matrix&);
        Matrix operator*(const Matrix&);
        Matrix Transpose();
        Matrix GetSubVectorbyColumn(int column);
        void Print();
        int GetNumRow();
        int GetNumColumn();
        double GetVal(int x, int y);
};

class DataFrame{
    Matrix matrix;

    public:
        int ReadData(std::string FileName, char sep, char comment,bool IsHeader);
        Matrix GetMatrix(int index[], int nColumn);

};


Matrix Cor(Matrix &mat, int method = 1);
Matrix SimpleLinearRegression(Matrix &X, Matrix &Y);