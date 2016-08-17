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
        int len,keylen,i,j=0;
        string plainText,key="";
        key=argv[1];
        keylen=strlen(key);
        for(i=0;i<keylen;i++)
        {
            if(key[i]<65 || ( key[i]>90 && key[i]<97 ) || key[i]>122)
            {
                printf("U Idiot ! Type in right arguments !\n");
                return(1);
            }
        }
        plainText=GetString();
        len=strlen(plainText);
        
        char cipherText[len];
        int key_code[keylen];
        for(i=0;i<keylen;i++)
        {
            if(key[i]>=65 && key[i]<91)
            {
                key_code[i]=key[i]-65;    
            }
            else if(key[i]>=97 && key[i]<123)
            {
                key_code[i]=key[i]-97;
            }
       //     printf("%d\t",key_code[i]);
        }
//        printf("%s\n",key);
//        printf("%s\n",plainText);
//        printf("%d\t%d\n",len,keylen);
        
        for(i=0;i<len;i++)
        {
            if(j == keylen)
            {
                j=0;
            }
        //    printf("%d\t%c\t",plainText[i],plainText[i]);
            if(plainText[i]>=65 && plainText[i]< 91)
            {
                if(plainText[i]+key_code[j]>90)
                {
                    cipherText[i]=plainText[i]+key_code[j] - 26;
                }
                else
                {
                    cipherText[i]=plainText[i]+key_code[j];
                }
                j++;
            }
            else if(plainText[i]>=97 && plainText[i]< 123)
            {
                if(plainText[i]+key_code[j]>122)
                {
                    cipherText[i]=plainText[i]+key_code[j] - 26;
                }
                else
                {
                    cipherText[i]=plainText[i]+key_code[j];
                }
                j++;
            }
            else
            {
                cipherText[i]=plainText[i];
            }
//            printf("%d\t%c\n",cipherText[i],cipherText[i]);
        }
        cipherText[i]='\0';
        printf("%s\n",cipherText);
    }
    return(0);
}
