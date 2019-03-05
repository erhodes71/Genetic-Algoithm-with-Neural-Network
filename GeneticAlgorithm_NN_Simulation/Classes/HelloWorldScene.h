#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <stdlib.h>
#include <stdio.h>      /* printf */
#include <math.h>
//#include "NN.hpp"

#define PI 3.14159265

using namespace cocos2d;
using namespace std;

class CreatureData
{
public:
    CreatureData();
    void updateCreature();
    void lifeSpanExtended();//--->> adds to total amount of food and extends lifespan
    void lifeSpanNulled();
    void incimentAmountOfFood();
    double getLifeSpan();
    
    void setTotalAmountFood(int amount);
    int getTotalAmountFood();
    ~CreatureData();
    
    
    
private:
    int totalAmountFood;//Use this as fitness score
    double lifeSpan;//-->>Starts with 60
    

};

class NN
{
    
public:
    NN();
    NN(double x[2], double y[2], double z[2],double t[2]);
    void rotation(double input);
    double sig(double input);
    ~NN();
    
    //
    void setArrayX(double xx[2]);
    void setArrayY(double yy[2]);
    void setArrayZ(double zz[2]);
    void setArrayT(double tt[2]);
    
    
    void printChromosome();
    
    //Conversion methods
    string decToBinary(double input);
    
    
    //Returns the weights
    double* getArrayX();//--USE THIS FOR NOW
    
    double* getArrayY();
    double* getArrayZ();
    double* getArrayT();
    
    
    //W1
    double arrayX[2];
    double arrayY[2];
    double arrayZ[2];
    
    //W2
    double arrayT[2];
    
    //OUTPut
    double outPut[3];
    
    //Data for GA
    double fitness;
    std::string chromosome;
    
};



class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void update(float delta);
    
    //Time handling
    unsigned _elapsedTime; //Millieconds
    
    //Neural nets
    
    //Food
    Sprite* food[1];
    NN* nets[10];
    CreatureData* cD[10];
    
    //Spawning Functions
    void spawnCreatures();
    void spawnFood();
    
    //Genetic Algorithm Functions
    void GeneticAlgorithm();
    string Crossover(int nn1, int nn2);
    string Mutate(string nn);
    int Roulette(double TotalFitness);
    double binaryToDec(string input);
    int numberOfGenerations;
    
    int numberOfCreaturesActive;
    int numberOfFoodActive;
    
    //Update File for record
    void updateFile();
    
    //Display of different generations
    CCLabelTTF* ttf1;
    
    //Update the creature rotations
    void updateCreature(int creatureID);
    
    //Find max
    int findMax(double first, double second, double third);
    
    
    //Calulates the distance of the two points
    double distance(double x1, double x2, double y1, double y2);
    
    //Gets the rotation of the single coordinate
    double getRotationSingleCoordinate(double x, double y);
    
    
    bool onContactBegan(PhysicsContact &contact);
    
    int spawnIndex;
    int spawnFoodIndex;
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    
};

#endif // __HELLOWORLD_SCENE_H__
