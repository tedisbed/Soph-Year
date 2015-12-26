#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "gfx2.h"
#define PI acos(-1)

double main_circlex(double a, double b);
double main_circley(double x, double y);

double circle1x(double a,double r, double b);
double circle1y(double a,double r, double b);
double circle2x(double a,double r, double b);
double circle2y(double a,double r, double b);
double circle3x(double a,double r, double b);
double circle3y(double a,double r, double b);
double circle4x(double a,double r, double b);
double circle4y(double a,double r, double b);

int main(void){
    int loop = 1;
    int wt=500,ht=500;
    double x = 250, y = 250;
    double mcx = 0, mcy =0;
    double dx = 0,dy = 0,dz = 0, da = 0;
    double x1 = 0, x2 = 0, x3 = 0, x4 = 0;
    double y1 = 0, y2 = 0, y3 = 0, y4 = 0;
    double x11 = 0, x22 = 0, x33 = 0, x44 = 0;
    double y11 = 0, y22 = 0, y33 = 0, y44 = 0;
    double x111 = 0, x222 = 0, x333 = 0, x444 = 0;
    double y111 = 0, y222 = 0, y333 = 0, y444 = 0;
    double xx1 = 0, xx2=0, xx3=0, xx4=0;
    double yy1 = 0, yy2=0, yy3=0, yy4=0;
    double xxx1 = 0, xxx2=0, xxx3=0, xxx4=0;
    double yyy1 = 0, yyy2=0, yyy3=0, yyy4=0;
    double r = 40;
    double rad = 15;
    double increment = .1, goup = .2;
    gfx_open(wt,ht,"Carnival Ride");
    while(loop){
        gfx_clear_color(255,255,255);
        gfx_clear();
// main circle
        mcx = main_circlex(x,dx);    
        mcy = main_circley(y,dx);
        gfx_color(255,0,0);
        gfx_circle(mcx,mcy,50);
// 4 outside circles
        x1 = circle1x(mcx,50,dy);// pi / 2
        y1 = circle1y(mcy,50,dy);
        x2 = circle2x(mcx,50,dy);// pi
        y2 = circle2y(mcy,50,dy);
        x3 = circle3x(mcx,50,dy);// pi * 3/2
        y3 = circle3y(mcy,50,dy);
        x4 = circle4x(mcx,50,dy);// 0
        y4 = circle4y(mcy,50,dy);
        gfx_color(0,255,0);
        gfx_circle(x1,y1,20);
        gfx_circle(x2,y2,20);
        gfx_circle(x3,y3,20);
        gfx_circle(x4,y4,20);
// rodes that go in and out 
        if( r < 40){
            increment = increment * -1;
        }else if(r > 100){
            increment = -1 * increment;
        }
        
        r = r + increment;
        gfx_color(0,0,255);
        xx1 = circle1x(x1,20,dy);
        yy1 = circle1y(y1,20,dy);
        xxx1 = circle1x(xx1,r,dy);
        yyy1 = circle1y(yy1,r,dy);
        gfx_line(xx1,yy1,xxx1,yyy1);

        xx2 = circle2x(x2,20,dy);
        yy2 = circle2y(y2,20,dy);
        xxx2 = circle2x(xx2,r,dy);
        yyy2 = circle2y(yy2,r,dy);
        gfx_line(xx2,yy2,xxx2,yyy2);

        xx3 = circle3x(x3,20,dy);
        yy3 = circle3y(y3,20,dy);
        xxx3 = circle3x(xx3,r,dy);
        yyy3 = circle3y(yy3,r,dy);
        gfx_line(xx3,yy3,xxx3,yyy3);

        xx4 = circle4x(x4,20,dy);
        yy4 = circle4y(y4,20,dy);
        xxx4 = circle4x(xx4,r,dy);
        yyy4 = circle4y(yy4,r,dy);
        gfx_line(xx4,yy4,xxx4,yyy4);
// circles at the end of the rods
        gfx_color(0,255,255);
        gfx_circle(xxx1,yyy1,10);
        gfx_circle(xxx2,yyy2,10);
        gfx_circle(xxx3,yyy3,10);
        gfx_circle(xxx4,yyy4,10);
        
// spining rods with cirles around it that go in and out
        if( rad < 15){
            goup = goup * -1;
        }else if(rad > 35){
            goup = -1 * goup;
        }
        
        rad = rad + goup;
        gfx_color(148,0,211);
        x11 = circle1x(xxx1,10,da);
        y11 = circle1y(yyy1,10,da);
        x111 = circle1x(x11,rad,da);
        y111 = circle1y(y11,rad,da);
        gfx_line(x11,y11,x111,y111);

        x22 = circle2x(xxx2,10,da);
        y22 = circle2y(yyy2,10,da);
        x222 = circle2x(x22,rad,da);
        y222 = circle2y(y22,rad,da);
        gfx_line(x22,y22,x222,y222);

        x33 = circle3x(xxx3,10,da);
        y33 = circle3y(yyy3,10,da);
        x333 = circle3x(x33,rad,da);
        y333 = circle3y(y33,rad,da);
        gfx_line(x33,y33,x333,y333);

        x44 = circle4x(xxx4,10,da);
        y44 = circle4y(yyy4,10,da);
        x444 = circle4x(x44,rad,da);
        y444 = circle4y(y44,rad,da);
        gfx_line(x44,y44,x444,y444);
// the circles
        gfx_color(0,0,0);
        gfx_circle(x444,y444,12);
        gfx_circle(x333,y333,12);
        gfx_circle(x222,y222,12);
        gfx_circle(x111,y111,12);

        gfx_flush();
        usleep(8000);
// the speeds at which the differnt things go at
        dx = dx + .01;
        dy = dy + .03;
        dz = dz + .05;
        da = da + .07;
    }
}
// the functions below just start at different positions and do rotational
// motion. i thought i had to write a function for every single rotation but no
// starting values in order as they appear
// they appear as an x and then a y
// (PI/2)
// PI
// PI * (3/2)
// 0
double circle1x(double a,double r, double dx){
    double x = 0;

    x = a + r * cos(dx + (PI/2));
    return x;
}
double circle1y(double a, double r, double dx){
    double y = 0;

    y  = a + r * sin(dx + (PI/2));
    return y;
}
double circle2x(double a, double r, double dx){
    double x = 0;

    x = a + r * cos(dx + PI);
    return x;
}
double circle2y(double a, double r, double dx){
    double y = 0;

    y = a + r * sin(dx + PI);
    return y;
}
double circle3x(double a, double r, double dx){
    double x = 0;

    x = a + r * cos(dx + (PI*3/2));
    return x;
}
double circle3y(double a, double r, double dx){
    double y = 0;

    y = a + r * sin(dx + (PI * 3/2));
    return y;
}
double circle4x(double z, double r, double dx){
    double x = 0;

    x = z + r * cos(dx);
    return x;
}
double circle4y(double a, double r, double dx){
    double y = 0;

    y = a + r * sin(dx);
    return y;
}
// i didnt need either of these two functions but figured that out after
// these just make the red large circle
double main_circley(double b, double dx){
    double r = 75,y = 0;
    y = b + r * sin(dx);
    return y;
}
double main_circlex(double a, double dx){
    double r = 75,x = 0;
    x = a + r * cos(dx);
    return x;
}
