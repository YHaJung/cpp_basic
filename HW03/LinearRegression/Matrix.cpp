#include "Matrix.h"

/* Your code here */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <algorithm>

using namespace std;


int DataFrame::ReadData(std::string FileName, char sep, char comment,bool IsHeader){
    ifstream myfile(FileName);
    string line;
    string word;

	if (myfile.is_open()){
		while(getline(myfile, line)){
            if (line[0] != comment){
                if (IsHeader){
                    IsHeader = false;
                }else{
                    vector<double> row;
                    istringstream sline(line);
                    while(getline(sline, word, sep)){
                        row.push_back(std::stod(word));
                    }
                    matrix.data.push_back(row);
                }
            } 
        }
		myfile.close();
	}else{
		cout << "Unable to open file";
	}
	return 0;
}

Matrix DataFrame::GetMatrix(int index[], int nColumn){
    Matrix new_matrix;
    for(vector<double> v : matrix.data){
        vector<double> r;
        for (int i=0; i<nColumn; i++){
            r.push_back(v[index[i]]);
        }
        new_matrix.data.push_back(r);
    }
    return new_matrix;
}


Matrix Matrix::operator+ (const Matrix& param){
    Matrix new_matrix;
    for(int i=0; i<data.size(); i++){
        vector<double> v;
        for(int j=0; j<data[0].size(); j++){
            v.push_back(data[i][j] + param.data[i][j]);
        }
        new_matrix.data.push_back(v);
    }
    return new_matrix;
}

Matrix Matrix::operator- (const Matrix& param){
    Matrix new_matrix;
    for(int i=0; i<data.size(); i++){
        vector<double> v;
        for(int j=0; j<data[0].size(); j++){
            v.push_back(data[i][j] - param.data[i][j]);
        }
        new_matrix.data.push_back(v);
    }
    return new_matrix;
}

Matrix Matrix::operator*(const Matrix& matrix2){
    Matrix new_matrix;
    for(int i=0; i<data.size(); i++){
        vector<double> v;
        for(int j=0; j<matrix2.data[0].size(); j++){
            double d = 0;
            for(int k=0;k<data[0].size();k++){
                d+=data[i][k]*matrix2.data[k][j];
            }
            v.push_back(d);
        }
        new_matrix.data.push_back(v);
    }
    return new_matrix;
}

Matrix Matrix::Transpose(){
    Matrix new_matrix;
    for(int i=0; i< data[0].size(); i++){
        vector<double> v;
        for(int j=0; j< data.size(); j++){
            v.push_back(data[j][i]);
        }
        new_matrix.data.push_back(v);
    }
    return new_matrix;
}

Matrix Matrix::GetSubVectorbyColumn(int column){
    Matrix new_matrix;
    for(int i=0; i<GetNumRow(); i++){
        vector<double> v;
        v.push_back(data[i][column]);
        new_matrix.data.push_back(v);
    }
    return new_matrix;
}

void Matrix::Print(){
    for(vector<double> v: data){
        for(double d : v){
            cout << d << ' ';
        }
        cout << endl;
    }
}


int Matrix::GetNumRow(){
    return data.size();
}

int Matrix::GetNumColumn(){
    return data[0].size();
}

double Matrix::GetVal(int x, int y){
    return data[x][y];
}

vector<double> Col2row(const Matrix& matrix){
    vector<double> v;
    for (int i=0; i<matrix.data.size(); i++){
        v.push_back(matrix.data[i][0]);
    }
    return v;
}

double pearsonCorrelation(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0, sum_y2 = 0.0;

    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
        sum_y2 += y[i] * y[i];
    }

    double numerator = (n * sum_xy) - (sum_x * sum_y);
    double denominator = sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y));
    if (denominator == 0.0) {
        return 0.0;
    } else {
        return numerator / denominator;
    }
}

double kendallTau(const std::vector<double>& x, const std::vector<double>& y)
{
    int n = x.size();
    std::vector<std::pair<double, double>> data2(n);
    for (int i = 0; i < n; ++i) {
        data2[i] = std::make_pair(x[i], y[i]);
    }

    std::sort(data2.begin(), data2.end());

    double concordant = 0, discordant = 0, xeq=0, yeq=0;
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
            if ((data2[i].first - data2[j].first)*(data2[i].second - data2[j].second)< 0 ){
                discordant++;
            }
        }
    }
    return 1 - (2*discordant / (n * (n - 1) / 2));
}



Matrix Cor(Matrix &mat, int method) {
    int n = mat.GetNumRow();
    int m = mat.GetNumColumn();
    Matrix corMat;
    corMat.data = vector<vector<double>>(m,vector<double>(m));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < i; j++) {
            double cor = 0.0;
            vector<double> c1 = Col2row(mat.GetSubVectorbyColumn(i));
            vector<double> c2 = Col2row(mat.GetSubVectorbyColumn(j));
            if (method == 1) {
                cor = pearsonCorrelation(c1, c2);
            } else if (method == 2) {
                cor = kendallTau(c1, c2);
            }
            corMat.data[i][j] = cor;
            corMat.data[j][i] = cor;
        }
        corMat.data[i][i] = 1.0;
    }
    return corMat;
}


Matrix SimpleLinearRegression(Matrix &X, Matrix &Y){
    vector<double> vX = Col2row(X);
    vector<double> vY = Col2row(Y);
    int n = vX.size();
    double sum_x = 0;
    double sum_y = 0;
    double sum_xy = 0;
    double sum_x_squared = 0;

    for (int i = 0; i < n; i++) {
        sum_x += vX[i];
        sum_y += vY[i];
        sum_xy += vX[i] * vY[i];
        sum_x_squared += vX[i] * vX[i];
    }

    double slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x_squared - sum_x * sum_x);
    double intercept = (sum_y - slope * sum_x) / n;

    vector<vector<double>> coefficients {{intercept}, {slope}};
    Matrix new_matrix;
    new_matrix.data = coefficients;

    return new_matrix;
}