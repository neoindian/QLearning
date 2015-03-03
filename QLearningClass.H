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
#include <sstream>
#include <time.h>
#include <stdlib.h>


using namespace std;

class QLearningClass
{
  private:
    std::vector<double> values_;
    std::vector<string> nextState_;
    std::vector<string> currentState_;
    std::vector<string> direction_;
    string state_;

  public:
    double getValue(int index);
    string getNextState(int index);
    string getDirection(int index);
//Setters
    void setState(string state);
    void setValue(double value,int index);
    void setValue(double value);
    void setNextState(string nxtState);
    void setDirection(string dir);
   
};


class containerQLearningClass
{
public:
  containerQLearningClass(string fileName_);
  void claimReward(double& reward, string & nextState);
  void selectAction(int stateRowNum,string & action,int & actNum);
  int getMaxQValue(const string nextState);

  void flushToFile(void);
  void flushChkPointsToFile(void);

  void qLearningAlgorithm(void);

  std::vector<QLearningClass> qRVal_;
  std::vector<QLearningClass> qDashRVal_;
  std::vector<int> loopChkPoints;
  std::vector<double> qValPoints;
  std::vector<string> actions_;
};
 #endif 


