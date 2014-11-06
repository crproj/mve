/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Lutz Priese, Volker Rehrman, Patrick Sturm

*/


#ifndef _ipcclassichsvcolsim_h_
#define _ipcclassichsvcolsim_h_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0

  Copyright 2002,Patrick Sturm
************************************************/

// Include-Files
#include <ipccolor.h>
#include <math.h>
#include <stdlib.h>

// Class: ipcClassicHSVSimilarityFunction
class ipcClassicHSVSimilarityFunction
{
private:
  int HUEDISTANCE[16][16];
  int VALDISTANCE[16][16];
  int SATDISTANCE[16][16];

public:
  ipcClassicHSVSimilarityFunction();

  inline bool colorSimilar(int h1,int s1,int v1,int h2,int s2,int v2) const;
  inline int compareColors(int hue,int val,int sat,int hue1,int sat1,int val1,
                           int hue2,int sat2,int val2) const;
};

#include <stdio.h>
// Implementation of ipcHSVSimilarity-Function
inline bool ipcClassicHSVSimilarityFunction::colorSimilar(int h1,int s1,int v1,int h2,int s2,int v2) const
{
  int deltaHue,a,b;
  int hue_dist,vmax,vmin,smax,smin;

  // Let us throw some bits away
  s1=(s1>>4); 
  s2=(s2>>4);
	v1=(v1>>3);
	v2=(v2>>3);
  deltaHue=h2-h1;
  if (v1>=v2) 
  { 
    vmax = v1; 
    vmin = v2; 
  }
  else            
  { 
    vmax=v2; 
    vmin=v1; 
  }
  if (s1>=s2) 
  { 
    smax=s1; 
    smin=s2; 
  }
  else            
  { 
    smax=s2; 
    smin=s1; 
  }
  a = vmax>>1;
  b = smin;
  if ((vmax - vmin) > (VALDISTANCE[b][a])) return false;
  if ((smax - smin) > (SATDISTANCE[b][a])) return false;
  hue_dist = HUEDISTANCE[b][a];
  deltaHue=abs(h2-h1);
	if ((deltaHue>hue_dist) && (deltaHue<360-hue_dist)) return false;
	
  return true;
}


inline int ipcClassicHSVSimilarityFunction::compareColors(int hue,int val,int sat,
                    int hue1,int sat1,int val1,int hue2,int sat2,int val2) const
{
  int deltaS1,deltaS2,deltaH1,deltaH2,deltaV1,deltaV2;

  sat1=sat1>>4;
  sat2=sat2>>4;
  val1=val1>>3;
  val2=val2>>3;
  deltaS1=abs(sat1-sat);
  deltaS2=abs(sat2-sat);
  deltaV1=abs(val1-val);
  deltaV2=abs(val2-val);
  deltaH1=abs(hue1-hue);
  deltaH2=abs(hue2-hue);
	if (deltaH1>180) deltaH1=360-deltaH1;
	if (deltaH2>180) deltaH2=360-deltaH2;
	
  if ((val<8) || (sat<6))
  {
    if (deltaV1>deltaV2) return 2;
		else if (deltaV1<deltaV2) return 1;
		else 
		{
		  if (deltaS1>deltaS2) return 2;
			else if (deltaS1<deltaS2) return 1;
			else
			{
			  if (deltaH1>deltaH2) return 2;
				else return 1;
			}
		}	  
  }
	else
	{
    if (deltaH1>deltaH2) return 2;
		else if (deltaH1<deltaH2) return 1;
		else 
		{
		  if (deltaV1>deltaV2) return 2;
			else if (deltaV1<deltaV2) return 1;
			else
			{
			  if (deltaS1>deltaS2) return 2;
				else return 1;
			}
		}	  
	}
}

#endif
