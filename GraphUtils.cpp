//GraphUtils.cpp
#include <graphics.h>

#include <stdlib.h>

#include <stdio.h>

#include <conio.h>

#include "graphsys.h"


/* Initialize the computer coordinate system using the dimensions of the
window */
GraphSystem r; 
extern GraphSystem g;

//Initialise computer view
void GraphSystem::InitialiseCView() {
	memset(&r.Cview,0, sizeof(r.Cview));        //Memeset to initialise to zero
	r.Cview.right = getmaxwidth();
	r.Cview.bottom = getwindowheight ();
}

//Initialize the graphics system
bool GraphSystem::InitialiseSystem() {

   int gdriver = EGA, gmode, errorcode;
   char name[] = "";

   //Initialize graphics mode
   initgraph(&gdriver, &gmode, name);



   //Read result of initialization
   errorcode = graphresult();
   initwindow(getmaxwidth( ), getmaxheight( ),"Projectile Project");
   
   



   if (errorcode != grOk)    //An error occurred 

   {

      return false;              //Return with error code 

   }

   memset(&r.Cview,0, sizeof(r.Cview));
   memset(&r.Wview,0, sizeof(r.Wview));
   r.InitialiseCView();
   return true;
}

//Shut down the graphics system
void GraphSystem::CloseSystem() {
	closegraph();
	exit(0);
}

/*Make  the transformnation for world view  and bottom left as origin
with scaled paramaters keeping aspect ratios intact
Using simple coordinate geometry transformations
The Basic idea is:
Given Two rectangles, with their coordinates, assume they are similar rectangles i.e ratio of sides
is same. Hence using basic rations we can go from one system to other
*/


void GraphSystem::Setworldview(int w, int h) {
    r.Wview.left   = 0;
    r.Wview.right  = w;
    r.Wview.top    = h;
    r.Wview.bottom = 0;
    
	float aspect = (float)r.GetCWidth()/ r.GetCHeight();
	
	if ( aspect > 1.0 ) {
    	r.Wview.right  = w;
    	r.Wview.top    = (int) (w / aspect);
	} else {
    	r.Wview.top    = h;
    	r.Wview.right  = (int) (h * aspect);
	}
}

//Get X coordinate in computer view given world coordinate

int GraphSystem::GetCxCoord(float x) {

	float xDist  = x - r.Wview.left;
	float cWidth = r.GetCWidth();

	float wWidth  = r.GetWorldWidth();
	float cDist = xDist * cWidth / wWidth;
	return (int)cDist + r.Cview.left;
}

//Get Y coordinate in computer view given world coordinate
int GraphSystem::GetCyCoord(float y) {

	float yDist    = r.Wview.top - y;
	float cHeight  = r.GetCHeight();

	float wHeight  = r.GetWorldHeight();

	float cDist = yDist * cHeight / wHeight;
	return (int)cDist + r.Cview.left;
}

int GraphSystem::GetWorldWidth() {

	return r.Wview.right - r.Wview.left;
}

int GraphSystem::GetWorldHeight() {

	return r.Wview.top - r.Wview.bottom;
}

int GraphSystem::GetCHeight() {
   	return r.Cview.bottom - r.Cview.top;
}

int GraphSystem::GetCWidth() {

	return r.Cview.right - r.Cview.left;
}

OrgT GraphSystem::GetWorg() {
	OrgT o;
	o.x = r.Wview.left;
	o.y = r.Wview.bottom;
	return o;
}


int GraphSystem::GetScaledDist(float dist) {
    return r.GetCxCoord(dist);

}
