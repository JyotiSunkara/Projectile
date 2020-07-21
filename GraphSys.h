//GraphSys.h
#ifndef GRAPHSYS_H
#define GRAPHSYS_H

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


// Rectangular boundaries   

typedef class Boundary {    //Typedef is an alias generating in data modifier

public: 
	int left;
	int top;
	int right;
	int bottom;
} RectT;

// Origin of the the coordinate system 

typedef struct Origin {
	int x;
	int y;
} OrgT;

typedef class  GraphSystem {
			
            
    public:         
            							/* The boundaries of the world coordinate system. I assumed bottom left as origin. */
	RectT Wview; // World View
	
										/* The extent of the computer  coordinate system. It assume left top is the origin
											and Y increases downwards */
	RectT Cview; // Computer View
	
	
           GraphSystem    CreateGraphSystem();
           void 		  DestroyGraphSystem();
           bool           InitialiseSystem();
           void 		  CloseSystem();
           void           InitialiseCView();
           void 		  Setworldview(int w, int h);
           int 		      GetCxCoord(float x);
           int 		      GetCyCoord(float x);
           int 		      GetWorldWidth();
           int 		      GetWorldHeight();
           int 		      GetCHeight();
           int 		      GetCWidth();
           OrgT 		  GetWorg();
           OrgT 		  GetCorg();
           int 		      GetScaledDist(float x);
           
	
} GraphSystemT;




#endif
