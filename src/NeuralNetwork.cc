#include "../include/NeuralNetwork.hh"
#include "../include/matrix.hh"
#include "../include/utils/MultiplyMatrix.hh"

void NeuralNetwork::backPropagation(){
    vector<Matrix *> newWeights;
    Matrix *gradient;
    //moving from output to hidden
    int outputLayerIndex = this->layers.size()-1;
    Matrix* derivedValuesYtoZ = this->layers.at(outputLayerIndex)->matrixifyDerivedVals();
    Matrix* gradientsYToZ = new Matrix(1,this->layers.at(outputLayerIndex)->getNeurons().size(),false);
    //cout<<"HELLO1 "<<errors.size()<<endl;
    for(int i=0;i<this->errors.size();i++){
        double d = derivedValuesYtoZ->getValue(0,i);    
        double e = this->errors.at(i);
        double g = d * e;
        gradientsYToZ->setValue(0,i,g);
    }
    //cout<<"HELLO2"<<endl;
    int lastHiddenLayerIndex = outputLayerIndex - 1;
    Layer *lastHiddenLayer = this->layers.at(lastHiddenLayerIndex);
    
    Matrix *weightsOutputToHidden = this->weightMatrices.at(outputLayerIndex-1);
    Matrix *deltaOutputToHidden = (new utils::MultiplyMatrix(
                                gradientsYToZ->transpose(),
                                lastHiddenLayer->matrixifyActivatedVals()))->execute()->transpose();
    
    Matrix *newWeightsOutputToHidden = new Matrix(deltaOutputToHidden->getNumRows(),
                                        deltaOutputToHidden->getNumCols(),false);
    
    for(int r=0;r<deltaOutputToHidden->getNumRows();r++){
        for(int c=0;c<deltaOutputToHidden->getNumCols();c++){
            double originalWeight = weightsOutputToHidden->getValue(r,c);
            double deltaWeight = deltaOutputToHidden->getValue(r,c);
            newWeightsOutputToHidden->setValue(r,c,originalWeight-deltaWeight);
        }
    }
    newWeights.push_back(newWeightsOutputToHidden);
    //cout<<"HELLO3"<<endl;
    gradient = new Matrix(gradientsYToZ->getNumRows(),gradientsYToZ->getNumCols(),false);
    for(int r=0;r<gradientsYToZ->getNumRows();r++){
        for(int c=0;c<gradientsYToZ->getNumCols();c++){
            gradient->setValue(r,c,gradientsYToZ->getValue(r,c));
        }
    }
    //cout<<"HELLO4"<<endl;
    for(int i = (outputLayerIndex-1);i>0;i--){
        Layer *l = this->layers.at(i);
        Matrix *derivedHidden = l->matrixifyDerivedVals();
        Matrix *activatedHidden = l->matrixifyActivatedVals();
        Matrix *derivedGradients = new Matrix(
                                    1,
                                    l->getNeurons().size(),
                                    false
                                    );
        Matrix *weightMatrix = this->weightMatrices.at(i);
        Matrix *originalWeight = this->weightMatrices.at(i-1);

        for(int r=0;r<weightMatrix->getNumRows();r++){
            double sum = 0;
            for(int c=0;c<weightMatrix->getNumCols();c++){
                sum += gradient->getValue(0,c) * weightMatrix->getValue(r,c);
            }
            double g = sum * activatedHidden->getValue(0,r);
            derivedGradients->setValue(0,r,g);
        }
        //cout<<"HELLO5"<<endl;
        Matrix *leftNeurons = (i-1)==0 ? this->layers.at(0)->matrixifyVals() :this->layers.at(i-1)->matrixifyActivatedVals();
        Matrix *deltaWeights = (new utils::MultiplyMatrix(derivedGradients->transpose(),leftNeurons))->execute()->transpose();
        Matrix *newWeight = new Matrix(
            deltaWeights->getNumRows(),deltaWeights->getNumCols(),false
        );
        
        for(int r=0;r<newWeight->getNumRows();r++){
            for(int c=0;c<newWeight->getNumCols();c++){
                double w = originalWeight->getValue(r,c);
                double d = deltaWeights->getValue(r,c);
                double nn = w - d;
                newWeight->setValue(r,c,nn);
            }
        }
        //cout<<"HELLO6"<<endl;
        gradient = new Matrix(derivedGradients->getNumRows(),derivedGradients->getNumCols(),false);
        for(int r=0;r<derivedGradients->getNumRows();r++){
            for(int c=0;c<derivedGradients->getNumCols();c++){
                gradient->setValue(r,c,derivedGradients->getValue(r,c));
            }
        }
        newWeights.push_back(newWeight);
    }
    reverse(newWeights.begin(),newWeights.end());
    this->weightMatrices = newWeights;
}

void NeuralNetwork::setErrors(){
    this->errors.clear();
    if(this->target.size()==0){
        cerr << "No Target found for this Neural Network"<<endl;
        assert(false);
    }

    if(this->target.size()!=this->layers.at(this->layers.size()-1)->getNeurons().size()){
        cerr << "Target size is not the same as output size:" << this->layers.at(this->layers.size()-1)->getNeurons().size()<<endl;
        assert(false);
    }

    this->error = 0.0;
    vector<Neuron *> outputNeurons = this->layers.at(this->layers.size()-1)->getNeurons();

    for(int i=0;i<target.size();i++){
        //cout<<outputNeurons.at(i)->getActivatedVal()<<" "<<target.at(i)<<endl;
        double tempError = (outputNeurons.at(i)->getActivatedVal()) - target.at(i);
        this->errors.push_back(tempError);
        this->error+=tempError;
    }
    this->historicalErrors.push_back(this->error);
}

NeuralNetwork::NeuralNetwork(vector<int> topology){
    this->topology = topology;
    this->topologySize = topology.size();
    for(int i=0;i<this->topologySize;i++){
        Layer *l = new Layer(topology.at(i));
        this->layers.push_back(l);
    }

    for(int i=0;i<this->topologySize-1;i++){
        Matrix *m = new Matrix(topology.at(i),topology.at(i+1),true);
        this->weightMatrices.push_back(m);
    }
}

void NeuralNetwork::feedForward(){
    for(int i=0;i<this->layers.size()-1;i++){
        Matrix *a = this->getNeuronMatrix(i);

        if(i!=0){
            a = this->getActivatedNeuronMatrix(i);
        }

        Matrix *b = this->getWeightMatrix(i);
        Matrix *c = (new utils::MultiplyMatrix(a,b))->execute();

        for(int c_index=0;c_index<c->getNumCols();c_index++)
            this->setNeuronValue(i+1,c_index,c->getValue(0,c_index));
    }
}

void NeuralNetwork::setCurrentInput(vector<double> input){
    this->currentInput = input;
    for(int i=0;i<input.size();i++){
        this->layers.at(0)->setVal(i,input.at(i));
    }
}

void NeuralNetwork::printToConsole(){
    for(int i=0;i<this->topologySize;i++){
        cout<<"Layer : "<<i<<endl;
        if(i==0){
            Matrix *m = this->layers.at(i)->matrixifyVals();
            m->printToConsole();
        }else{
            Matrix *m = this->layers.at(i)->matrixifyActivatedVals();
            m->printToConsole();
        }
    }
}