/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Patrick Sturm

*/


#ifndef _ipcstdfilter_h_
#define _ipcstdfilter_h_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0

  Copyright 2002, Patrick Sturm
************************************************/

// Include
#include <ipccolor.h>
#include <ipcmatrix.h>
#include <math.h>
// Functions
void ipcSNNFilter(int width, int height, const ipcRGB* input, ipcRGB* output);
void ipcSNNFilter8bit(int width, int height, const unsigned char* input, unsigned char* output);
void ipcSNNFilter16bit(int width, int height, const unsigned short* input, unsigned short* output);
void ipcKuwaharaNagaoFilter(int width, int height, const ipcRGB* input, ipcRGB* output);
void ipcKuwaharaNagaoFilter8bit(int width, int height, const unsigned char* input, unsigned char* output);
void ipcKuwaharaNagaoFilter16bit(int width, int height, const unsigned short* input, unsigned short* output);

/** low-pass filtering of input image with Gaussian convolution. Discrete mask calculated by Gaussian.*/
void ipcGaussianFilter(int imageWidth, int imageHeight, const unsigned char* input, unsigned char* output, float sigma);

/** low-pass filtering of input image with Gaussian convolution. Approximated calculation (Pascal).*/
void ipcGaussianFilterPascal(int imageWidth, int imageHeight, const unsigned char* input, unsigned char* output, int maskradius);

/** calculating horizontal and vertical derivatives. Discrete mask calculated with the first derivative of a Gaussian. */
void ipcGaussianDerivation(int imageWidth, int imageHeight, const unsigned char* input, float sigma, 
	int* xOutput, int* yOutput, int& minXValue, int& maxXValue, int& minYValue, int& maxYValue);

/** calculating vertical derivative by filtering with sobel mask.*/
void ipcSobelFilterX(int imageWidth, int imageHeight, const unsigned char* input, int* xOutput, int& minValue, int& maxValue);

/** calculating horizontal derivative by filtering with sobel mask.*/
void ipcSobelFilterY(int imageWidth, int imageHeight, const unsigned char* input, int* yOutput, int& minValue, int& maxValue);

/** calculating the gradient magnitude from directional derivatives with euclidean distance.*/
void ipcEdgeStrength(int imageWidth, int imageHeight, const int* xInput, const int* yInput,	unsigned short* edgeOutput, int& maxValue);

/** calculating the gradient direction from directional derivatives. */
void ipcOrientation(int imageWidth, int imageHeight, const int* xInput, const int* yInput, unsigned short* orientOutput);
		
//! This function applies a filter function several times on an image.
/*
  \param 
*/
template <class ipcPixelType>
void ipcIterateStdFilter(int width, int height, const ipcPixelType* input, ipcPixelType* output, ipcPixelType* temp, 
                         int iterations, void(*filter)(int,int,const ipcPixelType*,ipcPixelType*))
{
  ipcPixelType* images[2];

  images[0]=temp;
  images[1]=output;

  if (iterations>0)
  {
    int target=1;
    iterations--;
    (*filter)(width,height,input,images[target]);
    target=1-target;
    while (iterations>0)
    { 
      iterations--;
      (*filter)(width,height,images[1-target],images[target]);
      target=1-target;
    }
    if (target==1) memcpy(output,temp,sizeof(ipcPixelType)*width*height);
  }
}


#endif
