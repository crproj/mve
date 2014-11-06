#pragma GCC system_header
/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Lutz Priese, Volker Rehrman, Patrick Sturm

*/


#ifndef _IPCTRAFFICSIGNLINKCONTROL_H_
#define _IPCTRAFFICSIGNLINKCONTROL_H_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0

  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <ipccolor.h>
#include <ipchsvcolsim.h>
#include <ipctrafficsigncolsim.h>
#include <ipccodebase.h>
#include <math.h>

// ipcTrafficSignLinkControl
class ipcTrafficSignLinkControl: public ipcTrafficSignHSVSimilarityFunction
{
private:
  int count,hueCount,redLowCount,redHighCount,currLevel;
	int hueSum,satSum,valSum;
  ipcHSV avgHSV;

public:
  ipcTrafficSignLinkControl();

  inline void begin(int level, const ipcHSV& hsv);
  inline void add(const ipcHSV& hsv);
  inline bool add(const ipcHSV& hsv1, const ipcHSV& hsv2);

  inline void begin(int level, const ipcCodeelement<ipcHSV>* ce);
  inline void add(const ipcCodeelement<ipcHSV>* ce);
  inline bool add(const ipcCodeelement<ipcHSV>* ce1, const ipcCodeelement<ipcHSV>* ce2);

  inline void setFeature(ipcHSV& hsv);
  inline int compareFeatures(const ipcHSV& hsvCE1, const ipcHSV& hsvCE2, const ipcHSV& hsvSubCE);
};


// ipcTrafficSignLinkControlXY
class ipcTrafficSignLinkControlXY: public ipcTrafficSignHSVSimilarityFunction
{
private:
  int currLevel;
	int xSum,ySum,valSum,count;
  ipcHSV avgHSV;

public:
  ipcTrafficSignLinkControlXY();

  inline void begin(int level, const ipcHSV& hsv);
  inline void add(const ipcHSV& hsv);
  inline bool add(const ipcHSV& hsv1, const ipcHSV& hsv2);

  inline void begin(int level, const ipcCodeelement<ipcHSV>* ce);
  inline void add(const ipcCodeelement<ipcHSV>* ce);
  inline bool add(const ipcCodeelement<ipcHSV>* ce1, const ipcCodeelement<ipcHSV>* ce2);

  inline void setFeature(ipcHSV& hsv);
  inline int compareFeatures(const ipcHSV& hsvCE1, const ipcHSV& hsvCE2, const ipcHSV& hsvSubCE);
};


// ipcTrafficSignLinkControl
inline void ipcTrafficSignLinkControl::begin(int level, const ipcHSV& hsv)
{
  currLevel=level;
  redLowCount=0;
	redHighCount=0;
	if (hsv.sat>0)
	{
    hueSum=hsv.hue;
		if (hsv.hue<=60) redLowCount=360;
		else if (hsv.hue>=300) redHighCount=1;
		hueCount=1;
	}
	else 
	{
	  hueCount=0;
		hueSum=0;
	}
	satSum=hsv.sat;
	valSum=hsv.val;
	count=1;
}


inline void ipcTrafficSignLinkControl::add(const ipcHSV& hsv)
{
  if (hsv.sat>0)
  {
	  if (hsv.hue<=60) redLowCount+=360;
    else if (hsv.hue>=300) redHighCount++;
    hueSum+=hsv.hue;
    hueCount++;
	}
	satSum+=hsv.sat;
  valSum+=hsv.val;
  count++;
}


inline bool ipcTrafficSignLinkControl::add(const ipcHSV& hsv1, const ipcHSV& hsv2)
{
  if (colorSimilarDetect(hsv1.hue,hsv1.sat,hsv1.val,hsv2.hue,hsv2.sat,hsv2.val))
	{
	  add(hsv2);		
		return true;
	}
	return false;
}


inline void ipcTrafficSignLinkControl::begin(int level, const ipcCodeelement<ipcHSV>* ce)
{
  //if (level==1) begin(0,ce->data);
  currLevel=level;
  redLowCount=0;
	redHighCount=0;
	if (ce->data.sat>0)
	{
    hueSum=ce->data.hue;
		if (ce->data.hue<=60) redLowCount=360;
		else if (ce->data.hue>=300) redHighCount=1;
		hueCount=1;
	}
	else 
	{
	  hueCount=0;
		hueSum=0;
	}
	satSum=ce->data.sat;
	valSum=ce->data.val;
	avgHSV.hue=hueSum;
	avgHSV.sat=satSum;
	avgHSV.val=valSum;
	count=1;
}


inline void ipcTrafficSignLinkControl::add(const ipcCodeelement<ipcHSV>* ce)
{
  if (ce->data.sat>0)
  {
    if (ce->data.hue<=60) redLowCount+=360;
    else if (ce->data.hue>=300) redHighCount++;
    hueSum+=ce->data.hue;
		hueCount++;
	}
	satSum+=ce->data.sat;
	valSum+=ce->data.val;
	count++;
		
	if (hueCount>0) 
	{
	  if (redHighCount>0)
  	  avgHSV.hue=(hueSum+redLowCount+(hueCount>>1))/hueCount;
		else avgHSV.hue=(hueSum+(hueCount>>1))/hueCount;
  	if (avgHSV.hue>=360) avgHSV.hue=avgHSV.hue-360;
	}
	else avgHSV.hue=0;
	avgHSV.sat=satSum/count;
	avgHSV.val=valSum/count;
	//hueSum=avgHSV.hue*hueCount;
	//red=(avgHSV.hue>300);
}


inline bool ipcTrafficSignLinkControl::add(const ipcCodeelement<ipcHSV>* ce1, const ipcCodeelement<ipcHSV>* ce2)
{
  //if (currLevel==0) return add(ce1->data,ce2->data);
  if (colorSimilarLink(avgHSV.hue,avgHSV.sat,avgHSV.val,ce2->data.hue,ce2->data.sat,ce2->data.val)
   /*&& colorSimilarLink(ce1->data.hue,ce1->data.sat,ce1->data.val,ce2->data.hue,ce2->data.sat,ce2->data.val)*/)
	{
    add(ce2);
		return true;
	}
	return false;
}


inline void ipcTrafficSignLinkControl::setFeature(ipcHSV& hsv)
{
  if (currLevel==0)
	{
		if (hueCount>0) 
		{
		  if (redHighCount>0)
  		  avgHSV.hue=(hueSum+redLowCount+(hueCount>>1))/hueCount;
			else avgHSV.hue=(hueSum+(hueCount>>1))/hueCount;
  		if (avgHSV.hue>=360) avgHSV.hue=avgHSV.hue-360;
		}
  	else avgHSV.hue=0;
		
		avgHSV.sat=satSum/count;
		avgHSV.val=valSum/count;
	}
	hsv.hue=avgHSV.hue;
	//hsv.sat=(255*((int)(avgHSV.sat)>>4))/15;
	//hsv.val=(255*((int)(avgHSV.val)>>4))/15;
	hsv.sat=avgHSV.sat;
	hsv.val=avgHSV.val;
}


inline int ipcTrafficSignLinkControl::compareFeatures(const ipcHSV& hsvCE1, const ipcHSV& hsvCE2, const ipcHSV& hsvSubCE)
{
  return compareColors(hsvSubCE.hue,hsvSubCE.sat,hsvSubCE.val,
                       hsvCE1.hue,hsvCE1.sat,hsvCE1.val,
                       hsvCE2.hue,hsvCE2.sat,hsvCE2.val);
}


// ipcTrafficSignLinkControlXY
inline void ipcTrafficSignLinkControlXY::begin(int level, const ipcHSV& hsv)
{
  currLevel=level;
  ipcConvertHSToCartesian(hsv.hue,hsv.sat,xSum,ySum);
	valSum=hsv.val;
	count=1;
}


inline void ipcTrafficSignLinkControlXY::add(const ipcHSV& hsv)
{
  int x,y;

  ipcConvertHSToCartesian(hsv.hue,hsv.sat,x,y);
  xSum+=x;
  ySum+=y;
  valSum+=hsv.val;
	count++;
}


inline bool ipcTrafficSignLinkControlXY::add(const ipcHSV& hsv1, const ipcHSV& hsv2)

{
  if (colorSimilarDetect(hsv1.hue,hsv1.sat,hsv1.val,hsv2.hue,hsv2.sat,hsv2.val))
	{
    add(hsv2);
		return true;
	}
	return false;
}


inline void ipcTrafficSignLinkControlXY::begin(int level, const ipcCodeelement<ipcHSV>* ce)
{
  currLevel=level;
  ipcConvertHSToCartesian(ce->data.hue,ce->data.sat,xSum,ySum);
	valSum=ce->data.val;
  avgHSV=ce->data;
	count=1;
}


inline void ipcTrafficSignLinkControlXY::add(const ipcCodeelement<ipcHSV>* ce)
{
  int x,y;

  ipcConvertHSToCartesian(ce->data.hue,ce->data.sat,x,y);
  xSum+=x;
  ySum+=y;
  valSum+=ce->data.val;
  count++;
  ipcConvertCartesianToHS(xSum/count,ySum/count,avgHSV.hue,avgHSV.sat);
	avgHSV.val=valSum/count;
}


inline bool ipcTrafficSignLinkControlXY::add(const ipcCodeelement<ipcHSV>* ce1, const ipcCodeelement<ipcHSV>* ce2)
{
  if (colorSimilarLink(avgHSV.hue,avgHSV.sat,avgHSV.val,ce2->data.hue,ce2->data.sat,ce2->data.val)
   /*&& colorSimilarLink(ce1->data.hue,ce1->data.sat,ce1->data.val,ce2->data.hue,ce2->data.sat,ce2->data.val)*/)
	{
    add(ce2);
		return true;
	}
	return false;
}


inline void ipcTrafficSignLinkControlXY::setFeature(ipcHSV& hsv)
{
  if (currLevel==0)
	{
    ipcConvertCartesianToHS(xSum/count,ySum/count,avgHSV.hue,avgHSV.sat);
		avgHSV.val=valSum/count;
	}
  hsv=avgHSV;
}


inline int ipcTrafficSignLinkControlXY::compareFeatures(const ipcHSV& hsvCE1, const ipcHSV& hsvCE2, const ipcHSV& hsvSubCE)
{
  return compareColors(hsvSubCE.hue,hsvSubCE.sat,hsvSubCE.val,
                       hsvCE1.hue,hsvCE1.sat,hsvCE1.val,
                       hsvCE2.hue,hsvCE2.sat,hsvCE2.val);
}

#endif
