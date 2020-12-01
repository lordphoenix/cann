#include<bits/stdc++.h>
#include "../include/matrix.hpp"
#include "../include/Neuron.hpp"

using namespace std;

int main()
{
    Neuron *nn = new Neuron(1.77);
    cout<<"Value "<<nn->getVal()<<endl;
    cout<<"Activated Val "<<nn->getActivatedVal()<<endl;
    cout<<"Derived Val "<<nn->getDerivedVal()<<endl;
    return 0;
}