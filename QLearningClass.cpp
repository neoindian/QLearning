#include "QLearningClass.H"


int QLearningClass::getValue(int index)
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

void QLearningClass::setValue(int value)
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
         QLearningClass qL;
         qL.setState("1");
         cout<<"Continue::"<<endl;
         int count = 1;
         while(count <=4)
         { 
           sin >> dir >> nxtState >> reward; 
           cout << dir << " "<<nxtState << " "<<reward<<endl;
           qL.setDirection(dir);
           qL.setNextState(nxtState); 
           qL.setValue(reward);
           count++;
         }
         //inputFile.sync();
         q_.push_back(qL);
       }
       inputFile.close();
     }
}


int main(int argc , char * argv[])
{
string fileName_ = argv[1];
containerQLearningClass cQ_(fileName_);
return 0;
}


