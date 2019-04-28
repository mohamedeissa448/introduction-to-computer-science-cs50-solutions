#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include <ctype.h>
int main (void)
    {
      string name = get_string();

    //print the first initial as an uppercase letter
    printf("%c", toupper(name[0]));

    //loop and find space characters.
    for (int i = 0; i < strlen(name); i++)
    {
        if (name[i] == ' ')
        {
            // print next character as an uppercase char
            printf("%c", toupper(name[i + 1]));
        }
    }

    //print new line
    printf("\n");
    }