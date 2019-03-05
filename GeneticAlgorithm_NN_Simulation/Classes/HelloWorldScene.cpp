//-------------------
/*
 
GENETIC ALGORITHM Neural Network
BY: ERIC RHODES

DESCRIPTION: 
This project is used to demonstrait the effectivness of a Neural Network trained by means of a Genetic Algorithm.
It uses cocos2dx game engine to handle collisions and handle time/frame rates.
 
*/
//-------------------


#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include <iostream>
#include <fstream>


USING_NS_CC;

#define numberOfCreatures 10
#define numberOfFood 10

//#define numberOfCreaturesBeforeRestart 18

//Random number between 1 and 0
#define RANDOM_NUM		((double)rand()/(RAND_MAX))

#define CROSSOVER_RATE 0.7
#define MUTATION_RATE 0.001

//#define MAX_NODE = (0.8191*0.8191)


CreatureData::CreatureData()
{
    totalAmountFood = 0;
    lifeSpan = 20;
}

CreatureData::~CreatureData()
{
    
}

//Returns the lifespan of the creature
double CreatureData::getLifeSpan()
{
    return lifeSpan;
}

//Returns the total amount of food
int CreatureData::getTotalAmountFood()
{
    return totalAmountFood;
}

//Sets the total amount of food
void CreatureData::setTotalAmountFood(int amount)
{
    totalAmountFood = amount;
}

//Expands life span
void CreatureData::lifeSpanExtended()
{
    lifeSpan += 20;

}

//Clear lifespan
void CreatureData::lifeSpanNulled()
{
    lifeSpan = 0;
    
}

//Updates the Creature
void CreatureData::updateCreature()
{
    lifeSpan -= 1;

}

//Incriments the amount of food
void CreatureData::incimentAmountOfFood()
{
    totalAmountFood += 1;
    
}


//Default constructor -> creates randome weights
NN::NN()
{
    //Set the weights
    //srand(time(NULL));
    
    //W1
    for(int i = 0; i < 2; i++)
    {
        
        //________________________
        //Handles X Weights
        double random1 = (rand()%8191);
        double setValue1 = random1/10000;
        
        double binRand1 = RANDOM_NUM;
        
        if(binRand1 >= 0.5)
        {
            arrayX[i] = setValue1;
        }else{
            arrayX[i] = -setValue1;
        }
        
        
        
        //________________________
        //Handles Y Weights
        double random2 = (rand()%8191);
        double setValue2 = random2/10000;
        
        double binRand2 = RANDOM_NUM;
        
        if(binRand2 >= 0.5)
        {
            arrayY[i] = setValue2;
        }else{
            arrayY[i] = -setValue2;
        }
        
        
        
        
        //________________________
        //Handles Z Weights
        double random3 = (rand()%8191);
        double setValue3 = random3/10000;
        
        double binRand3 = RANDOM_NUM;
        
        if(binRand3 >= 0.5)
        {
            arrayZ[i] = setValue3;
        }else{
            arrayZ[i] = -setValue3;
        }
    }
    
    //W2
    for(int i = 0; i < 2; i++)
    {
        //________________________
        //Handles T Weights
        double random = (rand()%8191);
        double setValue = random/10000;
        
        double binRand1 = RANDOM_NUM;
        
        if(binRand1 >= 0.5)
        {
            arrayT[i] = setValue;
        }else{
            arrayT[i] = -setValue;
        }
        
    }
    
    //Creating chromosome of creature
    string chromosomeString = "";
    
    //X weights added to chromosome
    for(int i = 0; i < 2; i++)
    {
        if(arrayX[i] > 0){
            string chunk = decToBinary(arrayX[i]*10000);
            chromosomeString += "1";//If positive
            chromosomeString += chunk;
        }else{
            string chunk = decToBinary(arrayX[i]*10000*-1);
            chromosomeString += "0";//If negative
            chromosomeString += chunk;
        }
    }
    
    //Y weights added to chromosome
    for(int i = 0; i < 2; i++)
    {
        if(arrayY[i] > 0){
            string chunk = decToBinary(arrayY[i]*10000);
            chromosomeString += "1";//If positive
            chromosomeString += chunk;
        }else{
            string chunk = decToBinary(arrayY[i]*10000*-1);
            chromosomeString += "0";//If negative
            chromosomeString += chunk;
        }
    }
    
    //Z weights added to chromosome
    for(int i = 0; i < 2; i++)
    {
        if(arrayZ[i] > 0){
            string chunk = decToBinary(arrayZ[i]*10000);
            chromosomeString += "1";//If positive
            chromosomeString += chunk;
        }else{
            string chunk = decToBinary(arrayZ[i]*10000*-1);
            chromosomeString += "0";//If negative
            chromosomeString += chunk;
        }
    }
    
    //T weights added to chromosome
    for(int i = 0; i < 2; i++)
    {
        if(arrayT[i] > 0){
            string chunk = decToBinary(arrayT[i]*10000);
            chromosomeString += "1";//If positive
            chromosomeString += chunk;
        }else{
            string chunk = decToBinary(arrayT[i]*10000*-1);
            chromosomeString += "0";//If negative
            chromosomeString += chunk;
        }
    }
    
    chromosome = chromosomeString;
}

NN::~NN()
{
    
}

NN::NN(double x[2], double y[2], double z[2], double t[2])
{
    //Set the weights
    setArrayX(x);
    setArrayY(y);
    setArrayZ(z);
    setArrayT(t);
    
    //Creating chromosome of creature
    string chromosomeString = "";
    
    //X weights added to chromosome
    for(int i = 0; i < 2; i++)
    {
        string chunk = decToBinary(arrayX[i]*10000);
        chromosomeString += chunk;
    }
    
    //Y weights added to chromosome
    for(int i = 0; i < 2; i++)
    {
        string chunk = decToBinary(arrayY[i]*10000);
        chromosomeString += chunk;
    }
    
    //Z weights added to chromosome
    for(int i = 0; i < 2; i++)
    {
        string chunk = decToBinary(arrayZ[i]*10000);
        chromosomeString += chunk;
    }
    
    //T weights added to chromosome
    for(int i = 0; i < 2; i++)
    {
        string chunk = decToBinary(arrayT[i]*10000);
        chromosomeString += chunk;
    }
    
    chromosome = chromosomeString;
}

//Set the X array
void NN::setArrayX(double xx[2])
{
    arrayX[0] = xx[0];
    arrayX[1] = xx[1];
    
}

//Convert the Decimal to Binary
string NN::decToBinary(double input)
{
    //Create
    string output = "";
    int count = 0;
    int value = (int)input;
    
    //13 is chromosome length
    for(int i = 0; i < 13; i++)
    {
        if(value%2 == 0)
        {
            value = value/2;
            output = output + "0";
        }else{
            value = value/2;
            output = output + "1";
        }
        count++;
    }
    
    //Reverse
    string newOutPut = "";
    int reverse = 0;
    for(int i = count-1; i >= 0; i--)
    {
        newOutPut += output.at(i);
        reverse++;
    }
    
    return newOutPut;
}


//Set the Y array
void NN::setArrayY(double yy[2])
{
    arrayY[0] = yy[0];
    arrayY[1] = yy[1];

}

//Set the Z array
void NN::setArrayZ(double zz[2])
{
    arrayZ[0] = zz[0];
    arrayZ[1] = zz[1];

}

//Set the T array
void NN::setArrayT(double tt[2])
{
    arrayT[0] = tt[0];
    arrayT[1] = tt[1];

}

//WHAT IS GOING TO BE CHANGED
void NN::rotation(double input)
{

    //printf("first: %f \nsecond: %f \nthird: %f\n",(newNorth * (arrayX[0])) + (newEast * (arrayX[1])),(newNorth * (arrayY[0])) + (newEast * (arrayY[1])) + (newSouth * (arrayY[2])) + (newWest * (arrayY[3])),(newNorth * (arrayZ[0])) + (newEast * (arrayZ[1])) + (newSouth * (arrayZ[2])) + (newWest * (arrayZ[3])));
    
    //Change the proportion
    //input = input/600;
    
    //THIS IS FOR TEST>>>HAVE THIS AS OUTPUT
    double NEWOUTPUT = sig(input*arrayT[0]);
    
    
    //calculation
    double arrayTT[] = {input*arrayT[0],
                        input*arrayT[1]};
    
    double arrayTTSIG[2];
    arrayTTSIG[0] = sig(arrayTT[0]);
    arrayTTSIG[1] = sig(arrayTT[1]);
    
    double Xoutput = arrayTTSIG[0]*arrayX[0] + arrayTTSIG[1]*arrayX[1];
    double Youtput = arrayTTSIG[0]*arrayY[0] + arrayTTSIG[1]*arrayY[1];
    double Zoutput = arrayTTSIG[0]*arrayZ[0] + arrayTTSIG[1]*arrayZ[1];


    
    //Sigmoid Version of arrayZ
    /*double arrayZZ[2];
    arrayZZ[0] = sig(arrayTT[0]);
    arrayZZ[1] = sig(arrayTT[1]);
    
    //printf("first: %f\nsecond: %f\nthird %f\n",arrayZZ[0],arrayZZ[1],arrayZZ[2]);
    double arrayOutput[3];
    arrayOutput[0] = {(arrayZZ[0]*arrayX[0])+(arrayZZ[1]*arrayX[1])};
    arrayOutput[1] = {(arrayZZ[0]*arrayY[0])+(arrayZZ[1]*arrayY[1])};
    arrayOutput[2] = {(arrayZZ[0]*arrayZ[0])+(arrayZZ[1]*arrayZ[1])};
    */
    
    
    //Output Calculation
    //double output = (arrayZZ[0]* (arrayT[0]))+(arrayZZ[1]* (arrayT[1]))+(arrayZZ[2]* (arrayT[2]));
    //double sigdOutput = sig(output);
    
    double arrayOutputSig[3];
    outPut[0] = sig(Xoutput);//arrayTT[0];//sig(arrayTT[0]);
    outPut[1] = sig(Youtput);//arrayTT[1];//sig(arrayTT[1]);
    outPut[2] = sig(Zoutput);//arrayTT[2];//sig(arrayTT[2]);
    
    
    //Check if sigdOutput is nan
    /*if(isnan(sigdOutput))
    {
        sigdOutput = 0;
    }*/
    for(int i = 0; i < 3; i++)
    {
        if(isnan(arrayOutputSig[i]))
        {
            arrayOutputSig[i] = 0;
        }
    }
}

//Sigmoid function
double NN::sig(double input)
{
    //Sigmoid
    return 1 / (1 + exp(-5*input));
}

//Prints the Chromosomes
void NN::printChromosome()
{
    //W1 and W2
    CCLOG("W1");
    CCLOG("----------");
    for(int i = 0; i < 2; i++)
    {
        CCLOG("{W1: %f %f %f}",arrayX[0], arrayX[1], arrayX[2]);
    }
    CCLOG("\n");
}

//Returns the value of the X weights
double* NN::getArrayX()
{
    double* x = arrayX;
    
    return x;
}

//Returns the value of the Y weights
double* NN::getArrayY()
{
    double* y = arrayY;
    
    return y;
}

//Returns the value of the Z weights
double* NN::getArrayZ()
{
    double* z = arrayZ;
    
    return z;
}

//Returns the value of the T weights
double* NN::getArrayT()
{
    double* t = arrayT;
    
    return t;
}

//Enumeration for Physics Category
enum class PhysicsCategory {
    None = 0,
    Creature = (1 << 0),    // 1
    Food = (1 << 1), // 2
    All = PhysicsCategory::Creature | PhysicsCategory::Food, // 3
    Border = (1 << 2)
};

//Creates the scene
Scene* HelloWorld::createScene()
{
    // create the scene with physics enabled
    auto scene = Scene::createWithPhysics();
    
    // set gravity
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    
    // optional: set debug draw
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    //This gets the size and origin
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    
    
    //Sets the background
    auto background = DrawNode::create();
    background->drawSolidRect(origin, winSize, Color4F(0.6,0.6,0.6,1.0));
    background->setName("Background");
    
    this->addChild(background);
    
    ///Generation Count Lable
    auto generationCountLable = LabelTTF::create("Generation: ","Arial",24);
    generationCountLable->setPosition(Point(80,20));
    this->addChild(generationCountLable);
    
    
    ttf1 = CCLabelTTF::create("1", "Arial", 24);
    ttf1->setPosition(Point(150,20));
    ttf1->setAnchorPoint(ccp(0,0.5f));
    this->addChild(ttf1);
    
    //************************************************************************************************************************************************
    //Main SetUp
    
    srand(time(NULL));
    
    //Sets the num of creatures
    numberOfCreaturesActive = 0;
    
    numberOfFoodActive = 0;
    
    
    //Spawns the creatues
    spawnIndex = 0;
    for(int i = 0; i < numberOfCreatures; i++)
    {
        spawnIndex = i;
        spawnCreatures();
        
    }
    
    //Spawns the creatues NN
    spawnIndex = 0;
    for(int i = 0; i < numberOfCreatures; i++)
    {
        nets[i] = new NN();
    }
    
    //Creates the data for the creatures
    for(int i = 0; i < numberOfCreatures; i++)
    {
        cD[i] = new CreatureData();
    }

    
    
    
    //Spawn the Food
    spawnFoodIndex = 0;
    for(int i = 0; i < numberOfFood; i++)
    {
        spawnFood();
    
    }
    
    //Schedules the update() function
    scheduleUpdate();

    //Starts to listen to collision
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    //Sets time to 0
    _elapsedTime = 0;
    
    //Start number of generations
    numberOfGenerations = 1;
    
    //Display First Set of Creatures
    //updateFile();
    
    return true;
}

void HelloWorld::update(float delta)
{
    double randomNUMBER = RANDOM_NUM;
    
    
    //Time handling
    _elapsedTime += static_cast<unsigned>(delta * 1000.0f);
    if (_elapsedTime > 1000) {
        // 1 seconds has passed
        auto children = _children;
        for(auto child : children)
        {
            if(child->getName() == "Creature")
            {
                cD[child->getTag()]->updateCreature();
                //CCLOG("OUTPUT: %f %f %f", nets[child->getTag()]->outPut[0],nets[child->getTag()]->outPut[1],nets[child->getTag()]->outPut[2]);
                if(cD[child->getTag()]->getLifeSpan() == 0)
                {
                    child->removeFromParentAndCleanup(true);
                    //CCLOG("REMOVED");
                    numberOfCreaturesActive--;
                    
                    //-----------TEST-------------
                    //cD[child->getTag()]->setTotalAmountFood(0);
                }
            }
        }
        _elapsedTime = 0;
    }
    
    //This gets the size and origin
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    
    //
    auto children = _children;
    for(auto child : children)
    {
        
        if(child->getName() == "Creature"){
            //Updates the rotation
            updateCreature(child->getTag());//----->
            //float xPos = child->getPosition().x + cos(child->getRotation());
            //float yPos = child->getPosition().y + sin(child->getRotation());
            //child->setPosition(Vec2(xPos, yPos));
            
            //Checks if the creature is out of bounds and then puts it back in
            if(child->getPosition().x >= winSize.width + 3)
            {
                child->setPosition(origin.x, child->getPosition().y);
                //child->setPosition(child->getPosition().x - 3, child->getPosition().y);
                //cD[child->getTag()]->lifeSpanNulled();
            }
        
            if(child->getPosition().x <= origin.x - 3)
            {
                child->setPosition(winSize.width, child->getPosition().y);
                //child->setPosition(child->getPosition().x + 3, child->getPosition().y);
                //cD[child->getTag()]->lifeSpanNulled();
            }
        
            if(child->getPosition().y >= winSize.height + 3)
            {
                child->setPosition(child->getPosition().x, origin.y);
                //child->setPosition(child->getPosition().x, child->getPosition().y - 3);
                //cD[child->getTag()]->lifeSpanNulled();
            }
        
            if(child->getPosition().y <= origin.y - 3)
            {
                child->setPosition(child->getPosition().x, winSize.height);
                //child->setPosition(child->getPosition().x, child->getPosition().y + 3);
                //cD[child->getTag()]->lifeSpanNulled();
            }
        }
        
    }
    
    int NumberOFACTIVEFOOD = 0;
    for(auto child : children)
    {
        if(child->getName() == "Food")
        {
            NumberOFACTIVEFOOD++;
        }
    }
    
    while(NumberOFACTIVEFOOD < numberOfFood)
    {
        spawnFood();
    }
    
    if(numberOfCreaturesActive <= 9)
    {
        for(auto child : children)
        {
            if(child->getName() == "Creature")
            {
                child->removeFromParentAndCleanup(true);
            }
        }
        GeneticAlgorithm();
        
        
    }
}

void HelloWorld::updateFile()
{
    CCLOG("Generation: [%i]\n", numberOfGenerations);
    CCLOG("--------------------------------------\n");
    
    //Prints each Creature's (Weights, fitness, chromosome)
    for(int i = 0; i < numberOfCreatures; i++)
    {
        CCLOG("Creature[%i]\n",i);
        CCLOG("---------------\n");
        nets[i]->printChromosome();
        CCLOG("Fitness: %f\n", nets[i]->fitness);
        CCLOG("Chromosome: %s\n",nets[i]->chromosome.c_str());
        CCLOG("Total Amount of Food: %i\n",cD[i]->getTotalAmountFood());
    }
    CCLOG("--------------------------------------\n\n\n");
}

void HelloWorld::spawnCreatures()
{
    //This gets the size and origin
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    
    
    //Creature
    auto circle = DrawNode::create();
    circle->drawCircle(origin, 10, 0, 100, false, Color4F(1,6,1,1.0));
    
    Sprite* creature = Sprite::create();
    
    //Physics of creature
    // 1
    auto creatureSize = creature->getContentSize();
    auto physicsBody = PhysicsBody::createCircle(10);
    // 2
    physicsBody->setDynamic(true);
    // 3
    physicsBody->setCategoryBitmask((int)PhysicsCategory::Creature);
    physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
    physicsBody->setContactTestBitmask((int)PhysicsCategory::Food);
    
    creature->setPhysicsBody(physicsBody);
    
    creature->addChild(circle);
    
    //
    auto creatureContenctSize = creature->getContentSize();
    auto selfContentSize = this->getContentSize();
    
    //Handles Y
    int minY = creatureContenctSize.height/2;
    int maxY = selfContentSize.height - creatureContenctSize.height/2;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;
    
    //Handles X
    int minX = creatureContenctSize.width/2;
    int maxX = selfContentSize.width - creatureContenctSize.width/2;
    int rangeX = maxX - minX;
    int randomX = (rand() % rangeX) + minX;
    
    creature->setPosition(randomX, randomY);
    
    int minRot = 0;
    int maxRot = 360;
    int rangeRot = maxRot - minRot;
    int randomRot = (rand() % rangeRot) + minRot;
    
    creature->setRotation(randomRot);//was 180
    
    
    creature->setName("Creature");
    creature->setTag(spawnIndex);//The index when spawning it
    
    
    this->addChild(creature);
    
    numberOfCreaturesActive++;
    
}

void HelloWorld::spawnFood()
{
    //This gets the size and origin
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    
    //Creature
    auto circle = DrawNode::create();
    circle->drawCircle(origin, 5, 0, 100, false,Color4F(243,100,0,1.0));
    
    
    auto food = Sprite::create();
    
    //Physics Functionality
    auto foodSize = food->getContentSize();
    auto physicsBody = PhysicsBody::createCircle(5);
    physicsBody->setDynamic(true);
    physicsBody->setCategoryBitmask((int)PhysicsCategory::Food);
    physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
    physicsBody->setContactTestBitmask((int)PhysicsCategory::Creature);
    food->setPhysicsBody(physicsBody);
    
    food->addChild(circle);
    
    //
    auto foodContenctSize = food->getContentSize();
    auto selfContentSize = this->getContentSize();
    
    //Handles Y
    int minY = foodContenctSize.height/2;
    int maxY = selfContentSize.height - foodContenctSize.height/2;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;
    
    //Handles X
    int minX = foodContenctSize.width/2;
    int maxX = selfContentSize.width - foodContenctSize.width/2;
    int rangeX = maxX - minX;
    int randomX = (rand() % rangeX) + minX;
    
    food->setPosition(randomX, randomY);
    food->setName("Food");
    
    
    this->addChild(food);
    
    numberOfFoodActive++;
    
}

//Gets the distance
double HelloWorld::distance(double x1, double x2, double y1, double y2)
{
    return sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
}


//This is used to update the creatures rotation
void HelloWorld::updateCreature(int creatureID)
{
    //Get the new rotation from the
    auto children = _children;
    
    //Gets the creature with the creatureID
    Sprite* creature;
    for(auto child : children)
    {
        if(child->getTag() == creatureID)
        {
            creature = (Sprite*)child;
        }
    }
    
    //Gets the closest food to the creature
    Sprite* closestFood;
    double distanceFromClosedFood = -1;
    for(auto child : children)
    {
        if(child->getName() == "Food")
        {
            if(distanceFromClosedFood < 0)
            {
                closestFood = (Sprite*)child;
                distanceFromClosedFood = distance(creature->getPosition().x, closestFood->getPosition().x, creature->getPosition().y, closestFood->getPosition().y);
            }else{
                double distanceFromClosedFoodTemp = distance(creature->getPosition().x, child->getPosition().x, creature->getPosition().y, child->getPosition().y);
                if(distanceFromClosedFoodTemp < distanceFromClosedFood)
                {
                    closestFood->setPosition(Vec2(child->getPosition().x,child->getPosition().y));
                    distanceFromClosedFood = distanceFromClosedFoodTemp;
                }
            }
            
            
        }
    }
    
    double xClosestFood = closestFood->getPosition().x;
    double yClosestFood = closestFood->getPosition().y;
    
    //Directions
    /*double north = 0;
    double east = 0;
    double south = 0;
    double west = 0;*/
    
    double tempX = xClosestFood - creature->getPosition().x;
    double tempY = yClosestFood - creature->getPosition().y;
    /*if(tempX < 0)
    {
        west = tempX*(-1);
    }
    if(tempX > 0)
    {
        east = tempX;
    }
    if(tempY < 0)
    {
        south = tempY*(-1);
    }
    if(tempY > 0)
    {
        north = tempY;
    }*/
    
    
    //---TEST---
    double degree = getRotationSingleCoordinate(tempX, tempY);
    double sectoredDegree = 0;
    
    //Gets creature sector
    int sectorCreature = 0;
    if(creature->getRotation() >= 0 && creature->getRotation() < 90)
    {
        sectorCreature = 1;
        sectoredDegree = creature->getRotation();//I
    }else if(creature->getRotation() >= 90 && creature->getRotation() < 180)
    {
        sectorCreature = 2;
        sectoredDegree = 90 - creature->getRotation();//II
    }else if(creature->getRotation() >= 180 && creature->getRotation() < 270)
    {
        sectorCreature = 3;
        sectoredDegree = 180 - creature->getRotation();//III
    }else if(creature->getRotation() >= 270 && creature->getRotation() < 360)
    {
        sectorCreature = 4;
        sectoredDegree = 270 - creature->getRotation();//IV
    }
    
    //Gets sector of the food
    int sectorFood = 0;
    if(tempX >= 0)
    {
        if(tempY >= 0)
        {
            sectorFood = 1;
        }else{
            sectorFood = 4;
        }
    }else{
        if(tempY >= 0)
        {
            sectorFood = 2;
        }else{
            sectorFood = 3;
        }
    }
    
    //Sets input
    bool sameSector = false;
    bool inRange = false;
    if(sectorFood == sectorCreature)
    {
        sameSector = true;
    }
    
    //Checks if is inRange
    double rangeL = sectoredDegree - 20;
    double rangeR = sectoredDegree + 20;
    if(degree >= rangeL && degree <= rangeR)
    {
        inRange = true;
    }
    
    //double testOutPut1 = 0.6;
    //double testOutPut2 = 0.6;
    //double testOutPut3 = 0.4;

    
    
    //Gets the input
    double input = -0.8191;
    if(sameSector == true && inRange == true)
    {
        CCLOG("TEST");
        input = 0.8191;
        
        //testOutPut1 = 0.6;
        //testOutPut2 = 0.4;
        //testOutPut3 = 0.4;
        
    }else{
        distanceFromClosedFood = 0;
    }
    CCLOG("INPUT:: %f\n", input);
    
    
    
    nets[creatureID]->rotation(distanceFromClosedFood/600);
    double outPut1 = nets[creatureID]->outPut[0];
    double outPut2 = nets[creatureID]->outPut[1];
    double outPut3 = nets[creatureID]->outPut[2];
    //double changeOfRotation = rotationPost*360;
    
    //THE MAX OUTPUT and NODE
    double MAX_NODE = 480*0.8191;
    double MAX_OUTPUT = MAX_NODE*0.8191 + MAX_NODE*0.8191;
    
    //Gets the output of the net
    int decision = findMax(outPut1, outPut2, outPut3);
    
    //Sets the new rotation
    for(auto child : children)
    {
        if(child->getTag() == creatureID)
        {
            //Sets new Rotation of Creature
            CCLOG("OUTPUT::%f %f %f\n",outPut1, outPut2, outPut3);
            //printf("Rotation Post: %f\n",rotationPost);
            if(outPut1 >= 0.5)
            {
                float xPos = child->getPosition().x + cos(child->getRotation());
                float yPos = child->getPosition().y + sin(child->getRotation());
                child->setPosition(Vec2(xPos, yPos));
            }
            if(outPut2 >= 0.5)
            {
                child->setRotation(child->getRotation()-0.001);
            }
            
            if(outPut3 >= 0.5)
            {
                child->setRotation(child->getRotation()+0.001);
            }
         
            //int i = findMax(1,1,1);
            //Handles the move function
            /*if(decision == 1){
                float xPos = child->getPosition().x + cos(child->getRotation());//child->getRotation()
                float yPos = child->getPosition().y + sin(child->getRotation());//child->getRotation()
                child->setPosition(Vec2(xPos, yPos));
            }
            
            //Handles the left rotation
            if(decision == 2){
                child->setRotation(child->getRotation()-0.01);//0.01
            }
            
            //Handles the right rotation
            if(decision == 3){
                child->setRotation(child->getRotation()+0.01);//0.01
            }*/
            
            /*if(outPut1 <= 0.5)
            {
                //Set rotation
                child->setRotation(child->getRotation()+0.01);//0.01
                
                //Update the position
                float xPos = child->getPosition().x + cos(child->getRotation());//child->getRotation()
                float yPos = child->getPosition().y + sin(child->getRotation());//child->getRotation()
                child->setPosition(Vec2(xPos, yPos));
                
            }else{
            
                //Update the position
                float xPos = child->getPosition().x + cos(child->getRotation());//child->getRotation()
                float yPos = child->getPosition().y + sin(child->getRotation());//child->getRotation()
                child->setPosition(Vec2(xPos, yPos));
            }*/
            
            
            //------TEST------
            //Left/Middle/Right output
            /*if(changeOfRotation >= 190 && changeOfRotation < 223)
            {
                //Left
                child->setRotation(child->getRotation()-changeOfRotation);
            }
            
            if(changeOfRotation >= 223 && changeOfRotation < 256)
            {
                //Middle
                child->setRotation(child->getRotation());
            }
            
            if(changeOfRotation >= 256 && changeOfRotation < 290)
            {
                //Right
                child->setRotation(child->getRotation()+changeOfRotation);
            }*/
            
            //OTHER TEST
            /*if(rotationPost < 120 && rotationPost >= 0)
            {
                //Left
                child->setRotation(child->getRotation()-1);
            }
            else if(rotationPost < 240 && rotationPost >= 120)
            {
                //Right
                child->setRotation(child->getRotation());
            }
            else if(rotationPost < 360 && rotationPost >= 240)
            {
                //Right
                child->setRotation(child->getRotation()+1);
            }*/
            
            
            
            
            
        }
    }
}

int HelloWorld::findMax(double first, double second, double third)
{
    //The output
    int i = 0;
    if(first > second && first > third)
    {
        i = 1;
    }
    else if(second > first && second > third)
    {
        i = 2;
    }else if(third > first && third > second)
    {
        i = 3;
    }
    
    
    return i;
}

bool HelloWorld::onContactBegan(PhysicsContact &contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    //nodeA->removeFromParent();
    //nodeB->removeFromParent();
    
    //BOTH CAN BE REMOVED
    if(nodeB != NULL){
        if(nodeB->getName() == "Food"){
            nodeB->removeFromParentAndCleanup(true);
            spawnFood();
        
            //Adds more lifespan to a creature
            if(nodeA != NULL){
                int index = nodeA->getTag();
                cD[index]->lifeSpanExtended();
                cD[index]->incimentAmountOfFood();
                numberOfFoodActive--;
            }
        }
    }
    
    return true;
}

//Genetic algorithm Call
void HelloWorld::GeneticAlgorithm()
{
    
    //Get total fitness
    double totalFitness = 0;
    for(int i = 0; i < numberOfCreatures; i++)
    {
        if(cD[i]->getTotalAmountFood() == 200){
            CCLOG("FOUND!");
            
            //Stops program if found
            unscheduleUpdate();
        }else{
        float fitness = 1/(float)fabs((double)(200 - cD[i]->getTotalAmountFood()));
        nets[i]->fitness = fitness;
        totalFitness += fitness;
        }
    }
    
    //Prints the Previous Generation
    updateFile();
    
    NN newNets[numberOfCreatures];
    //Gets new set
    for(int i = 0; i < numberOfCreatures; i++)
    {
        int nn1 = Roulette(totalFitness);
        int nn2 = Roulette(totalFitness);
        
        //GA
        string newNetCrossOver = Crossover(nn1, nn2);//--->>>CrossOver
        string newNet = Mutate(newNetCrossOver);//--->>>Mutate
        
        //Weights to be added
        double xx[3];
        double yy[2];
        double zz[2];
        double tt[2];
        
        //Convert to a NN
        int x = 0;
        for(int i = 0; i < 14*2; i+=14)
        {
            string gene = newNet.substr(i, 14);
            string gene2 = newNet.substr(i, 13);
            //printf("X:%s\n",gene.c_str());
            
            string sign = gene.substr(0,1);
            if(sign == "1")
            {
                double decimalRepOfGene = binaryToDec(gene2);
                xx[x] = decimalRepOfGene/10000;
                x++;
            }else if(sign == "0")
            {
                double decimalRepOfGene = binaryToDec(gene2);
                xx[x] = -1*decimalRepOfGene/10000;
                x++;
            }
            
            
            
        }
        int y = 0;
        for(int i = 14*2; i < 14*4; i+=14)
        {
            string gene = newNet.substr(i, 14);
            string gene2 = newNet.substr(i, 13);
            //printf("Y:%s\n",gene.c_str());
            
            string sign = gene.substr(0,1);
            if(sign == "1")
            {
                double decimalRepOfGene = binaryToDec(gene2);
                yy[y] = decimalRepOfGene/10000;
                y++;
            }else if(sign == "0")
            {
                double decimalRepOfGene = binaryToDec(gene2);
                yy[y] = -1*decimalRepOfGene/10000;
                y++;
            }
            
        }
        int z = 0;
        for(int i = 14*4; i < 14*6; i+=14)
        {
            string gene = newNet.substr(i, 14);
            string gene2 = newNet.substr(i, 13);
            //printf("Z:%s\n",gene.c_str());
            
            string sign = gene.substr(0,1);
            if(sign == "1")
            {
                double decimalRepOfGene = binaryToDec(gene2);
                zz[z] = decimalRepOfGene/10000;
                z++;
            }else if(sign == "0")
            {
                double decimalRepOfGene = binaryToDec(gene2);
                zz[z] = -1*decimalRepOfGene/10000;
                z++;
            }
            
            
        }
        int t = 0;
        for(int i = 14*6; i < 14*8; i+=14)
        {
            string gene = newNet.substr(i, 14);
            string gene2 = newNet.substr(i, 13);
            //printf("T:%s\n",gene.c_str());
            
            string sign = gene.substr(0,1);
            if(sign == "1")
            {
                double decimalRepOfGene = binaryToDec(gene2);
                tt[t] = decimalRepOfGene/10000;
                t++;
            }else if(sign == "0")
            {
                double decimalRepOfGene = binaryToDec(gene2);
                tt[t] = -1*decimalRepOfGene/10000;
                t++;
            }
            //end+=16;
        }
        
        //Set new weights
        newNets[i].setArrayX(xx);
        newNets[i].setArrayY(yy);
        newNets[i].setArrayZ(zz);
        newNets[i].setArrayT(tt);
        
        
        //Re-sets the food
        auto children = _children;
        
        //Gets the creature with the creatureID
        numberOfFoodActive = 0;
        for(auto child : children)
        {
            if(child->getName() == "Food")
            {
                child->removeFromParentAndCleanup(true);
            }
        }
        
        for(int i = 0; i< numberOfFood; i++)
        {
            spawnFood();
        }
    }
    
    //Sets the spawn Index
    numberOfCreaturesActive = 0;
    
    
    //Spawns the creatues

    //Re-assigns the nets[]
    for(int i = 0; i < numberOfCreatures; i++)
    {
        nets[i]->setArrayX(newNets[i].getArrayX());
        nets[i]->setArrayY(newNets[i].getArrayY());
        nets[i]->setArrayZ(newNets[i].getArrayZ());
        nets[i]->setArrayT(newNets[i].getArrayT());
    }
    
    spawnIndex = 0;
    for(int i = 0; i < numberOfCreatures; i++)
    {
        spawnIndex = i;
        spawnCreatures();
        
    }
    
    
    //Creates the data for the creatures
    for(int i = 0; i < numberOfCreatures; i++)
    {
        cD[i] = new CreatureData();
    }
    
    //GENETIC ALGORITHM TRACKING DATA AND DISPLAY
    numberOfGenerations++;
    string textOfNumberOfGenerations = std::to_string(numberOfGenerations);
    ttf1->setString(textOfNumberOfGenerations);
    
    
}

//Crossover Function
string HelloWorld::Crossover(int nn1, int nn2)
{
    //Get genes of the two NN
    string first = nets[nn1]->chromosome;
    string newString = first;
    string second = nets[nn2]->chromosome;
    
    //Dependent on the crossover rate
    if (RANDOM_NUM < CROSSOVER_RATE)
    {
        //create a random crossover point
        int crossover = (int) (RANDOM_NUM * (14*8));
        
        newString = first.substr(0, crossover) + second.substr(crossover, (14*8));
    }
    
    return newString;
}

//Mutate Function
string HelloWorld::Mutate(string nn)
{
    for (int i=0; i < nn.length(); i++)
    {
        if (RANDOM_NUM < MUTATION_RATE)
        {
            if (nn.at(i) == '1')
                
                nn.at(i) = '0';
            
            else
                
                nn.at(i) = '1';
        }
    }
    return nn;
}

//Picks random creature
int HelloWorld::Roulette(double TotalFitness)
{
    //Takes a slice from the spectrem
    double sum = 0;
    double Slice = (double)(RANDOM_NUM * TotalFitness);
    //printf("Slice: %f Total Fitness: %f\n",Slice,TotalFitness);
    for(int i = 0; i < numberOfCreatures; i++)
    {
        sum += nets[i]->fitness;
        if(sum >= Slice)
        {
            return i;
        }
    }
    
    return 0;
}

//Converts the binary string to Decimal
double HelloWorld::binaryToDec(string input)
{
    double sum = 0;
    int count = (int)(input.size()) - 1;
    for(int i = 0; i < input.size(); i++)
    {
        double check = (input.at(i)-48);
        
        if(check == 1)
        {
            sum += pow(2,count);
            
        }
        count--;
        
    }
    return sum;
}

//Get rotation
double HelloWorld::getRotationSingleCoordinate(double x, double y)
{
    double degree = atan2(y, x);
    
    return degree;
}



