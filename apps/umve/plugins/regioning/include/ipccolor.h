/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Patrick Sturm

*/


#ifndef _ipccolor_h_
#define _ipccolor_h_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0
  
  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <iostream>

//! Structure that describes the three components of a rgb color
const short ipcUndefinedHue = -1;

//! Structure that describes the three components of a rgb color
struct ipcRGB
{
  unsigned char red,green,blue;
};


//! Structure that describes the three components of a hsv color
struct ipcHSV
{
  short hue;
  unsigned char sat,val;
};


// Functions
void ipcConvertHSToCartesian(int hue, int sat, int& x, int& y);
void ipcConvertCartesianToHS(int x, int y, short& hue, unsigned char& sat);
void ipcConvertRGBToHSV(double r, double g, double b, double& h, double& s, double& v);
void ipcConvertHSVToRGB(double h, double s, double v, double& r, double& g, double& b);
void ipcConvertRGBToHSV(int w, int h, const ipcRGB* source, ipcHSV* target, bool school = false);
void ipcConvertHSVToRGB(int w, int h, const ipcHSV* source, ipcRGB* target);
void ipcConvertRGBToHSV(int size, const ipcRGB* source, ipcHSV* target, bool school = false);
void ipcConvertHSVToRGB(int size, const ipcHSV* source, ipcRGB* target);
void ipcConvertRGBToHSV(const ipcRGB& rgb, ipcHSV& hsv);
void ipcConvertHSVToRGB(const ipcHSV& hsv, ipcRGB& rgb);
void ipcConvertRGBToHSVSchool(const ipcRGB& rgb, ipcHSV& hsv);
void ipcConvertRGBToHSVSchool(int r, int g, int b, int &h, int &s, int &v);
void ipcConvertRGBToHSVSchool(int r, int g, int b, ipcHSV& hsv);

std::ostream& operator << (std::ostream& out, const ipcRGB& rgb);
std::ostream& operator << (std::ostream& out, const ipcHSV& hsv);

#endif
