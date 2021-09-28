#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *image, *outputImage, *lecturas;
    FILE *fptr;

    fptr=fopen("his_n_1.txt","w");
    image = fopen("dados.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("img2_dd.bmp","wb");    //Imagen transformada
    long ancho;
    long alto;
    unsigned char r, g, b;               //Pixel
    unsigned char* ptr;

    unsigned char xx[54];
    int cuenta = 0;
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("largo img %li\n",alto);
    printf("ancho img %li\n",ancho);

    ptr = (unsigned char*)malloc(alto*ancho*3* sizeof(unsigned char));

    unsigned char b_0[ancho*alto];
    unsigned char g_0[ancho*alto];
    unsigned char r_0[ancho*alto];
    int c = 0;

    while(!feof(image)){
      b = fgetc(image);
      g = fgetc(image);
      r = fgetc(image);

      if (c < (ancho*alto))
      {
        b_0[c] = b;
        g_0[c] = g;
        r_0[c] = r;

      }

      unsigned char pixel = 0.21*r+0.72*g+0.07*b;

      ptr[cuenta] = pixel; //b
      ptr[cuenta+1] = pixel; //g
      ptr[cuenta+2] = pixel; //r

      cuenta++;
      c++;
    }                                        //Grises

    int b_1[256];
    for (int i = 0; i < 256; ++i)
    {
      b_1[i] = 0;
      for (int j = 0; j < ancho*alto; ++j)
      {
        if (b_0[j] == i)
        {
          b_1[i]+= 1;
        }
      }
    }

    int g_1[256];
    for (int i = 0; i < 256; ++i)
    {
      g_1[i] = 0;
      for (int j = 0; j < ancho*alto; ++j)
      {
        if (g_0[j] == i)
        {
          g_1[i]+= 1;
        }
      }
    }

    int r_1[256];
    for (int i = 0; i < 256; ++i)
    {
      r_1[i] = 0;
      for (int j = 0; j < ancho*alto; ++j)
      {
        if (r_0[j] == i)
        {
          r_1[i]+= 1;
        }
      }
    }  


    for (int i = 0; i < 256; ++i)
    {
      fprintf(fptr, "%i\t%i\t%i\n", b_1[i], g_1[i], r_1[i]);
    }

    cuenta = ancho;
    for (int i = 0; i < alto*ancho*3; ++i) {
      fputc(ptr[i+(cuenta*3)+2], outputImage);
      fputc(ptr[i+(cuenta*3)+1], outputImage);
      fputc(ptr[i+(cuenta*3)], outputImage);
      cuenta--;
      if (cuenta == 0){
        cuenta = ancho;
      }
    }

    free(ptr);
    fclose(image);
    fclose(outputImage);
    fclose(fptr);
    return 0;
}
