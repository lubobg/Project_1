/// @file main .c
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"


unsigned char subtraction( unsigned char * image , unsigned char * image1, unsigned char * image2, int width , int height , int channel) 
{
    for (int i = 0; i < height ; i ++) 
    {
        for (int j = 0; j < width ; j ++)  
        {
            int dif = 0;
            for (int k = 0; k < channel ; k++) 
            {
            dif += abs(image [ i * width * channel + j * channel + k ] -  image1 [ i * width * channel + j * channel + k ]);
            }

            if(dif < 160) 
            {
                for(int k = 0; k < channel ; k++) 
                {
                image [ i * width * channel + j * channel + k ] = image2 [ i * width * channel + j * channel + k ];
                }
            }
        }
    }
}


int main ()
{
int width , height , channel ;
char path_img [] = "./images/foreground.png";
char path_img1 [] ="./images/background.png";
char path_img2 [] ="./images/new_background.png";
char save_path [] = "./new_result.png";

unsigned char * image = stbi_load ( path_img , &width , &height , & channel , 0);
if ( image == NULL )
{
    printf ("\n Error in loading the image \n");
    exit (1) ;
}
printf (" Width = %d\n Height = %d\n Channel = %d\n", width , height , channel );

unsigned char * image1 = stbi_load ( path_img1 , &width , &height , & channel , 0);
if ( image1 == NULL )
{
    printf ("\n Error in loading the image \n");
    exit (1) ;
}
printf (" Width = %d\n Height = %d\n Channel = %d\n", width , height , channel );

unsigned char * image2 = stbi_load ( path_img2 , &width , &height , & channel , 0);
if ( image2 == NULL )
{
    printf ("\n Error in loading the image \n");
    exit (1) ;
}
printf (" Width = %d\n Height = %d\n Channel = %d\n", width , height , channel );

subtraction (image , image1, image2, width , height , channel );
stbi_write_png ( save_path , width , height , channel , image , width * channel );
printf (" New image saved to %s\n", save_path );
}