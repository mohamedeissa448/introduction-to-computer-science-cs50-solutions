#include <stdio.h>
#include <cs50.h>
int main(void)
{
    float y;int x;int counter=0;
    do{
        printf("O hai! How much change is owed?\n") ;
        y=get_float();
     }
     while (y<0);
    x=y*100;
     while (x/25>0)
     {
         x-=25;
         counter++;
     }
     while (x/10>0)
     {
         x-=10;
         counter++;
     }
     while (x/5>0)
     {
         x-=5;
         counter++;
     }
     while (x/1>0)
     {
         x-=1;
         counter++;
     }
   printf("%d\n",counter);
   return 0;
}