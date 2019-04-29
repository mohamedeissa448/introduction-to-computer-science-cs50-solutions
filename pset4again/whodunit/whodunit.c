#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
int main(int argc,char*argv[])
{
    if (argc!=3)
          {
              fprintf(stderr,"correct usage:./file infile outfile\n");
              return 1;
          }
     char*infile=argv[1];
     char*outfile=argv[2];
     FILE*ptrinf=fopen(infile,"r");
     FILE*ptroutf=fopen(outfile,"w");
     if (ptrinf==NULL)
          {
            fprintf(stderr,"couldnot open %s\n",infile);
            return 2;
          }
     if (ptroutf==NULL)
          {
            fprintf(stderr,"couldnot create %s\n",outfile);
            return 3;
            fclose(ptrinf);
          }
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,ptrinf);
    fread(&bih,sizeof(BITMAPINFOHEADER),1,ptrinf);
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,ptroutf);
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,ptroutf);
     if (bfh.bfType != 0x4d42 || bfh.bfOffBits != 54 || bih.biSize != 40 ||
        bih.biBitCount != 24 || bih.biCompression != 0)
    {
        fclose(ptroutf);
        fclose(ptrinf);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    int padding=(4-(bih.biWidth*3)%4)%4;
    for (int i=0;i<abs(bih.biHeight);i++)
        {
            for(int j=0;j<bih.biWidth;j++)
               {
                   RGBTRIPLE bgr;
                   fread(&bgr,sizeof(RGBTRIPLE),1,ptrinf);
                        // write RGB triple to outfile
                            if(bgr.rgbtRed == 255)
                            {
                        		bgr.rgbtRed = 0;
                          		bgr.rgbtBlue = 100;
                        		bgr.rgbtGreen = 60;
                            }
                   fwrite(&bgr,sizeof(RGBTRIPLE),1,ptroutf);

               }
               fseek(ptrinf,padding,SEEK_CUR);
                  for(int k=0;k<padding;k++)
                  {
                      fputc(0x00,ptroutf);
                  }

        }

        fclose(ptrinf);
         fclose(ptroutf);
         return 0;

}