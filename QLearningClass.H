/*
* Author: Nishant Pattanaik
*
* File  :QLearningClass.cpp
*
* Date C: March 2 , 2015
*
*
* Description: This file contains the class declarations for
*              holding the Q Learning parameters. 
*
*/


#ifndef __QLEARNING_CLASS__
#define __QLEARNING_CLASS__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

class QLearningClass
{
  private:
    std::vector<int> values_;
    std::vector<string> nextState_;
    std::vector<string> currentState_;
    std::vector<string> direction_;

  public:
    int getValue(int index);
    string getNextState(int index);
    string getDirection(int index);

};

class containerQLearningClass
{
public:
  containerQLearningClass(string fileName_);
};
 #endif 

