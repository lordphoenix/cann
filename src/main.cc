#include<bits/stdc++.h>
#include "../include/matrix.hpp"

using namespace std;

int main()
{
    Matrix *m = new Matrix(3,3,true);
    m->printToConsole();
    cout<<"--------------------------------------------------------"<<endl;
    Matrix *mT = m->transpose();
    mT->printToConsole();
    return 0;
}