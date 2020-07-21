//IntroUtils.cpp
#include<iostream.h>
#include<fstream.h>
#include <math.h>
#include "intro.h"

bool Box::insideBox(int x, int y){
                             /*Checks whether the poniter click has been made inside the box
                              Box is assumed to be rectangle or square.*/
     if(x < xRight && x > xLeft){
          
          if(y < yBottom && y > yTop){
               return true;
               }
          }
          
     else{          
          return false;
          }
          
}
void Box::displayInfo(char fileName[]){
     /*In order to put information into the box
       Box is assumed to be rectangle or square*/ 
       
       char wordInfo[20];
       
       fstream ioFlow(fileName, ios::in | ios::out);
       
       ioFlow>>wordInfo;
       cout<<wordInfo;
       while(!ioFlow.eof())
       {
                           ioFlow>>wordInfo;
                           cout<<wordInfo;
                           }
}
/*If in box A then do graph and if X go back to menu page 
else if in box B then do display information and if X return to the main page */
