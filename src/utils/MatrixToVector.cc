#include "../../include/utils/MatrixToVector.hh"

utils::MatrixToVector::MatrixToVector(Matrix *a){
    this->a = a;
}

vector<double> utils::MatrixToVector::execute(){
    vector<double> result;

    for(int i=0;i<this->a->getNumRows();i++){
        for(int j=0;j<this->a->getNumCols();j++){
            result.push_back(a->getValue(i,j));
        }
    }

    return result;
}