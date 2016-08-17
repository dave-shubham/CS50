#include<stdio.h>
#include<cs50.h>

int main()
{
    int height_of_pyramid=0,i=0,j=0;
    do
    {
        printf("Height:");
        height_of_pyramid=GetInt();
    }while(height_of_pyramid>23 || height_of_pyramid<0);
    for(i=0;i<height_of_pyramid;i++)
    {
        for(j=height_of_pyramid-1;j>i;j--)
        {
            printf(" ");
        }
        for(j=0;j<i+2;j++)
        {
            printf("#");
        }
        printf("\n");
    }
    return(0); 
}