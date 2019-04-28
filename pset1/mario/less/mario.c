#include<cs50.h>
#include<stdio.h>
int main(void)
{
   int height=get_int("Height: ") ;
   while(height<0||height>23)
   {
       height=get_int("Height: ") ;
   }
int counter_of_tabs=0;
   for(int i=height;i>0;i--){

       for(int tab=i-1;tab>0;tab--)
       {
           printf(" ");
           counter_of_tabs++;
       }
       for(int hash=0;hash<height+1-counter_of_tabs;hash++)
       {
           printf("#");
       }
        printf("\n");
        counter_of_tabs=0;
  }
}