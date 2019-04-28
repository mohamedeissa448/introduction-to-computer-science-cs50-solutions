#include<stdio.h>
#include<cs50.h>
#include<string.h>
bool isalphabtic(char c);
int main(int argc, string argv[])
{
    //checking number of arguments
    if (argc != 2)
    {
        printf("command line arguments should be two!\n");
        return 1;
    }
    for(int i=0,n=strlen(argv[1]);i<n;i++)
    {
        if( ! isalphabtic(argv[1][i]))
        {
            printf("error!\n");
        return 1;
        }
    }
    string s = get_string("plaintext:  ");
    string key=argv[1];
    int h,holder;
    int m=strlen(key);
    for(int j=0;j<m;j++)
    {
        if(key[j]>=65&&key[j]<=90)
                {
                    key[j]-=65;
                }
                else if(key[j]>=97&&key[j]<=122)
                {
                    key[j]-=97;
                }

    }
    string modi="a";int jj=0;

    for(int i=0,n=strlen(s);i<n;i++)
        {
            if(isalphabtic(s[i])){
               modi[jj]=s[i];
               jj++;
           }
            h=jj%m;
                if(s[i] >= 65&&s[i] <= 90)
                {
                    s[i] = s[i]+key[h];
                    if(s[i]>90)
                    {
                      s[i] = s[i]-90+64;
                    }
                }
                 else if(s[i]>= 97&&s[i] <= 122)
                {
                    holder = s[i]+key[h];
                    if(holder>122)
                    {
                        s[i] = holder-122+96;
                    }
                    else
                    {
                        s[i] = s[i]+key[h];
                    }
               }

        }

        printf("ciphertext: %s\n", s);
}



   bool isalphabtic(char c)
{
    if((c>=65 && c<=90) || (c>=97 && c<=122))
    {
        return true;
    }
    else
    {
    return false;
    }
}