#include<stdio.h>
#include<cs50.h>
#include<math.h>
float nanf(const char *tagp);

int main()
{
    float bath_time_mins=0.0;
    printf("minutes : ");
    bath_time_mins=GetFloat();
    printf("bottles : %.f\n",(1.5*128*bath_time_mins)/16.0);
    return(0); 
}