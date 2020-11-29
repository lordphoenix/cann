#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include<bits/stdc++.h>
using namespace std;

class Matrix{
    public:
        Matrix(int r, int c, bool isRandom);
        Matrix *transpose();
        Matrix *copy();

        void setValue(int r, int c, double v) {this->data.at(r).at(c) = v;}
        double getValue(int r, int c){ return this->data.at(r).at(c); }

        vector<vector<double> > getDatas(){return this->data;}

        void printToConsole();

        int getNumRows() { return this->numRows;}
        int getNumCols() { return this->numCols;}
    
        private:
        int numRows,numCols;
        double generateRandomNumber();
        vector<vector<double> > data;
};

#endif