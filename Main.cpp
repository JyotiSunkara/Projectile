//Main.cpp
#include <cstdlib>

#include <iostream>

#include<process.h>

#include <graphics.h>

#include "graphsys.h"

#include <stdio.h>

#include "parabola.h"

#include "intro.h"

using namespace std;

/* Width and Height of the Screen in Metres
We assume Bottom left is the origin of the coordinate system
*/

#define MAX_WIDTH   (10000)   /* In metres */
#define MAX_HEIGHT  (1200)   /* In metres */

#define BALL_RADIUS     (100)
#define TEXT_COLOR      (COLOR(255,255,255))
#define LINE_COLOR      (COLOR(255,0,255))
#define BALL_FILLCOLOR  (11)

#define DISPPARAM_XPOS (20)
#define DISPPARAM_YPOS (60)


#define DISPATTR_XPOS (20)
#define DISPATTR_YPOS (40)

#define MAX_POINTS (1024)

GraphSystem g;
extern Parabola_t    p;

void runloop();
void menupage();
//Test function to test the graphics */
int testDraw() {
   /* Draw ellipse */
   int stangle = 0, endangle = 360;

   int xradius = 2400, yradius = 1000;
   int closeSide = 5;
   
   int midx = 10;

   int midy = 10;

    ellipse( g.GetCxCoord(midx), g.GetCyCoord(midy), stangle, endangle,
   			g.GetScaledDist(xradius), g.GetScaledDist(yradius));

	char buffer [ 256];
	snprintf(buffer, sizeof(buffer), "midx = %d converted midx %d \n" , midx, g.GetCxCoord(midx));
	outtext(buffer);

}


static int pts[MAX_POINTS * 2];
int num_pts = 0;
void init_points() {
	memset(&pts[0], 0, sizeof(pts));
	num_pts = 0;
}

void add_point(int x, int y) {
	pts[num_pts*2] = x;
	pts[num_pts*2 + 1] = y;
	num_pts++;
}

//Draw circle at the given place in world coordinate system
void drawCircle(float x, float y) {

    setfillstyle(SOLID_FILL, BALL_FILLCOLOR);
    fillellipse( g.GetCxCoord(x), g.GetCyCoord(y),
				 g.GetScaledDist(BALL_RADIUS), g.GetScaledDist(BALL_RADIUS));
	add_point(g.GetCxCoord(x), g.GetCyCoord(y));
}

static float min_speed = 200;
static float max_speed = 350;
static float inc_speed =  10;

static float min_angle = 30;
static float max_angle = 85;
static float inc_angle =  5;


static float cur_speed = min_speed;
static float cur_angle = min_angle;

static void reset() {

	cur_speed = min_speed;
	cur_angle = min_angle;
}

static void incr_speed() {

	cur_speed = MIN(max_speed, cur_speed + inc_speed);
}

static void decr_speed() {

	cur_speed = MAX(min_speed, cur_speed - inc_speed);
}


static void incr_angle() {

	cur_angle = MIN(max_angle, cur_angle + inc_angle);

}

static void decr_angle() {
	cur_angle = MAX(min_angle, cur_angle - inc_angle);
}



static void disp_params() {
	char digit_string[256];
	setcolor(TEXT_COLOR);
	
    sprintf(digit_string, "Speed = %6.2f m/s Angle = %6.2f degrees", cur_speed, cur_angle);

    outtextxy(DISPPARAM_XPOS, DISPPARAM_YPOS, digit_string);
}

static void disp_attrs(int t, float tottime, float x, float y) {
    char digit_string[256];
	setcolor(TEXT_COLOR);
    sprintf(digit_string, "Total time = %6.2fs Current time = %3d s             Current X = %6.2f m Current Y = %6.2f m", tottime, t, x,y);

    outtextxy(DISPATTR_XPOS, DISPATTR_YPOS, digit_string);
}


void redraw() {

   p.CreateParabola(cur_speed, cur_angle);
   float totTime = p.GetT();
   
   int deltaT = 2;
   int t;
   init_points();
   for( t = 0 ; t <= (int)totTime; t = t + deltaT )
   {

	  float x = p.GetR(t);
	  float y = p.GetH(t);
	  
	  disp_attrs(t,totTime, x,y);
	  disp_params();
	  drawCircle(x,y);
	  setcolor(TEXT_COLOR);
	  drawpoly(num_pts, &pts[0]);
      delay(100);

      clearviewport();
   }

}

static void disp_instruc(){
       
       
       initwindow(1000,600,"Instructions");
      
       
       setlinestyle(SOLID_LINE, 1 ,3);
       setcolor(TEXT_COLOR);
       rectangle(100,100,160,160);//Up
       rectangle(100,200,160,260);//Down
       rectangle(100,300,160,360);//Right
       rectangle(100,400,160,460);//Left
       rectangle(500,100,560,160);//M
       rectangle(500,200,560,260);//X
       rectangle(100,500,160,560);//Space
       
       settextstyle(COMPLEX_FONT,HORIZ_DIR, 1);
       
       outtextxy(120,120, "Up");
       outtextxy(110,220, "Down");
       outtextxy(103,320, "Right");
       outtextxy(110,420, "Left");
       outtextxy(110,520, "Home");
       outtextxy(525,120, "M");
       outtextxy(525,220, "X");
       
       outtextxy(250,120, "Increment angle");
       outtextxy(270,140, "by 5 degrees");
       outtextxy(250,220, "Decrement angle");
       outtextxy(270,240, "by 5 degrees");
       outtextxy(250,320, "Increment speed");
       outtextxy(270,340, "by 10 m/s");
       outtextxy(250,420, "Decrement speed");
       outtextxy(270,440, "by 10 m/s");
       outtextxy(250,520, "Reset speed to 200m/s");
       outtextxy(250,540, "and angle to 30 degrees");
       outtextxy(655,120, "Menu Page");
       outtextxy(655,220, "Exit");
     
              
       
       char c = 0;
      
       while(true){ 
            fflush(stdin);
            c = (char) getch( );
            delay(10);
            
            if(c == 'm' || c == 'M'){

            closegraph();
            menupage();
            return;
            
            }
            
            if(c == 'X' || c=='x'){
                 
                 closegraph();
                 return;}
            
         };
      
       
}
static void disp_info() {

    initwindow(1400,500,"Information");
	setcolor(TEXT_COLOR);
	int x = DISPATTR_XPOS;
	int y = DISPATTR_YPOS;
    
   

	
    char *info[] = {"Range:  Total horizontal distance travelled by the projectile."," ",
    				"Velocity: The horizontal velocity of a projectile is constant.", "The vertical velocity of a projectile changes by 9.8 m/s each second."," ",
    				"Acceleration: There is a vertical acceleration caused by gravity has a numerical value of 9.8 m/s/s."," ",
    				"Time of flight: The time of flight only depends on the initial velocity, the launch angle , and the acceleration due to gravity."," ",
    				"Angle of projection: An object launched into projectile motion will have an initial launch angle anywhere from 0 to 90 degrees."," ",
    				""
    				};

	for ( int i = 0; i < 1024, strlen(info[i])!= 0; i++)	
	{		
		 outtextxy(x, y, info[i]);
		 y +=30;
	}	
    
    char c = 0;
    while(true)
    {    fflush(stdin);
         c = (char) getch( );
         delay(200);
         
         if(c == 'm' || c == 'M'){
         closegraph();
         menupage();
          return;}
         
         if(c == 'X' || c=='x'){
                 
                 closegraph();
                 return;}
         
         
         };

         
}
    
void menuloop() {
	char c = 0;
	/* kick start the first motion */
	redraw();
	 do
	    {
	        c = (char) getch( );
	        if (c != 0) {
                    if ( c == 'm' || c == 'M') {
                    closegraph();
	        		menupage(); 
				}
				redraw();
	            cout << "That is ASCII value: " << (int) c << endl;
			} 
              else {   // Process one of the special keys:
	            c = (char) getch( );
	            switch (c)

	            {
	                case KEY_HOME:    reset();      break;

	                case KEY_UP  :    incr_angle(); break;

	                case KEY_DOWN:    decr_angle(); break;

	                case KEY_RIGHT:   incr_speed(); break;

	                case KEY_LEFT:    decr_speed(); break;

	                default: break;
	            }
	            
                redraw();
	        }

	    }while ((c != 'x') && (c != 'X'));
		return;
}

void menupage()
{
     initwindow(700,500, "Menu Page");
     int x,y;
     
     setlinestyle(SOLID_LINE, 1 ,3);
     setcolor(11);
     rectangle(130,100,530,180);
     rectangle(130,200,530,280);
     rectangle(130,300,530,380);
          
     setcolor(15);
     settextstyle(COMPLEX_FONT,HORIZ_DIR, 4);
     outtextxy(220,125, "Instructions");
     outtextxy(220,225, "Information");
     outtextxy(220,325, "Projectile");
     
     while(!ismouseclick(WM_LBUTTONDOWN))
     {delay(100);}
     getmouseclick(WM_LBUTTONDOWN, x, y);
     outstreamxy(x,y);
     
     if(x >= 130 && x <= 530 && y >= 100 && y <= 180)
     {
           disp_instruc();
           
           }
     
     else if(x >= 130 && x <= 530 && y >= 200 && y <= 280)
     {
          disp_info();
          }
     
     else if(x >= 130 && x <= 530 && y >= 300 && y <= 380)
     {
           g.InitialiseSystem();

           setcolor(COLOR(0,255,0));

           g.Setworldview(MAX_WIDTH,MAX_HEIGHT);

           menuloop();

           closegraph();
          
          }
       
   
} 

int main()
{
  
  menupage();

   return 0;
}
