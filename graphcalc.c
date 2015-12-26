#include <stdio.h>
#include <math.h>
#include "gfx2.h"

int axis(int x,int y);
char *num2str(int n);
double ypoint(double a,double z);
double Fact(double q);
void plot(double x, double y);

int main(void){
	int ht,wd;
    int x,y;
    double a=0,z=1,yy=0;
    char c;
    int loop = 1;

	ht = 500;
	wd = 500;
	gfx_open(ht,wd,"Graphing Calc");// open graphics window
    x = 250;
    y = 250;
    while(loop){
    axis(x,y);// display the axis
    if(gfx_event_waiting()){
        c = gfx_wait();
        switch(c){
            case '=':// increasing the number of terms
                z = z + 1;
                gfx_clear();
                gfx_text(25,25,num2str(z));
                break;
            case '-':// decreasing the number of terms
                z = z - 1;
                if(z <=0){
                    z = 1;
                }
                gfx_clear();
                gfx_text(25,25,num2str(z));
                break;
            case 'q':
                loop = 0;
                break;
        }
    }
    for(a = -10;a<=10;a+=.04){//plotting the graph
        plot(a,ypoint(a,z));
        gfx_flush();
    }
    }

}
void plot(double x,double y){ //plot graph func
    double xnew, ynew;
    double wt = 250, ht = 250;
    xnew = (x/.04) + wt;
    ynew = ht - (y/.04);
    gfx_color(255,0,0);
    gfx_point(xnew,ynew);
    gfx_flush();
}
double Fact (double q)//factorial
{
    double s = 1;
    while(q>1) 
    {
        s *= q;
        q--;
    }
    return s;
}
double ypoint(double a, double z)//y point for function
{
    int count = 1,i;
    double sum = 0;
    double court = 1;
    for(i = 1;i<=z;i++){
        if(count == 1){
            sum = sum + (pow(a,court) / Fact(court));
            count = 0;
        }else{
            sum = sum - (pow(a,court) / Fact(court));
            count = 1;
        }
        court = court +2;
    }
    return sum;
}
char *num2str(int n)
{
    static char a[10], *p = a;
    snprintf(p, 10, "%d", n);
    return p;
}

int axis(int x, int y)//axis function
{
    int xx=x,a=x,b=x,c=x;
    int yy=x,d=x,e=x,f=x;
    int i;
	gfx_color(255,255,255);
    for(i=0;i<10;i++){
        gfx_line(xx,yy,xx+25,yy);
        xx = xx + 25;
        gfx_line(xx,yy+5,xx,yy-5);
        gfx_text(xx,yy+17,num2str(i+1));

        gfx_line(a,d,a-25,d);
        a = a - 25;
        gfx_line(a,d+5,a,d-5);
        gfx_text(a,b-7,num2str(-i-1));
    
        gfx_line(b,e,b,e+25);
        e = e +25;
        gfx_line(b-5,e,b+5,e);
        gfx_text(b+7,e,num2str(-i-1));

        gfx_line(c,f,c,f-25);
        f = f -25;
        gfx_line(c-5,f,c+5,f);
        gfx_text(c+7,f,num2str(i+1));
    }

}
