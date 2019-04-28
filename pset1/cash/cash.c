#include <cs50.h>
#include <stdio.h>
#include<math.h>

int main(void)
{
   float cash =get_float("Change owed: ");
   while(cash<0){
       cash =get_float("Change owed: ");
     }
   int cent=round(cash*100);
   int counter=0;
   while(cent>=25)
   {
       cent-=25;
       counter++;
   }
 while(cent>=10)
   {
       cent-=10;
       counter++;
   }
  while(cent>=5)
   {
       cent-=5;
       counter++;
   }
   while(cent>=1)
   {
       cent-=1;
       counter++;
   }


printf("%i\n",counter);



}
