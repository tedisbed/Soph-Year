/* Author: Nick Palutsis & Teddy Brombach
Class: CSE 20211
Final Project
Date: December 13, 2015 */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "gfx4.h"

struct ship{
   double x;
   double y;
   double *pX;
   double *pY;
   double theta;
   int r;
   int v;
   int exists;
};

void draw_falcon(int, double, int, int);
void draw_fighter(int, double, int, int, int);
int collision(int, int, int, int, int, int);
void infinite_edge(int, int, int, double *, double *);
int main()
{
	int wd;
	int ht;
	int waittime = 20000;
	int play;
	int level = 1;
	int win = 0;
	int otherkey = 0;
	int impact = 0;
	int r = 2;
	int v = 3;
	double dtheta = .1;
	char c;
	
	struct ship falcon;
	struct ship fighter1;
	struct ship fighter2;
	struct ship fighter3;
	struct ship fighter4;
	
	wd = gfx_screenwidth()*2/3;
   ht = gfx_screenheight()*2/3;
	
	gfx_open(wd, ht, "Star Wars");  // Open a new window for drawing.
	
   while(c != 'q'){
      while(level <= 4){
         gfx_clear();
         gfx_flush();
         gfx_color(255, 0, 0);
         if(level == 1)
            gfx_text(wd/2, ht/2-20, "LEVEL: 1");
         else if(level == 2)
            gfx_text(wd/2, ht/2-20, "LEVEL: 2");
         else if(level == 3)
            gfx_text(wd/2, ht/2-20, "LEVEL: 3");
         else if(level == 4)
            gfx_text(wd/2, ht/2-20, "LEVEL: 4");
         gfx_text(wd/2, ht/2, "Press 's' to start");
         gfx_text(wd/2, ht/2+20, "Press 'q' to quit");
         gfx_text(wd/2, ht/2+60, "Speed: Press '1' for slow enemies");
         gfx_text(wd/2, ht/2+80, "Speed: Press '2' for medium enemies");
         gfx_text(wd/2, ht/2+100, "Speed: Press '3' for fast enemies");
         gfx_text(wd/2, ht/2+120, "Size: Press '4' for small enemies");
         gfx_text(wd/2, ht/2+140, "Size: Press '5' for medium enemies");
         gfx_text(wd/2, ht/2+160, "Size: Press '6' for large enemies");
         gfx_text(wd/2, ht/2+200, "J: Turn counterclockwise");
         gfx_text(wd/2, ht/2+220, "L: Turn clockwise");
         gfx_text(wd/2, ht/2+240, "I: Increase speed");
         gfx_text(wd/2, ht/2+260, "K: Slow down / Reverse");
         gfx_text(wd/2, ht/2+280, "Spacebar: Shoot laser");
         c = gfx_wait();
         if(c == 's'){
            play = 1;
         }
         else if(c == '1')
            v = 1;
         else if(c == '2')
            v = 3;
         else if(c == '3')
            v = 5;
         else if(c == '4')
            r = 1;
         else if(c == '5')
            r = 2;
         else if(c == '6')
            r = 3;
         else if(c == 'q')
            break;
         else{
            play = 0;
            otherkey = 1;
         }

	      falcon.x = wd/2;
	      falcon.y = ht/2;
	      falcon.pX = &falcon.x;
	      falcon.pY = &falcon.y;
	      falcon.r = ht/25;
	      falcon.theta = 0;
	      falcon.v = 1;
	
	      fighter1.x = 0;
	      fighter1.y = 0;
	      fighter1.pX = &fighter1.x;
	      fighter1.pY = &fighter1.y;
	      fighter1.r = ht/60*r;
	      fighter1.theta = M_PI/3;
	      fighter1.v = v;
	      fighter1.exists = 0;

	      fighter2.x = wd;
	      fighter2.y = ht;
	      fighter2.pX = &fighter2.x;
	      fighter2.pY = &fighter2.y;
	      fighter2.r = ht/60*r;
	      fighter2.theta = -M_PI/2;
	      fighter2.v = 1;
	      fighter2.exists = 0;

	      fighter3.x = 0;
	      fighter3.y = ht;
	      fighter3.pX = &fighter3.x;
	      fighter3.pY = &fighter3.y;
	      fighter3.r = ht/60*r;
	      fighter3.theta = -M_PI/3;
	      fighter3.v = 1;
	      fighter3.exists = 0;
	
	      fighter4.x = wd;
	      fighter4.y = 0;
	      fighter4.pX = &fighter3.x;
	      fighter4.pY = &fighter3.y;
	      fighter4.r = ht/60*r;
	      fighter4.theta = M_PI/2;
	      fighter4.v = 1;
	      fighter4.exists = 0;
	
         if(level == 1)
            fighter1.exists = 1;
         else if(level == 2){
            fighter1.exists = 1;
            fighter2.exists = 1;
         }
         else if(level == 3){
            fighter1.exists = 1;
            fighter2.exists = 1;
            fighter3.exists = 1;
         }
         else if(level == 4){
            fighter1.exists = 1;
            fighter2.exists = 1;
            fighter3.exists = 1;
            fighter4.exists = 1;
         }
         
	      while(play){   
		      gfx_clear();
		      gfx_flush;
		      
		      draw_falcon(falcon.r, falcon.theta, falcon.x, falcon.y);
		      draw_fighter(fighter1.r, fighter1.theta, fighter1.x, fighter1.y, fighter1.exists);
		      draw_fighter(fighter2.r, fighter2.theta, fighter2.x, fighter2.y, fighter2.exists);
		      draw_fighter(fighter3.r, fighter3.theta, fighter3.x, fighter3.y, fighter3.exists);
		      draw_fighter(fighter4.r, fighter4.theta, fighter4.x, fighter4.y, fighter4.exists);

		      gfx_flush;
		      usleep(waittime);      // Pause for set number of seconds

		      if(gfx_event_waiting()) { 
			      c = gfx_wait();
			      if(c == 'q')		// Quits program
				      return 0;
			      else if(c == 'j')
				      falcon.theta = falcon.theta - dtheta;
			      else if(c == 'l')
				      falcon.theta = falcon.theta + dtheta;
			      else if(c == 'i'){
				      if(falcon.v <= 5)
					      falcon.v++;
			      }
			      else if(c == 'k'){
				      if(falcon.v >= -3)
					      falcon.v--;
			      }
			      else if(c == ' '){
			         int i;
			         int r = 0;
			         double x;
			         double y;
		            x = r*cos(falcon.theta) + falcon.x;
		            y = r*sin(falcon.theta) + falcon.y;
			         while(!collision(x, y, 0, fighter1.x, fighter1.y, fighter1.r) &&
			               !collision(x, y, 0, fighter2.x, fighter2.y, fighter2.r) &&
			               !collision(x, y, 0, fighter3.x, fighter3.y, fighter3.r) &&
			               !collision(x, y, 0, fighter4.x, fighter4.y, fighter4.r) &&
			               (x > 0 && x < wd && y > 0 && y < ht)){
			            x = r*cos(falcon.theta) + falcon.x;
			            y = r*sin(falcon.theta) + falcon.y;
			            gfx_color(255, 0, 0);
			            gfx_line(falcon.x + 5*cos(falcon.theta), falcon.y + 5*sin(falcon.theta), x, y);
	               	draw_falcon(falcon.r, falcon.theta, falcon.x, falcon.y);
	               	draw_fighter(fighter1.r, fighter1.theta, fighter1.x, fighter1.y, fighter1.exists);
	               	draw_fighter(fighter2.r, fighter2.theta, fighter2.x, fighter2.y, fighter2.exists);
	               	draw_fighter(fighter3.r, fighter3.theta, fighter3.x, fighter3.y, fighter3.exists);
	               	draw_fighter(fighter4.r, fighter4.theta, fighter4.x, fighter4.y, fighter4.exists);
			            r++;
			            usleep(1000);
			            gfx_flush;
			         }
			         if(collision(x, y, 0, fighter1.x, fighter1.y, fighter1.r))
			            fighter1.exists = 0;
			         else if(collision(x, y, 0, fighter2.x, fighter2.y, fighter2.r))
			            fighter2.exists = 0;
			         else if(collision(x, y, 0, fighter3.x, fighter3.y, fighter3.r))
			            fighter3.exists = 0;
			         else if(collision(x, y, 0, fighter4.x, fighter4.y, fighter4.r))
			            fighter4.exists = 0;
		         }
			         
		      }

		      fighter1.theta = atan2((falcon.y-fighter1.y), (falcon.x-fighter1.x));
		      fighter2.theta = atan2((falcon.y-fighter2.y), (falcon.x-fighter2.x));
		      fighter3.theta = atan2((falcon.y-fighter3.y), (falcon.x-fighter3.x));
		      fighter4.theta = atan2((falcon.y-fighter4.y), (falcon.x-fighter4.x));
          
		      falcon.x = falcon.x + falcon.v * cos(falcon.theta);
		      falcon.y = falcon.y + falcon.v * sin(falcon.theta);
		      fighter1.x = fighter1.x + fighter1.v * cos(fighter1.theta);
		      fighter1.y = fighter1.y + fighter1.v * sin(fighter1.theta);
		      fighter2.x = fighter2.x + fighter2.v * cos(fighter2.theta);
		      fighter2.y = fighter2.y + fighter2.v * sin(fighter2.theta);
		      fighter3.x = fighter3.x + fighter3.v * cos(fighter3.theta);
		      fighter3.y = fighter3.y + fighter3.v * sin(fighter3.theta);
		      fighter4.x = fighter4.x + fighter4.v * cos(fighter4.theta);
		      fighter4.y = fighter4.y + fighter4.v * sin(fighter4.theta);
		
		      infinite_edge(wd, ht, falcon.r, falcon.pX, falcon.pY);
		
		      if(collision(falcon.x, falcon.y, falcon.r+5, fighter1.x, fighter1.y, fighter1.r+5) && fighter1.exists){
		         impact = 1;
		         break;
	         }
		      else if(collision(falcon.x, falcon.y, falcon.r+5, fighter2.x, fighter2.y, fighter2.r+5) && fighter2.exists){
		         impact = 1;
		         break;
	         }
		      else if(collision(falcon.x, falcon.y, falcon.r+5, fighter3.x, fighter3.y, fighter3.r+5) && fighter3.exists){
		         impact = 1;
		         break;
	         }
		      else if(collision(falcon.x, falcon.y, falcon.r+5, fighter4.x, fighter4.y, fighter4.r+5) && fighter4.exists){
		         impact = 1;
		         break;
	         }
		         
            if(!fighter1.exists && !fighter2.exists && !fighter3.exists && !fighter4.exists){
               win = 1;
               break;
            }
	      }
	      gfx_clear();
	      gfx_color(255, 0, 0);
	      int counter = 0;
	      if(impact){
	         while(counter < 100){
	            gfx_clear();
	            gfx_text(wd/2, ht/2, "GAME OVER");
	            level = 1;
	            impact = 0;
	            counter++;
	            usleep(20000);
	            gfx_flush();
            }
            break;
         }
	      else if(win && level == 4){
	         while(counter < 100){
	            gfx_clear();
	            gfx_text(wd/2, ht/2, "YOU WIN!");
	            level = 1;
	            win = 0;
	            counter++;
	            usleep(20000);
	            gfx_flush();
            }
            break;
         }
	      else if(win){
            while(counter < 100){
	            gfx_clear();
	            gfx_text(wd/2, ht/2, "NEXT LEVEL");
	            counter++;
	            win = 0;
	            usleep(20000);
	            gfx_flush();
            }
            level++;
            break;
         }
         win = 0;
         impact = 0;
         otherkey = 0;
      }
   }
	return 0;
}
//***********************************************************************************
//******************************* F U N C T I O N S *********************************
//***********************************************************************************

void draw_falcon(int r, double theta, int xc, int yc){
   gfx_color(200, 200, 200);
	gfx_fill_circle(xc, yc, r);
	XPoint mypts1[] = { {r*cos(theta + M_PI/15) + xc, r*sin(theta + M_PI/15)+yc},
		{r*cos(theta + M_PI/3) + xc, r*sin(theta + M_PI/3) + yc},
		{r*cos(theta + M_PI/12)*5/3 + xc, r*sin(theta + M_PI/12)*5/3 + yc},
		{r*cos(theta + M_PI/25)*19/12 + xc, r*sin(theta + M_PI/25)*19/12 + yc} };
	int sz1 = sizeof(mypts1)/sizeof(XPoint);
	gfx_fill_polygon(mypts1, sz1);
	XPoint mypts2[] = { {r*cos(theta - M_PI/15) + xc, r*sin(theta - M_PI/15)+yc},
		{r*cos(theta - M_PI/3) + xc, r*sin(theta - M_PI/3) + yc},
		{r*cos(theta - M_PI/12)*5/3 + xc, r*sin(theta - M_PI/12)*5/3 + yc},
		{r*cos(theta - M_PI/25)*19/12 + xc, r*sin(theta - M_PI/25)*19/12 + yc} };
	int sz2 = sizeof(mypts2)/sizeof(XPoint);
	gfx_fill_polygon(mypts2, sz2);  
	gfx_color(0, 0, 0);
	gfx_circle(xc, yc, r/4);
	gfx_line(r*cos(theta + M_PI/15) + xc, r*sin(theta + M_PI/15)+yc, (r/4)*cos(theta + M_PI/3) + xc, (r/4)*sin(theta + M_PI/3) + yc);
	gfx_line(r*cos(theta - M_PI/15) + xc, r*sin(theta - M_PI/15)+yc, (r/4)*cos(theta - M_PI/3) + xc, (r/4)*sin(theta - M_PI/3) + yc);
	gfx_line((r/4)*cos(theta + M_PI*4/3) + xc, (r/4)*sin(theta + M_PI*4/3) + yc, r*cos(theta + M_PI*4/3) + xc, r*sin(theta + M_PI*4/3) + yc);
	gfx_line((r/4)*cos(theta - M_PI*4/3) + xc, (r/4)*sin(theta - M_PI*4/3) + yc, r*cos(theta - M_PI*4/3) + xc, r*sin(theta - M_PI*4/3) + yc);
	gfx_line((r/4)*cos(theta + M_PI*3/2) + xc, (r/4)*sin(theta + M_PI*3/2) + yc, r*cos(theta + M_PI*3/2) + xc, r*sin(theta + M_PI*3/2) + yc);
	gfx_line((r/4)*cos(theta - M_PI*3/2) + xc, (r/4)*sin(theta - M_PI*3/2) + yc, r*cos(theta - M_PI*3/2) + xc, r*sin(theta - M_PI*3/2) + yc);

	gfx_fill_circle(r*cos(theta + M_PI)/2 + xc, r*sin(theta + M_PI)/2+yc, r/10);
	gfx_fill_circle(r*cos(theta + M_PI)*3/4 + xc, r*sin(theta + M_PI)*3/4+yc, r/10);
	gfx_fill_circle(r*cos(theta + M_PI*5/6)/2 + xc, r*sin(theta + M_PI*5/6)/2+yc, r/10);
	gfx_fill_circle(r*cos(theta + M_PI*5/6)*3/4 + xc, r*sin(theta + M_PI*5/6)*3/4+yc, r/10);
	gfx_fill_circle(r*cos(theta + M_PI*7/6)/2 + xc, r*sin(theta + M_PI*7/6)/2+yc, r/10);
	gfx_fill_circle(r*cos(theta + M_PI*7/6)*3/4 + xc, r*sin(theta + M_PI*7/6)*3/4+yc, r/10);
	gfx_circle(xc, yc, r);
}
//===================================================================================

void draw_fighter(int r, double theta, int xc, int yc, int exists){

   if(!exists)
      return;
      
	XPoint mypts1[] = { {r*cos(theta + M_PI)*4/5 + xc, r*sin(theta + M_PI)*4/5+yc},
		{r*cos(theta + +M_PI - M_PI/4)*3/2 + xc, r*sin(theta + M_PI - M_PI/4)*3/2 + yc},
		{r*cos(theta + M_PI - M_PI/7)*2 + xc, r*sin(theta + M_PI - M_PI/7)*2 + yc},
		{r*cos(theta + M_PI)*2 + xc, r*sin(theta + M_PI)*2 + yc},
		{r*cos(theta + M_PI + M_PI/7)*2 + xc, r*sin(theta + M_PI + M_PI/7)*2 + yc},
		{r*cos(theta + M_PI + M_PI/4)*3/2 + xc, r*sin(theta + M_PI + M_PI/4)*3/2 + yc},
		{r*cos(theta + M_PI)*4/5 + xc, r*sin(theta + M_PI)*4/5+yc} };
	int sz1 = sizeof(mypts1)/sizeof(XPoint);
	XPoint mypts2[] = { {r*cos(theta)*2/3 + xc, r*sin(theta)*2/3 + yc},
		{r*cos(theta - M_PI/4)*5/4 + xc, r*sin(theta - M_PI/4)*5/4 + yc},
		{r*cos(theta - M_PI*2/11)*7/4 + xc, r*sin(theta - M_PI*2/11)*7/4 + yc},
		{r*cos(theta)*7/4 + xc, r*sin(theta)*7/4 + yc},
		{r*cos(theta + M_PI*2/11)*7/4 + xc, r*sin(theta + M_PI*2/11)*7/4 + yc},
		{r*cos(theta + M_PI/4)*5/4 + xc, r*sin(theta + M_PI/4)*5/4 + yc},
		{r*cos(theta)*2/3 + xc, r*sin(theta)*2/3 + yc} };
	int sz2 = sizeof(mypts2)/sizeof(XPoint);
	gfx_color(0, 0, 0);
	gfx_fill_polygon(mypts2, sz2); 
	gfx_color(255, 255, 255);
	gfx_polygon(mypts2, sz2);
	gfx_fill_circle(xc, yc, r);
	gfx_color(0, 0, 0);
	gfx_circle(xc, yc, r);
	gfx_fill_circle(r*cos(theta)/3 + xc, r*sin(theta)/3+yc, r/3);
	gfx_fill_polygon(mypts1, sz1);
	gfx_color(255, 255, 255);
	gfx_polygon(mypts1, sz1);
}
//===================================================================================

int collision(int xm, int ym, int rm, int xf, int yf, int rf){
   
   if(sqrt(pow(xm-xf, 2) + pow(ym-yf, 2)) <= rm + rf)
      return 1;
   
   return 0;
}
//===================================================================================

void infinite_edge(int wd, int ht, int r, double *x, double *y){

	if(*x > wd + r + 20)
	   *x = -r - 10;
   else if(*x < -r - 20)
      *x = wd + r + 10;
   if(*y > ht + r + 20)
      *y = -r - 10;
   else if(*y < -r - 20)
      *y = ht + r + 10;
}
