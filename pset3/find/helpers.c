/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include<unistd.h>
#include "helpers.h"
#include<stdio.h>
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if(n<=0)
    {
        return false;
    }
    // TODO: implement a searching algorithm
  /*  
   int i;
    for(i=0;i<n;i++)
    {
        if(values[i]==value)
        {
            return true;
        }
    }
    return false;
*/
   int left=0,right=n-1,middle=(left+right)/2;
   while(1)
   {
        if(values[left] == value || values[right] == value )
        {
            return true;
        }
        else if(left>=right)
        {
            return false;
        }
        else
        {
            middle=(left+right)/2;

        //debugging
    
        //printf("%d\t%d\t%d\t%d\t%d\t%d\n",value,left,values[left],right,values[right],middle);
        //sleep(5);

            if(values[middle]==value)
            {
                return true;
            }
            else if(values[middle]<value)
            {
                left=middle+1;
            }
            else if(values[middle]>value)
            {
                right=middle;
            }
        }
   }
   
   

}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int i,swaps,j;
    for(i=0;i<n-1;i++)
    {
        swaps=0;
        for(j=0;j<n-1;j++)
        {
            if(values[j]>values[j+1])
            {
                values[j]=values[j]^values[j+1];
                values[j+1]=values[j]^values[j+1];
                values[j]=values[j]^values[j+1];
                swaps=1;
            }
        }
        if(swaps==0)
        {
            break;
        }
    }
    return;
}