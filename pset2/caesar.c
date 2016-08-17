#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<cs50.h>

int main(int argc,string argv[])
{
    if(argc != 2)
    {
        printf("U Idiot ! Type in right amount of arguments !\n");
        return(1);
    }
    else
    {
    //        printf("hi !");
        int i,len,k;
        k=atoi(argv[1]);
        k=k%26;
    //    printf("%d\n",k);
        string plainText;
        plainText=GetString();
        len=strlen(plainText);
        char cipherText[len];
    //    printf("%s\n",plainText);
        for(i=0;i<len;i++)
        {
        //    printf("%d\t%c\t",plainText[i],plainText[i]);
            if(plainText[i]>=65 && plainText[i]< 91)
            {
                if(plainText[i]+k>90)
                {
                    cipherText[i]=plainText[i]+k - 26;
                }
                else
                {
                    cipherText[i]=plainText[i]+k;
                }
            }
            else if(plainText[i]>=97 && plainText[i]< 123)
            {
                if(plainText[i]+k>122)
                {
                    cipherText[i]=plainText[i]+k - 26;
                }
                else
                {
                    cipherText[i]=plainText[i]+k;
                }
            }
            else
            {
                cipherText[i]=plainText[i];
            }
        }
        cipherText[i]='\0';
        printf("%s\n",cipherText);
    }
    return(0);
}
