#include <cs50.h>
#include <stdio.h>
int main (int argc,char*argv[])
{
    int i=0;
    if(argc!=2)
    {
        fprintf(stderr,"correct usage:./recover card.raw\n");
        return 1;
    }
    char *infile=argv[1];
    if(infile==NULL)
    {
        fprintf(stderr,"couldnot open%s\n",argv[1]);
        return 2;
    }
    FILE*ptrinf=fopen(infile,"r");
   unsigned char arr[512];bool found=false;FILE*ptroutf=NULL;
    while((fread(arr,512,1,ptrinf))==1)
    {
           if ((arr[0] == 0xff && arr[1] == 0xd8 && arr[2] == 0xff && (arr[3] & 0xe0) == 0xe0))
               {
                      if (found==true)
                      {
                          fclose(ptroutf);
                      }
                       char img_name[10];
                       sprintf(img_name,"%03i.jpg",i);
                       i++;
                       ptroutf=fopen(img_name,"w");
                       fwrite(arr,sizeof(char),512,ptroutf);
                       found=true;
               }
         else if(found==true)
           {
               fwrite(arr,sizeof(char),512,ptroutf);
           }
    }
    fclose(ptrinf);
    return 0;
}