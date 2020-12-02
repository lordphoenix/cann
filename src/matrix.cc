#include "../include/matrix.hpp"
using namespace std;

double Matrix::generateRandomNumber(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-.0001, .0001);

    return dis(gen);
}

Matrix::Matrix(int numRows, int numCols, bool isRandom){
    this->numRows = numRows;
    this->numCols = numCols;

    for(int i=0;i<numRows;i++){
        vector<double> cols;
        for(int j=0;j<numCols;j++){
            double value = isRandom?generateRandomNumber():0.00;
            cols.push_back(value);
        }
        this->data.push_back(cols);
    }
}

Matrix* Matrix::transpose(){
    Matrix* m = new Matrix(this->numRows,this->numCols,false);

    for(int i=0;i<this->numRows;i++){
        for(int j=0;j<this->numCols;j++){
            m->setValue(j,i,this->getValue(i,j));
        }
    }
    return m;
}

Matrix* Matrix::copy(){
    Matrix* m = new Matrix(this->numRows,this->numCols,false);

    for(int i=0;i<this->numRows;i++){
        for(int j=0;j<this->numCols;j++){
            m->setValue(i,j,this->getValue(i,j));
        }
    }
    return m;
}

void Matrix::printToConsole(){
    for(int i=0;i<this->numRows;i++){
        for(int j=0;j<this->numCols;j++){
            cout<<this->data.at(i).at(j)<<"\t\t";
        }
        cout<<endl;
    }
}