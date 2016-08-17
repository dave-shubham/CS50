#include<stdio.h>
#include<string.h>
#include<cs50.h>
#include<ctype.h>


int main(void)
{
//    char s[50],s1[10];
    string s;
    char s1[10];
    //gets(s);
    s=GetString();
    int i=0,len,j=0;
    for(len=strlen(s);i<len-1;i++)
    {
        if( i==0 )//&& ( ( s[i] >= 65 && s[i]<65+26 ) || ( s[i] >= 97 && s[i]<97+26 ) ) )
        {
            s1[j]=s[i];
            j++;
        }
        if(s[i]== ' ')
        {
            s1[j]=s[i+1];
            j++;
        }
    }
    s1[j]='\0';
    for(i=0,len=strlen(s1);i<len;i++)
    {
        if(islower(s1[i]))
        {
            s1[i]=toupper(s1[i]);
        }
    }
    printf("%s\n",s1);
    return(0);
}
