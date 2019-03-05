//
//  NN.cpp
//  GeneticAlgorithm_NN_Simulation
//
//  Created by Eric Rhodes on 7/27/17.
//
//

#include "NN.hpp"

NN::NN()
{
    //Set the weights
    srand (time(NULL));
    
    for(int i = 0; i < 3; i++)
    {
        //________________________
        int posNeg1 = rand()%2;
        double random1= rand()%100;
        
        if(posNeg1 == 0)
        {
            arrayX[i] = random1;
        }else{
            arrayX[i] = -random1;
        }
        //CCLOG("Test%f",posNeg1);
        
        
        
        //________________________
        int posNeg2 = rand()%2;
        double random2 = rand()%100;
        if(posNeg1 == 0)
        {
            arrayY[i] = random2;
        }else{
            arrayY[i] = -random2;
        }
        //CCLOG("%f",random2);
        
        
        
        //________________________
        int posNeg3 = rand()%2;
        double random3 = rand()%100;
        if(posNeg3 == 0)
        {
            arrayT[i] = random3;
        }else{
            arrayT[i] = -random3;
        }
        //CCLOG("%f",random3);
        
    }
    
}

NN::~NN()
{
    
}

NN::NN(double x[3], double y[3], double t[3])
{
    //Set the weights
    setArrayX(x);
    setArrayY(y);
    setArrayT(t);
    
}

//Set the X array
void NN::setArrayX(double xx[3])
{
    arrayX[0] = xx[0];
    arrayX[1] = xx[1];
    arrayX[2] = xx[2];
}

//Set the Y array
void NN::setArrayY(double yy[3])
{
    arrayY[0] = yy[0];
    arrayY[1] = yy[1];
    arrayY[2] = yy[2];
}

//Set the T array
void NN::setArrayT(double tt[3])
{
    arrayT[0] = tt[0];
    arrayT[1] = tt[1];
    arrayT[2] = tt[2];
}

double NN::rotation(double x, double y)
{
    //calculation
    double arrayZ[] = {(x * (arrayX[0])) + (y * (arrayY[0])),(x * (arrayX[1])) + (y * (arrayY[1])),(x * (arrayX[2])) + (y * (arrayY[2]))};
    printf("arrayZ: %f",arayZ);
    double arrayZZ[3];
    arrayZZ[0] = sig(arrayZ[0]);
    arrayZZ[1] = sig(arrayZ[1]);
    arrayZZ[2] = sig(arrayZ[2]);
    double output = (arrayZZ[0]* (arrayT[0]))+(arrayZZ[1]* (arrayT[1]))+(arrayZZ[2]* (arrayT[2]));
    
    return output;
}

//Sigmoid function
double NN::sig(double input)
{
    //Add other function here
    return 1 / (1 + exp(-input));
}

void NN::printChromosome()
{
    for(int i = 0; i < 3; i++)
    {
        CCLOG("{%f %f %f}",arrayX[i], arrayY[i], arrayT[i]);
    }
}
