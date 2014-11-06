/* 

  This "SOFTWARE" is a free software.
  
    You are allowed to download, use, modify and redistribute this software.
    The software is provided "AS IS" without warranty of any kind.
    
      Copyright: University of Koblenz, Lutz Priese, Volker Rehrman, Patrick Sturm
      
*/


#ifndef _IPCSTDHSVLINKCONTROL_H_
#define _IPCSTDHSVLINKCONTROL_H_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0

  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <ipccolor.h>
#include <ipchsvcolsim.h>
#include <ipchsvclassiccolsim.h>
#include <ipccodebase.h>
#include <math.h>

// ipcStdHSVLinkControl
class ipcStdHSVLinkControl: public ipcHSVSimilarityFunction
{
private:
  int count,currLevel;
  int redSum,greenSum,blueSum;
  ipcHSV avgHSV;
  
public:
  ipcStdHSVLinkControl();
  
  inline void begin(int level, const ipcHSV& hsv);
  inline void add(const ipcHSV& hsv);
  inline bool add(const ipcHSV& hsv1, const ipcHSV& hsv2);
  
  inline void begin(int level, const ipcCodeelement<ipcHSV>* ce);
  inline void add(const ipcCodeelement<ipcHSV>* ce);
  inline bool add(const ipcCodeelement<ipcHSV>* ce1, const ipcCodeelement<ipcHSV>* ce2);
  
  inline void setFeature(ipcHSV& hsv);
  inline int compareFeatures(const ipcHSV& hsvCE1, const ipcHSV& hsvCE2, const ipcHSV& hsvSubCE);
};


// ipcStdHSVLinkControlOnRGB
class ipcStdHSVLinkControlOnRGB : public ipcHSVSimilarityFunction
{
private:
  int count,currLevel;
  int redSum,greenSum,blueSum;
  int avgRed,avgBlue,avgGreen;
  ipcHSV rgbToHSV[64][64][64];
  ipcHSV avgHSV;
  
public:
  ipcStdHSVLinkControlOnRGB();
  
  inline void begin(int level, const ipcRGB& rgb);
  inline void add(const ipcRGB& rgb);
  inline bool add(const ipcRGB& rgb1, const ipcRGB& rgb2);
  
  inline void begin(int level, const ipcCodeelement<ipcRGB>* ce);
  inline void add(const ipcCodeelement<ipcRGB>* ce);
  inline bool add(const ipcCodeelement<ipcRGB>* ce1, const ipcCodeelement<ipcRGB>* ce2);
  
  inline void setFeature(ipcRGB& rgb);
  inline int compareFeatures(const ipcRGB& rgbCE1, const ipcRGB& rgbCE2, const ipcRGB& rgbSubCE);
};


// ipcStdHSVLinkControl
class ipcClassicHSVLinkControl : public ipcClassicHSVSimilarityFunction
{
private:
  int count,hueCount,currLevel;
  bool red;
  int hueSum,satSum,valSum;
  ipcHSV avgHSV;
  
public:
  ipcClassicHSVLinkControl();
  
  inline void begin(int level, const ipcHSV& hsv);
  inline void add(const ipcHSV& hsv);
  inline bool add(const ipcHSV& hsv1, const ipcHSV& hsv2);
  
  inline void begin(int level, const ipcCodeelement<ipcHSV>* ce);
  inline void add(const ipcCodeelement<ipcHSV>* ce);
  inline bool add(const ipcCodeelement<ipcHSV>* ce1, const ipcCodeelement<ipcHSV>* ce2);
  
  inline void setFeature(ipcHSV& hsv);
  inline int compareFeatures(const ipcHSV& hsvCE1, const ipcHSV& hsvCE2, const ipcHSV& hsvSubCE);
};


// Implementation of ipcStdHSVLinkControl
inline void ipcStdHSVLinkControl::begin(int level, const ipcHSV& hsv)
{
  ipcRGB rgb;
  
  avgHSV=hsv;
  currLevel=level;
  ipcConvertHSVToRGB(hsv,rgb);
  redSum=rgb.red;
  greenSum=rgb.green;
  blueSum=rgb.blue;
  count=1;
}


inline void ipcStdHSVLinkControl::begin(int level, const ipcCodeelement<ipcHSV>* ce)
{
  ipcRGB rgb;
  int weight=(ce->numOfSubCEs>0) ? ce->numOfSubCEs : 1;
  
  avgHSV=ce->data;
  currLevel=level;
  ipcConvertHSVToRGB(avgHSV,rgb);
  redSum=weight*(int)rgb.red;
  greenSum=weight*(int)rgb.green;
  blueSum=weight*(int)rgb.blue;
  count=weight;
}


inline void ipcStdHSVLinkControl::add(const ipcHSV& hsv)
{
  ipcRGB rgb;
  
  ipcConvertHSVToRGB(hsv,rgb);
  redSum+=rgb.red;
  greenSum+=rgb.green;
  blueSum+=rgb.blue;
  count++;
}


inline bool ipcStdHSVLinkControl::add(const ipcHSV& hsv1, const ipcHSV& hsv2)
{
  if (colorSimilar(hsv1.hue,hsv1.sat,hsv1.val,hsv2.hue,hsv2.sat,hsv2.val)) 
  {
    add(hsv2);
    return true;
  }
  return false;
}


inline void ipcStdHSVLinkControl::add(const ipcCodeelement<ipcHSV>* ce)
{
  ipcRGB rgb;
  int weight=(ce->numOfSubCEs>0) ? ce->numOfSubCEs : 1;
  
  ipcConvertHSVToRGB(ce->data,rgb);
  redSum+=weight*(int)rgb.red;
  greenSum+=weight*(int)rgb.green;
  blueSum+=weight*(int)rgb.blue;
  count+=weight;
  rgb.red=redSum/count;
  rgb.green=greenSum/count;
  rgb.blue=blueSum/count;
  ipcConvertRGBToHSV(rgb,avgHSV);
}


inline bool ipcStdHSVLinkControl::add(const ipcCodeelement<ipcHSV>* ce1, const ipcCodeelement<ipcHSV>* ce2)
{
	(void)ce1;
  if (colorSimilar(avgHSV.hue,avgHSV.sat,avgHSV.val,ce2->data.hue,ce2->data.sat,ce2->data.val) 
    /*&& colorSimilar(ce1->data.hue,ce1->data.sat,ce1->data.val,ce2->data.hue,ce2->data.sat,ce2->data.val)*/)
  {
    add(ce2);
    return true;
  }
  return false;
}

inline void ipcStdHSVLinkControl::setFeature(ipcHSV& hsv)
{
  if (currLevel==0)
  {
    ipcRGB avgRGB;
    
    avgRGB.red=redSum/count;
    avgRGB.green=greenSum/count;
    avgRGB.blue=blueSum/count;
    ipcConvertRGBToHSV(avgRGB,hsv);
  }
  else hsv=avgHSV;
}


inline int ipcStdHSVLinkControl::compareFeatures(const ipcHSV& hsvCE1, const ipcHSV& hsvCE2, const ipcHSV& hsvSubCE)
{
  return compareColors(hsvSubCE.hue,hsvSubCE.sat,hsvSubCE.val,
    hsvCE1.hue,hsvCE1.sat,hsvCE1.val,
    hsvCE2.hue,hsvCE2.sat,hsvCE2.val);
}



// Implementation of ipcStdHSVLinkControlOnRGB
inline void ipcStdHSVLinkControlOnRGB::begin(int level, const ipcRGB& rgb)
{
  currLevel=level;
  count=1;
  redSum=rgb.red;
  greenSum=rgb.green;
  blueSum=rgb.blue;
}


inline void ipcStdHSVLinkControlOnRGB::add(const ipcRGB& rgb)
{
  redSum+=rgb.red;
  greenSum+=rgb.green;
  blueSum+=rgb.blue;
  count++;
}


inline bool ipcStdHSVLinkControlOnRGB::add(const ipcRGB& rgb1, const ipcRGB& rgb2)
{
  const ipcHSV& hsv1 = rgbToHSV[rgb1.red>>2][rgb1.green>>2][rgb1.blue>>2];
  const ipcHSV& hsv2 = rgbToHSV[rgb2.red>>2][rgb2.green>>2][rgb2.blue>>2];
  
  if (colorSimilar(hsv1.hue,hsv1.sat,hsv1.val,hsv2.hue,hsv2.sat,hsv2.val))
  {
    add(rgb2);
    return true;
  }
  return false;
}


inline void ipcStdHSVLinkControlOnRGB::begin(int level, const ipcCodeelement<ipcRGB>* ce)
{
  //int weight=(ce->numOfSubCEs>0) ? ce->numOfSubCEs : 1;
  int weight=1<<ce->numOfSubCEs;
  redSum=weight*(int)ce->data.red;
  greenSum=weight*(int)ce->data.green;
  blueSum=weight*(int)ce->data.blue;
  count=weight;
  currLevel=level;
  avgRed=ce->data.red;
  avgGreen=ce->data.green;
  avgBlue=ce->data.blue;
  avgHSV=rgbToHSV[avgRed>>2][avgGreen>>2][avgBlue>>2];
}


inline void ipcStdHSVLinkControlOnRGB::add(const ipcCodeelement<ipcRGB>* ce)
{
  int weight=1<<ce->numOfSubCEs;
  
  redSum+=weight*(int)ce->data.red;
  greenSum+=weight*(int)ce->data.green;
  blueSum+=weight*(int)ce->data.blue;
  count+=weight;
  avgRed=redSum/count;
  avgGreen=greenSum/count;
  avgBlue=blueSum/count;
  avgHSV=rgbToHSV[avgRed>>2][avgGreen>>2][avgBlue>>2];
}


inline bool ipcStdHSVLinkControlOnRGB::add(const ipcCodeelement<ipcRGB>* ce1, const ipcCodeelement<ipcRGB>* ce2)
{
	(void)ce1;
  //const ipcHSV& hsv1 = rgbToHSV[ce1->data.red>>2][ce1->data.green>>2][ce1->data.blue>>2];
  const ipcHSV& hsv2 = rgbToHSV[ce2->data.red>>2][ce2->data.green>>2][ce2->data.blue>>2];
  
  if (colorSimilar(avgHSV.hue,avgHSV.sat,avgHSV.val,hsv2.hue,hsv2.sat,hsv2.val) 
    /*&& colorSimilar(hsv1.hue,hsv1.sat,hsv1.val,hsv2.hue,hsv2.sat,hsv2.val)*/)
  {
    add(ce2);
    return true;
  }
  return false;
}


inline void ipcStdHSVLinkControlOnRGB::setFeature(ipcRGB& rgb)
{
  if (currLevel==0)
  {
    rgb.red=redSum/count;
    rgb.green=greenSum/count;
    rgb.blue=blueSum/count;
  }
  else
  {
    rgb.red=avgRed;
    rgb.green=avgGreen;
    rgb.blue=avgBlue;
  }
}


inline int ipcStdHSVLinkControlOnRGB::compareFeatures(const ipcRGB& rgbCE1, const ipcRGB& rgbCE2, const ipcRGB& rgbSubCE)
{
  const ipcHSV& hsvCE1   = rgbToHSV[rgbCE1.red>>2][rgbCE1.green>>2][rgbCE1.blue>>2];
  const ipcHSV& hsvCE2   = rgbToHSV[rgbCE2.red>>2][rgbCE2.green>>2][rgbCE2.blue>>2];
  const ipcHSV& hsvSubCE = rgbToHSV[rgbSubCE.red>>2][rgbSubCE.green>>2][rgbSubCE.blue>>2];
  
  return compareColors(hsvSubCE.hue,hsvSubCE.sat,hsvSubCE.val,
    hsvCE1.hue,hsvCE1.sat,hsvCE1.val,
    hsvCE2.hue,hsvCE2.sat,hsvCE2.val);
}


// ipcStdHSVLinkControl
void ipcClassicHSVLinkControl::begin(int level, const ipcHSV& hsv)
{
  currLevel=level;
  if (hsv.sat>0)
  {
    red=(hsv.hue>=300);
    hueSum=hsv.hue;
    hueCount=1;
  }
  else 
  {
    hueCount=0;
    hueSum=0;
    red=false;
  }
  satSum=hsv.sat;
  valSum=hsv.val;
  count=1;
}


void ipcClassicHSVLinkControl::add(const ipcHSV& hsv)
{
  if (hsv.sat>0)
  {
    if (hsv.hue<=60 && red) hueSum+=hsv.hue+360;
    else if (hsv.hue>=300 && !red)
    {
      hueSum+=hueCount*360+hsv.hue;
      red=true;
    }
    else hueSum+=hsv.hue;
    hueCount++;
  }
  satSum+=hsv.sat;
  valSum+=hsv.val;
  count++;
}


bool ipcClassicHSVLinkControl::add(const ipcHSV& hsv1, const ipcHSV& hsv2)
{
  if (colorSimilar(hsv1.hue,hsv1.sat,hsv1.val,hsv2.hue,hsv2.sat,hsv2.val))
  {
    add(hsv2);
    return true;
  }
  return false;
}


void ipcClassicHSVLinkControl::begin(int level, const ipcCodeelement<ipcHSV>* ce)
{
  currLevel=level;
  if (ce->data.sat>0)
  {
    red=(ce->data.hue>=300);
    hueSum=ce->data.hue;
    hueCount=1;
  }
  else 
  {
    hueCount=0;
    hueSum=0;
    red=false;
  }
  satSum=ce->data.sat;
  valSum=ce->data.val;
  avgHSV.hue=hueSum;
  avgHSV.sat=satSum;
  avgHSV.val=valSum;
  count=1;
}


void ipcClassicHSVLinkControl::add(const ipcCodeelement<ipcHSV>* ce)
{
  if (ce->data.sat>0)
  {
    if (ce->data.hue<=60 && red) hueSum+=ce->data.hue+360;
    else if (ce->data.hue>=300 && !red)
    {
      hueSum+=hueCount*360+ce->data.hue;
      red=true;
    }
    else hueSum+=ce->data.hue;
    hueCount++;
  }
  satSum+=ce->data.sat;
  valSum+=ce->data.val;
  count++;
  
  if (hueCount>0) 
  {
    avgHSV.hue=(hueSum+(hueCount>>1))/hueCount;
    if (avgHSV.hue>=360) avgHSV.hue-=360;
  }
  else avgHSV.hue=0;
  avgHSV.sat=(satSum+(count>>1))/count;
  avgHSV.val=(valSum+(count>>1))/count;
  hueSum=avgHSV.hue*hueCount;
  red=(avgHSV.hue>300);
}


bool ipcClassicHSVLinkControl::add(const ipcCodeelement<ipcHSV>* ce1, const ipcCodeelement<ipcHSV>* ce2)
{
	(void)ce1;
  if (colorSimilar(avgHSV.hue,avgHSV.sat,avgHSV.val,ce2->data.hue,ce2->data.sat,ce2->data.val)
    /*&& colorSimilar(ce1->data.hue,ce1->data.sat,ce1->data.val,ce2->data.hue,ce2->data.sat,ce2->data.val)*/)
  {
    add(ce2);
    return true;
  }
  return false;
}


void ipcClassicHSVLinkControl::setFeature(ipcHSV& hsv)
{
  if (currLevel==0)
  {
    if (hueCount>0) 
    {
      avgHSV.hue=(hueSum+(hueCount>>1))/hueCount;
      if (avgHSV.hue>=360) avgHSV.hue-=360;
    }
    else avgHSV.hue=0;
    
    avgHSV.sat=(satSum+(count>>1))/count;
    avgHSV.val=(valSum+(count>>1))/count;
  }
  hsv.hue=avgHSV.hue;
  //hsv.sat=(avgHSV.sat>>4)<<4;
  //hsv.val=(avgHSV.val>>3)<<3;
  hsv.sat=(255*((int)(avgHSV.sat)>>4))/15;
  hsv.val=(255*((int)(avgHSV.val)>>3))/31;
}


int ipcClassicHSVLinkControl::compareFeatures(const ipcHSV& hsvCE1, const ipcHSV& hsvCE2, const ipcHSV& hsvSubCE)
{
  return compareColors(hsvSubCE.hue,hsvSubCE.sat,hsvSubCE.val,
    hsvCE1.hue,hsvCE1.sat,hsvCE1.val,
    hsvCE2.hue,hsvCE2.sat,hsvCE2.val);
}


#endif
