#include <stdio.h>

int main(){
    float x=0.1354;
    while ((x<=1.0f) & (x>=0.0f)){
           printf("%f\n", x);
           x = 4.1f*x*(1.0f-x);}

           return 0;
}