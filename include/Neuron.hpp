#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include<bits/stdc++.h>
using namespace std;

class Neuron{
    public:
        Neuron(double val);
        Neuron(double val, int activationType);

        void setVal(double v);

        void activate();

        void derive();

  // Getter
        double getVal() { return this->val; }
        double getActivatedVal() { return this->activatedVal; }
        double getDerivedVal() { return this->derivedVal; }
    private:
        double val;
        double activatedVal;
        double derivedVal;

        //int activationType = 3;
};

#endif