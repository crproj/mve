/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Patrick Sturm

*/


#ifndef _ipcpnmfile_h_
#define _ipcpnmfile_h_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0
  
  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <ipcmatrix.h>
#include <ipccolor.h>
#include <adverror.h>


// Excpeption
ADV_NEW_STD_EXCEPTION(ipcPNMException,"PNM-File invalid");
ADV_NEW_SUB_EXCEPTION(ipcEPNMSyntax,ipcPNMException,"Syntax Error in PPM-File");
ADV_NEW_SUB_EXCEPTION(ipcEPNMUnsupportedMagicNumber,ipcPNMException,"Unsupported Magicnumber...");

// Image-Format
enum ipcImageFormat {ipcIFUnknown, ipcIFGray, ipcIFRGB, ipcIFBit};


// PNMHeader
struct ipcPNMHeader
{
  char magicCode[3];
  int width,height;
  int maxValue;
  ipcImageFormat format;
};


// Forward-Declarations
void ipcReadPNMHeader(const char* filename, ipcPNMHeader& header);
void ipcLoadPNM(const char* filename, ipcPNMHeader& header, unsigned char* &image, bool allocateMemory = true);
void ipcSavePNM(const char* filename, ipcPNMHeader& header, unsigned char* image);
void ipcLoadPNM(const char* filename, ipcMatrix<ipcRGB>& image);
void ipcLoadPNM(const char* filename, ipcMatrix<unsigned short>& image, int& maxVal);
void ipcLoadPNM(const char* filename, ipcMatrix<unsigned char>& image, int& maxVal);
void ipcSavePNM(const char* filename, ipcMatrix<unsigned char>& image, int maxVal);
void ipcSavePNM(const char* filename, ipcMatrix<unsigned short>& image, int maxVal);
void ipcSavePNM(const char* filename, ipcMatrix<ipcRGB>& image);
void ipcSavePBM(const char* filename, ipcMatrix<unsigned char>& image);

#endif
