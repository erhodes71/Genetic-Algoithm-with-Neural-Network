//
//  NN.hpp
//  GeneticAlgorithm_NN_Simulation
//
//  Created by Eric Rhodes on 7/27/17.
//
//

#ifndef NN_hpp
#define NN_hpp

#include <stdio.h>
#include <stdlib.h>



using namespace std;

class NN
{
    
public:
    NN();
    NN(double x[3], double y[3], double t[3]);
    double rotation(double x, double y);
    double sig(double input);
    ~NN();
    
    //
    void setArrayX(double xx[3]);
    void setArrayY(double yy[3]);
    void setArrayT(double tt[3]);
    void printChromosome();
    
    
    //W1
    double arrayX[3];
    double arrayY[3];
    
    //W2
    double arrayT[3];
    
    //Data for GA
    double fitness;
    std::string chromosome;
    
};

#endif /* NN_hpp */
