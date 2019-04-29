#include<cs50.h>
#include<stdio.h>
#include"bmp.h"
int main (int argc,char*argv[])
{
    if (argc!=4)
        {
            fprintf(stderr,"correct usage:./resize n infile outfile\n");
            return 1;
        }
    int n=atoi(*(argv+1));
    char*infile=argv[2];
    char*outfile=argv[3];
    FILE*ptrinf=fopen(infile,"r");
    FILE*ptroutf=fopen(outfile,"w");
    BITMAPFILEHEADER bfh;
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,ptrinf);
    BITMAPINFOHEADER bih;
    fread(&bih,sizeof(BITMAPINFOHEADER),1,ptrinf);
    int old_padding = (4 - (bih.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bih.biWidth=bih.biWidth*n;
    long y=abs(bih.biWidth)/n;
    bih.biHeight=bih.biHeight*n;
    long x=abs(bih.biHeight)/n;
    int new_padding = (4 - (bih.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bih.biSizeImage=bih.biWidth*3*bih.biHeight+new_padding*bih.biHeight;
    bfh.bfSize=bih.biSizeImage+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,ptroutf);
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,ptroutf);
    for(int i=0;i<x;i++)
        {
            for(int m = 0; m < n; m++)
				{
              for(int j=0;j<y;j++)
              {
                 RGBTRIPLE rgb;
                 fread(&rgb,sizeof(RGBTRIPLE),1,ptrinf);

                 for(int k=0;k<n;k++)
                     {
                        fwrite(&rgb,sizeof(RGBTRIPLE),1,ptroutf);
                     }
              }
             // skip over padding, if any
             fseek(ptrinf, old_padding, SEEK_CUR);
             // then add it back (to demonstrate how)
            for (int l = 0; l < new_padding; l++)
            {
                fputc(0x00, ptroutf);

             }
               fseek(ptrinf, -(3 * y+ old_padding ), SEEK_CUR);
				}

   fseek(ptrinf, (3 * y+ old_padding ), SEEK_CUR);
       }
    fclose(ptrinf);
    fclose(ptroutf);
}