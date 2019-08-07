/*
aflair
prog6.c by Andrew Flair
ECE 2220 - Spring 2015
Programming Assignment 6
4/13/15

Purpose:
The purpose of this program is to take in two command line inputs,
one should be the name of an input 24-bit .bmp file and the second
should be the desired name of an output 24-bit .bmp file. The
program then reads the header information and pixel data of the
input file and applies a filter to the pixels. The filtered image
is stored into a seperate pixel data array and is then written to
a file with the desired output name.


Assumptions:
- The first command line argument is the name of a valid .bmp file in the directory
- The .bmp file is a standard format 24-bit .bmp file

*/

#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)
 
struct Header
{
   unsigned short int Type;
   unsigned int Size;
   unsigned short int Reserved1, Reserved2;
   unsigned int Offset;
} Header; 
 
struct InfoHeader
{
   unsigned int Size;
   int Width, Height;
   unsigned short int Planes;
   unsigned short int Bits;
   unsigned int Compression;
   unsigned int ImageSize;
   int xResolution, yResolution;
   unsigned int Colors;
   unsigned int ImportantColors;
} InfoHeader;
 
struct sPixel
{
   unsigned char Blue, Green, Red;
};
 
int main(int argc, char *argv[]) {
 
	int pixel_size, i, j;
	int pad = 0;
	char temp[4];
	int filter[3][3] =
	{{ 0, -1,  0},
	 {-1,  4, -1},
	 { 0, -1,  0},
	};
	
	i = 0;
	j = 0;
	
	/* Open input file and determine if it is real */
	FILE *input = fopen (argv[1], "rb");
	if (input == NULL) {
		printf("\nIncorrect input file name.\n");
		return -1;
	}
	
	printf("\nReading file %s...", argv[1]);
 	
 	/* Read header information */
   	fread(&Header, sizeof(Header), 1, input);
   	fread(&InfoHeader, sizeof(InfoHeader), 1, input);
	 
	/* Create padding for if it is needed when reading pixels  */
   	pad = InfoHeader.Width % 4;
   	if(pad != 0 ) {
   	   pad = 4 - pad;
   	}
   	 
   	pixel_size = sizeof(struct sPixel);
   	struct sPixel **pixeldata;
   	 
   	/* Allocate pixel array memory */
   	pixeldata = (struct sPixel **)calloc(InfoHeader.Height, sizeof(struct sPixel *));
	 
   	for(i=0;i<InfoHeader.Height; i++) {
   	   pixeldata[i] = (struct sPixel *)calloc(InfoHeader.Width, pixel_size);
   	}
   	
   	/* Read pixels into pixel structure array */
   	for(i=0; i < InfoHeader.Height; i++) {
   	   for(j=0; j < InfoHeader.Width; j++) {
   	      fread(&pixeldata[i][j], 3, 1, input);    
   	   }
   	   if(pad != 0) {
   	      fread(&temp, pad, 1, input);            
   	   }
   	}
   	
	printf("Done\n");
   	
	fclose(input);
	
	/* Create and allocate another pixel array structure for output */ 	
   	struct sPixel **pixeldata2;
   	pixeldata2 = (struct sPixel **)calloc(InfoHeader.Height, sizeof(struct sPixel*));// uhm
   	for(i=0;i<InfoHeader.Height; i++) {
   	   pixeldata2[i] = (struct sPixel *)calloc(InfoHeader.Width, pixel_size);
   	}
   	
   	/* Copy input array into output array */
   	for(i = 0; i < InfoHeader.Height; i++){
   		for(j = 0; j < InfoHeader.Width; j++){
   			pixeldata2[i][j] = pixeldata[i][j];
		}
	}
	
	/* 3x3 matrix filter[][] is applied to first pixel array and saved into second pixel array. 
	   pr, pg, and pb are int variables used to add up the multiplications of the filter and
	   the pixel values both of the current pixel and the surrounding pixels.
	*/
	
	printf("\nApplying filter...");
	
	int pr = 0, pg = 0, pb = 0;
	
   	for(i = 0; i < InfoHeader.Height; i++){
   		for(j = 0; j < InfoHeader.Width; j++){
   			if((i > 1) && (j > 1) && (i < InfoHeader.Height -1) && (j < InfoHeader.Width - 1)){
				pr += filter[0][0] * pixeldata[i-1][j-1].Red;
				pg += filter[0][0] * pixeldata[i-1][j-1].Green;
				pb += filter[0][0] * pixeldata[i-1][j-1].Blue;
				pr += filter[0][1] * pixeldata[i-1][j].Red;
				pg += filter[0][1] * pixeldata[i-1][j].Green;
				pb += filter[0][1] * pixeldata[i-1][j].Blue;
				pr += filter[0][2] * pixeldata[i-1][j+1].Red;
				pg += filter[0][2] * pixeldata[i-1][j+1].Green;
				pb += filter[0][2] * pixeldata[i-1][j+1].Blue;
				pr += filter[1][0] * pixeldata[i][j-1].Red;
				pg += filter[1][0] * pixeldata[i][j-1].Green;
				pb += filter[1][0] * pixeldata[i][j-1].Blue;
				pr += filter[1][1] * pixeldata[i][j].Red;
				pg += filter[1][1] * pixeldata[i][j].Green;
				pb += filter[1][1] * pixeldata[i][j].Blue;
				pr += filter[1][2] * pixeldata[i][j+1].Red;
				pg += filter[1][2] * pixeldata[i][j+1].Green;
				pb += filter[1][2] * pixeldata[i][j+1].Blue;
				pr += filter[2][0] * pixeldata[i+1][j-1].Red;
				pg += filter[2][0] * pixeldata[i+1][j-1].Green;
				pb += filter[2][0] * pixeldata[i+1][j-1].Blue;
				pr += filter[2][1] * pixeldata[i+1][j].Red;
				pg += filter[2][1] * pixeldata[i+1][j].Green;
				pb += filter[2][1] * pixeldata[i+1][j].Blue;
				pr += filter[2][2] * pixeldata[i+1][j+1].Red;
				pg += filter[2][2] * pixeldata[i+1][j+1].Green;
				pb += filter[2][2] * pixeldata[i+1][j+1].Blue;

				pixeldata2[i][j].Red = pr;
				pixeldata2[i][j].Green = pg;
				pixeldata2[i][j].Blue = pb;
				pr = 0; pg = 0; pb = 0;
			}
		}
	}
	
	printf("Done\n");   	  	
   	
   	/* Open output file for writing */
   	FILE *output = fopen(argv[2], "wb");
   	if (output == NULL) {
   	   printf("\nError opening output file.\n");
   	   return -1;
   	}
   	
   	printf("\nWriting data to new file %s...", argv[2]);
   	
   	/* Write header information first */
   	fwrite(&Header, sizeof(Header), 1,  output);
   	fwrite(&InfoHeader, sizeof(InfoHeader), 1, output);
   	 
   	/* For loop to write pixel data into output using same method as reading */
   	for(i=0; i < InfoHeader.Height ; i++) {
   	   for(j=0; j < InfoHeader.Width; j++) {   
   	      fwrite(&pixeldata2[i][j], pixel_size, 1, output);
   	   }
   	   if(pad != 0) {
   	      fwrite(&temp, pad, 1, output);
   	   }
   	}
	
	printf("Done\n\n");
	
	/* Free memory allocations */
	for(i=0; i<InfoHeader.Height; i++) {
		free(pixeldata[i]);
		pixeldata[i] = NULL;
		free(pixeldata2[i]);
		pixeldata2[i] = NULL;
	}
	free(pixeldata);
	pixeldata = NULL;
	free(pixeldata2);
	pixeldata2 = NULL;
	
		
   	fclose(output);
  	 
	return 0;
}
