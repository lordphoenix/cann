#ifndef _MULTIPLY_MATRIX_HPP_
#define _MULTIPLY_MATRIX_HPP_

#include "../matrix.hh"

#include<bits/stdc++.h>
using namespace std;

namespace utils{
    class MultiplyMatrix{
        public :
            MultiplyMatrix(Matrix *a,Matrix *b);
            Matrix *execute();
        private:
            Matrix *a;
            Matrix *b;
            Matrix *c;
    };
}

#endif