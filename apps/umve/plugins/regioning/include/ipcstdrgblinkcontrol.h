/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Lutz Priese, Volker Rehrman, Patrick Sturm

*/


#ifndef _IPCSTDRGBLINKCONTROL_H_
#define _IPCSTDRGBLINKCONTROL_H_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0

  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <ipccolor.h>
#include <ipccodebase.h>

// ipcStdRGBLinkControl
class ipcStdRGBLinkControl
{
private:
  int count,redSum,greenSum,blueSum;
  int avgRed,avgGreen,avgBlue;
  int currLevel,thresholdQuad;

public:
  inline ipcStdRGBLinkControl();
  inline void setThreshold(int threshold);
  inline void begin(int level, const ipcRGB& rgb);
  inline void add(const ipcRGB& rgb);
  inline bool add(const ipcRGB& rgb1, const ipcRGB& rgb2);
  inline void begin(int level, const ipcCodeelement<ipcRGB>* ce);
  inline void add(const ipcCodeelement<ipcRGB>* ce);
  inline bool add(const ipcCodeelement<ipcRGB>* ce1, const ipcCodeelement<ipcRGB>* ce2);
  inline void setFeature(ipcRGB& avgRGB);
  inline int compareFeatures(const ipcRGB& rgbCE1, const ipcRGB& rgbCE2, const ipcRGB& rgbSubCEs);
};


// ipcStdRGBLinkControl
inline ipcStdRGBLinkControl::ipcStdRGBLinkControl() 
{ 
  count=0; 
  redSum=0; 
  greenSum=0; 
  blueSum=0; 
  avgRed=0;
  avgGreen=0;
  avgBlue=0;
  currLevel=0;
  thresholdQuad=400;
}


inline void ipcStdRGBLinkControl::setThreshold(int threshold)
{
  thresholdQuad=threshold*threshold;
}


inline void ipcStdRGBLinkControl::begin(int level, const ipcRGB& rgb) 
{ 
  avgRed=redSum=rgb.red; 
  avgGreen=greenSum=rgb.green; 
  avgBlue=blueSum=rgb.blue; 
  count=1; 
  currLevel=level; 
}


inline void ipcStdRGBLinkControl::add(const ipcRGB& rgb)
{
  redSum+=rgb.red;
  greenSum+=rgb.green;
  blueSum+=rgb.blue;
  count++;
  if (currLevel>0)
  {
	  avgRed=redSum/count;
    avgGreen=greenSum/count;
    avgBlue=blueSum/count;
  }
}


inline bool ipcStdRGBLinkControl::add(const ipcRGB& rgb1, const ipcRGB& rgb2)
{
  int deltaRed,deltaGreen,deltaBlue,delta/*,delta2*/;

  if (currLevel==0)
  {
		deltaRed = (int)rgb1.red-rgb2.red;
		deltaGreen = (int)rgb1.green-rgb2.green;
		deltaBlue = (int)rgb1.blue-rgb2.blue;
		delta = deltaRed*deltaRed+deltaGreen*deltaGreen+deltaBlue*deltaBlue;
  }
  else //if (currLevel>0)
  {
  	deltaRed = avgRed-rgb2.red;
		deltaGreen = avgGreen-rgb2.green;
		deltaBlue = avgBlue-rgb2.blue;
		delta = deltaRed*deltaRed+deltaGreen*deltaGreen+deltaBlue*deltaBlue;
		//if (delta2>delta) delta=delta2;
  }

  if (delta<=thresholdQuad)
  {
    add(rgb2);
    return true;
  }
  return false;
}

 
inline void ipcStdRGBLinkControl::begin(int level, const ipcCodeelement<ipcRGB>* ce)
{
  begin(level,ce->data);
}


inline void ipcStdRGBLinkControl::add(const ipcCodeelement<ipcRGB>* ce)
{
  add(ce->data);
}


inline bool ipcStdRGBLinkControl::add(const ipcCodeelement<ipcRGB>* ce1, const ipcCodeelement<ipcRGB>* ce2)
{
  return add(ce1->data,ce2->data);
}


inline void ipcStdRGBLinkControl::setFeature(ipcRGB& avgRGB)
{
  if (currLevel==0)
  {
    avgRGB.red=redSum/count;
    avgRGB.green=greenSum/count;
    avgRGB.blue=blueSum/count;
  }
  else
  {
    avgRGB.red=avgRed;
    avgRGB.green=avgGreen;
    avgRGB.blue=avgBlue;
  }
}


inline int ipcStdRGBLinkControl::compareFeatures(const ipcRGB& rgbCE1, const ipcRGB& rgbCE2, const ipcRGB& rgbSubCE)
{
  int deltaRed1 = (int)rgbCE1.red-(int)rgbSubCE.red;
  int deltaGreen1 = (int)rgbCE1.green-(int)rgbSubCE.green;
  int deltaBlue1 = (int)rgbCE1.blue-(int)rgbSubCE.blue;
  int delta1 = deltaRed1*deltaRed1+deltaGreen1*deltaGreen1+deltaBlue1*deltaBlue1;
  int deltaRed2 = (int)rgbCE2.red-(int)rgbSubCE.red;
  int deltaGreen2 = (int)rgbCE2.green-(int)rgbSubCE.green;
  int deltaBlue2 = (int)rgbCE2.blue-(int)rgbSubCE.blue;
  int delta2 = deltaRed2*deltaRed2+deltaGreen2*deltaGreen2+deltaBlue2*deltaBlue2;
 
  if (delta1<=delta2) return 1;

  return 2;
}


#endif
