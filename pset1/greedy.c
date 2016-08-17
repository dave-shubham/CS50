#include<stdio.h>
#include<cs50.h>

int main()
{
    int amount,index=0,coins[4]={25,10,5,1},no_of_coins=0; //no_of_coins returns the final answer
    double change_owed;                                     //change_owed is amount owed to customer in dollar and 
    do                                                      //can be a whole number as well as fractional number  
    {
        printf("O hai! How much change is owed?\n");
        change_owed=GetDouble();                           //GetDouble is inbuilt function in CS50.h header file
    }while(change_owed<0);                                  //Checks so that changed owed is not negative
    amount=change_owed*100;                                 //converting change_owed into cents
    //printf("%f\t%d\n",change_owed,amount);
    while(amount!=0)                                        //loops over amount remaining and selects coins greedily based on highest denomination available
    {
        while(amount>=coins[index]) 
        {
            amount=amount-coins[index];
            no_of_coins++;
        }
        index++;
    }
    printf("%d\n",no_of_coins);
    return(0); 
}
