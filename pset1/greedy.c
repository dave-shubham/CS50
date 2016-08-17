#include<stdio.h>
#include<cs50.h>

int main()
{
    int amount,i=0,coins[4]={25,10,5,1},no_of_coins=0;
    double change_owed;
    do
    {
        printf("O hai! How much change is owed?\n");
        change_owed=GetDouble();//GetFloat();
    }while(change_owed<0);
    amount=change_owed*100;
    //printf("%f\t%d\n",change_owed,amount);
    while(amount!=0)
    {
        while(amount>=coins[i])
        {
            amount=amount-coins[i];
            no_of_coins++;
        }
        i++;
    }
    printf("%d\n",no_of_coins);
    return(0); 
}