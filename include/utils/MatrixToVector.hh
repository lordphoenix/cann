#ifndef _MATRIX_TO_VECTOR_HPP_
#define _MATRIX_TO_VECTOR_HPP_

#include "../matrix.hh"

#include<bits/stdc++.h>
using namespace std;

namespace utils{
    class MatrixToVector{
        public :
            MatrixToVector(Matrix *a);
            vector<double> execute();
        private:
            Matrix *a;
    };
}

#endif