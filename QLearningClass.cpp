#include "QLearningClass.H"

int getIndex(const string s)
{
  string n = s.substr(1,s.length());
  int index = atoi(n.c_str());
  //cout<<"Index for "<<s<<" is "<<index<<endl;
  return index; 
}

double QLearningClass::getValue(int index)
{
   return values_[index];
}
string QLearningClass::getNextState(int index)
{
   return nextState_[index];
}
string QLearningClass::getDirection(int index)
{
   return direction_[index];
}

void QLearningClass::setValue(double value,int index)
{
   values_[index]=value;
}
void QLearningClass::setValue(double value)
{
   values_.push_back(value);
}
void QLearningClass::setNextState(string nxtState)
{
   nextState_.push_back(nxtState);
}
void QLearningClass::setDirection(string dir)
{
   direction_.push_back(dir);
   
}

void QLearningClass::setState(string state)
{
  state_=state;
}


containerQLearningClass::containerQLearningClass(string fileName_)
{
     actions_.push_back("u");
     actions_.push_back("d");
     actions_.push_back("l");
     actions_.push_back("r");
     ifstream inputFile;
     inputFile.open(fileName_.c_str(),ios::out | ios::app | ios::binary);
     string line="";
     if (inputFile.is_open())
     {
       string dir,nxtState;
       int reward;
       while(getline (inputFile,line) )
       {
         cout<< line <<endl;
         stringstream sin(line);
         QLearningClass qL,qLDash;
         qL.setState("1");
         cout<<"Continue::"<<endl;
         int count = 1;
         while(count <=4)
         { 
           sin >> dir >> nxtState >> reward; 
           //cout << dir << " "<<nxtState << " "<<reward<<endl;
           qL.setDirection(dir);
           qL.setNextState(nxtState); 
           qL.setValue(reward);
           qLDash=qL;
           count++;
         }
         //inputFile.sync();

         qRVal_.push_back(qL);
         qDashRVal_.push_back(qLDash);
       }
       inputFile.close();
     }
}

void containerQLearningClass::selectAction(int stateRowNum,string & action,int & actNum)
{
  while(1)
  {
    actNum= rand() % 4+ 1;
    
    //cout<<"Action selected:: "<< actNum<<endl;
    action=actions_[actNum-1];
    if((qRVal_[stateRowNum].getDirection(actNum-1)=="i")||
        (qRVal_[stateRowNum].getValue(actNum-1)==-99))
    {
       //cout<<"Invalid state"<<endl;
       continue;
    }
    else
        break;
  }
}
int containerQLearningClass::getMaxQValue(const string nextState)
{
   int index = getIndex(nextState);

   QLearningClass q=qDashRVal_[index-1];
   int maxV=0;
   for(int i=0;i<4;i++)
   {
     if ( (q.getValue(i) != -99) &&
          (q.getValue(i)>maxV))
     {
        maxV=q.getValue(i);
     }
   }
   return maxV;
}
void containerQLearningClass::qLearningAlgorithm(void)
{
  int curState=1;
  double oldVal=0,qVal=0;
  int loopCount=0,i=0;
  double reward=0;
  
  string nextState="";
  int actNum=0;
  string action="";
  while(1)
  {
      action="";
      reward=0; 
      if(curState==7)
      {
       curState=1;
       cout<<"Rewind"<<endl;
      }
      //Select a valid action for current state
      selectAction(curState-1,action,actNum);
      //Interprete the next state from the action
      nextState=qRVal_[curState-1].getNextState(actNum-1);
      //Get the immediate reward for going to the next state
      reward = qRVal_[curState-1].getValue(actNum-1);
      //Get the max value possible for the next state
      int maxQVal= getMaxQValue(nextState);
      //Get the q value for going to the next state 
      qVal = reward + (0.9 * maxQVal);
      //Get the current q value for the current state and action
      oldVal = qDashRVal_[curState-1].getValue(actNum-1);
      //Update the q value for current state and action
      qDashRVal_[curState-1].setValue(qVal,actNum-1);
      //If no change from previous then increment redundant counter
      if(oldVal == qVal)
         loopCount++;
      else
         loopCount=0;
      //This is the iteration count
      i++;
      loopChkPoints.push_back(i);
      qValPoints.push_back((qVal - oldVal));
      //qValPoints.push_back((qVal));
      cout<<"Iteration "<< i <<" current state "<<
      curState<<" action "<< actNum << "next state " << getIndex(nextState);
      cout<<" reward "<< reward << "qVal = "<<qVal 
<<" old val "<<oldVal << " Max Q Val "<<maxQVal<<endl;
      if (loopCount > 51)
         break;
     if(nextState=="s7")
     {
        curState=1;
        cout<<"Rewind"<<endl;
     }
      else
        //Convert the string state to index
        curState=getIndex(nextState);
      oldVal=qVal; 
      //sleep(1);
  }

  int x = 0;
  /*while(x<loopChkPoints.size())
  {
     x++;
     cout<<"Loop chk:: " <<loopChkPoints[x]; 
     cout<<"Q val   :: " <<qValPoints[x]; 
     cout<<endl;
  }*/

}

void containerQLearningClass::claimReward(double & reward, string & nextState)
{

}

void containerQLearningClass::flushToFile(void)
{
   ofstream ofs;
   ofs.open ("test.txt", std::ofstream::out | std::ofstream::app);
   int i =0;
   while(i<qDashRVal_.size())
   {
     ofs<<qDashRVal_[i].getValue(0) << " ";
     ofs<<qDashRVal_[i].getValue(1) << " ";
     ofs<<qDashRVal_[i].getValue(2) << " ";
     ofs<<qDashRVal_[i].getValue(3) << " ";
     ofs<<endl;
     i++;
   }
   ofs.close();
}

void containerQLearningClass::flushChkPointsToFile(void)
{
   ofstream ofs;
   ofs.open ("chkpoints.txt", std::ofstream::out | std::ofstream::app);
   int i =0;
   vector<int>::iterator it = loopChkPoints.begin();
   while(it!=loopChkPoints.end())
   {
      ofs<<*(it)<<" ";
      it++;
   }
   ofs<<endl;
   vector<double>::iterator itval = qValPoints.begin();
   while(itval!=qValPoints.end())
   {
      ofs<<*(itval)<<" ";
      itval++;
   }
   ofs.close();
}


int main(int argc , char * argv[])
{
   string fileName_ = argv[1];
   containerQLearningClass cQ_(fileName_);
   int count = 0;
   cQ_.qLearningAlgorithm();
   cQ_.flushToFile();
   cQ_.flushChkPointsToFile();
   return 0;
}


