#include <stdio.h>
#include "gfx4.h"
#include <math.h>
#include <unistd.h>
#define PI acos(-1)

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3);
void drawtri(int x1,int y1,int x2,int y2,int x3,int y3);
void drawsquare(int x1,int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void squares(int x1,int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void spiralsquare(int x1,int y1,int x2,int y2, int x3, int y3,int x4, int y4,double r, double theta,double factor);
void circleofcircles(int x1, int y1, int r);
void snowflake(int x, int y, int r);
void tree(int x, int y, double r, double theta);
void fern(double x, double y, double r, double theta);

int main(void){
    int loop = 1;
    char num = '1';
    gfx_open(700,700, "Fractals");
    while (loop){
        if (gfx_event_waiting()){
            num = gfx_wait();
            switch(num){
                case '1':
                    gfx_clear();
                    sierpinski(100,100,350,600,600,100);
                    gfx_flush();
                    break;
                case '2':
                    gfx_clear();
                    squares(150,150,150,550,550,550,550,150);
                    gfx_flush();
                    break;
                case '3':
                    gfx_clear();
                    spiralsquare(650,300,800,300,800,450,650,450,300,0,150);
                    gfx_flush();
                    break;
                case'4':
                    gfx_clear();
                    circleofcircles(350,350,200);
                    gfx_flush();
                    break;
                case'5':
                    gfx_clear();
                    snowflake(350,350,200);
                    gfx_flush();
                    break;
                case'6':
                    gfx_clear();
                    tree(350,700,200,(3*PI/2));
                    gfx_flush();
                    break;
                case'7':
                    gfx_clear();
                    fern(350,700,300,(3*PI/2));
                    gfx_flush();
                    break;
                case'8':

                    break;
                case'q':
                    return 0;
                    break;
            }
        }
    }
}
void fern(double x, double y, double r, double theta){
    if(r<2) return;

    double x1 = x + r * cos(theta);
    double y1 = y + r * sin(theta);
    gfx_line(x,y,x1,y1);

    double x2 = x1 - (r/4)*cos(theta);
    double y2 = y1 - (r/4)*sin(theta);
    double x3 = x1 - (r/2)*cos(theta);
    double y3 = y1 - (r/2)*sin(theta);
    double x4 = x1 - (3*r/4)*cos(theta);
    double y4 = y1 - (3*r/4)*sin(theta);

    fern(x1,y1,r/4,theta - PI/6);
    fern(x1,y1,r/4,theta + PI/6);
    fern(x2,y2,r/4,theta - PI/6);
    fern(x2,y2,r/4,theta + PI/6);
    fern(x3,y3,r/4,theta - PI/6);
    fern(x3,y3,r/4,theta + PI/6);
    fern(x4,y4,r/4,theta - PI/6);
    fern(x4,y4,r/4,theta + PI/6);
}
void tree(int x, int y, double r,double theta){
    double x1,y1;

    if(r<2) return;

    x1 = x + r * cos(theta);
    y1 = y + r * sin(theta);

    gfx_line(x,y,x1,y1);

    r = r / 1.5;

    tree(x1,y1,r,theta + (PI/6));
    tree(x1,y1,r,theta - (PI/6));

}
void snowflake(int x, int y, int r){
    double x1,y1,x2,y2,x3,y3,x4,y4,x5,y5;

    if(r<2) return;

    x1 = x + r * cos(PI/5);
    y1 = y + r * sin(PI/5);
    x2 = x + r * cos(3*PI/5);
    y2 = y + r * sin(3*PI/5);
    x3 = x + r * cos(5*PI/5);
    y3 = y + r * sin(5*PI/5);   
    x4 = x + r * cos(7*PI/5);
    y4 = y + r * sin(7*PI/5);
    x5 = x + r * cos(9*PI/5);
    y5 = y + r * sin(9*PI/5);

    gfx_line(x,y,x1,y1);
    gfx_line(x,y,x2,y2);
    gfx_line(x,y,x3,y3);
    gfx_line(x,y,x4,y4);
    gfx_line(x,y,x5,y5);

    r = r / 2.5;

    snowflake(x1,y1,r);
    snowflake(x2,y2,r);
    snowflake(x3,y3,r);
    snowflake(x4,y4,r);
    snowflake(x5,y5,r);
}
void circleofcircles(int x, int y, int r){
    double x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6;

    if(r<2) return;

    gfx_circle(x,y,r);

    x1 = x + r * cos(0);
    y1 = y + r * sin(0);
    x2 = x + r * cos(PI/3);
    y2 = y + r * sin(PI/3);
    x3 = x + r * cos(2*PI/3);
    y3 = y + r * sin(2*PI/3);
    x4 = x + r * cos(PI);
    y4 = y + r * sin(PI);
    x5 = x + r * cos(4*PI/3);
    y5 = y + r * sin(4*PI/3);
    x6 = x + r * cos(5*PI/3);
    y6 = y + r * sin(5*PI/3);
    
    r = r /3;

    circleofcircles(x1,y1,r);
    circleofcircles(x2,y2,r);
    circleofcircles(x3,y3,r);
    circleofcircles(x4,y4,r);
    circleofcircles(x5,y5,r);
    circleofcircles(x6,y6,r);
}
void spiralsquare(int x1,int y1, int x2, int y2, int x3, int y3, int x4, int y4,double r, double theta,double factor){
    double x = 0, y = 0;
    
    if(factor<2) return;
    
    r = r *.8;
    theta = theta + PI/4;
    factor = factor *.8;
    
    drawsquare(x1,y2,x2,y2,x3,y3,x4,y4);
    
    x = 350 + r * cos(theta);
    y = 350 + r * sin(theta);
    spiralsquare(x,y,x + factor, y,x + factor, y + factor, x, y + factor,r,theta,factor);
}
void drawsquare(int x1,int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    gfx_line(x1,y1,x2,y2);
    gfx_line(x2,y2,x3,y3);
    gfx_line(x3,y3,x4,y4);
    gfx_line(x4,y4,x1,y1);
}
void squares(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    int diff = 0;
    if (abs(x3-x1)<2) return;

    diff = ((x1-x3)/5);
    drawsquare(x1,y1,x2,y2,x3,y3,x4,y4);

    squares(x1-diff,y1-diff,x1+diff,y1-diff,x1+diff,y1+diff,x1-diff,y1+diff);
    squares(x2-diff,y2-diff,x2+diff,y2-diff,x2+diff,y2+diff,x2-diff,y2+diff);
    squares(x3-diff,y3-diff,x3+diff,y3-diff,x3+diff,y3+diff,x3-diff,y3+diff);
    squares(x4-diff,y4-diff,x4+diff,y4-diff,x4+diff,y4+diff,x4-diff,y4+diff);

}
void drawtri( int x1, int y1, int x2, int y2, int x3, int y3){
    gfx_line(x1,y1,x2,y2);
    gfx_line(x2,y2,x3,y3);
    gfx_line(x3,y3,x1,y1);
}
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
        //Base case 
        if( abs(x2-x1) < 2 ) return;
       
        // Draw the triangle
        drawtri( x1, y1, x2, y2, x3, y3 );
       
        //Recursive calls
        sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2,(y1+y3)/2 );
        sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2,(y2+y3)/2 );
        sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2,(y2+y3)/2, x3, y3 );
}
