#include<stdio.h>
#include<cs50.h>
#include<string.h>
int main(int argc, string argv[])
{
    //checking number of arguments
    if (argc != 2)
    {
        printf("command line arguments should be two!");
        return 1;
    }
    //changing string key to integer key
    int key = 0,m = 1, n = strlen(argv[1]);
    for(int i =n-1; i >= 0; i--)
    {
        key = key + m * (argv[1][i] - 48);
        m *= 10;
    }
    //prompt user for plaintext
    string s = get_string("plaintext:  ");
    int holder;
    //changing plaintext into cipher text
    for(int i= 0, no = strlen(s); i<no; i++)
    {
        if(s[i] >= 65&&s[i] <= 90)
        {
            s[i] = s[i]+ (key%26);
            if(s[i]>90)
            {
              s[i] = s[i]-90+64;
            }
        }
       else if(s[i]>= 97&&s[i] <= 122)
        {
            holder = s[i]+(key%26);
            if(holder>122)
            {
                s[i] = holder-122+96;
            }
            else
            {
                s[i] = s[i]+(key%26);
            }
        }

    }
    printf("ciphertext: %s\n", s);

}