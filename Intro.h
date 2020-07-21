//Intro page
#ifndef INTRO_H
#define INTRO_H

typedef class Box
{
      public:
      
      /*Coordinates for the box assuming it is a rectangle or a square*/    
      
      int xLeft; 
      int yTop;   
      int xRight;         
      int yBottom;
      
      
      bool insideBox(int x, int y);
      void displayInfo(char fileName[]);  
      
};

#endif
      
      
     
      


