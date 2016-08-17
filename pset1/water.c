#include<stdio.h>
#include<cs50.h>

int main()
{
    float bath_time_mins=0.0,no_of_gallons,no_of_ounces,no_of_bottles;
    printf("minutes : ");
    bath_time_mins=GetFloat();
    no_of_gallons=1.5*bath_time_mins;
    no_of_ounces=128*no_of_gallons;
    no_of_bottles=no_of_ounces/16.0;
    printf("bottles : %.f\n",no_of_bottles);
    return(0); 
}