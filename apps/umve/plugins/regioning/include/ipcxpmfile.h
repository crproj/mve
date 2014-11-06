/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz-Landau, Patrick Sturm

*/


#ifndef _ipcxpmfile_h_
#define _ipcxpmfile_h_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0
  
  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
//#include <ipcimages.h>
#include <ipcmatrix.h>
#include <ipccolor.h>
#include <adverror.h>


// Excpeption
ADV_NEW_STD_EXCEPTION(ipcXPMException,"XPM-File invalid");
ADV_NEW_SUB_EXCEPTION(ipcEXPMSyntax,ipcXPMException,"Syntax Error in PPM-File");
ADV_NEW_SUB_EXCEPTION(ipcEXPMUnsupportedMagicNumber,ipcXPMException,"Unsupported Magicnumber...");


// XPMHeader
struct ipcXPMHeader
{
  char magicCode[3];
  int width,height;
  int maxValue;
};

// Forward-Declarations
extern void ipcReadXPMHeader(const char* filename, ipcXPMHeader& header);
extern int ipcLoadPGMFile(const char* filename, ipcMatrix<unsigned short>& result);
extern void ipcLoadPPMFile(const char* filename, ipcMatrix<ipcRGB>& result);
extern void ipcSavePGMFile(const char* filename, const ipcMatrix<unsigned short>& image, int maxValue = 255);
extern void ipcSavePPMFile(const char* filename, const ipcMatrix<ipcRGB>& image);

/*extern ipcAbstractImage* ipcLoadXPMFile(const char* filename);
extern void ipcSaveXPMFile(const char* filename, const ipcAbstractImage* image);*/



#endif