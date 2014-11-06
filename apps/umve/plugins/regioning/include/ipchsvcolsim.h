/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Lutz Priese, Volker Rehrman, Patrick Sturm

*/


#ifndef _IPC_HSVCOLSIM_H_
#define _IPC_HSVCOLSIM_H_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0

  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <ipccolor.h>
#include <math.h>
#include <stdlib.h>

// Class: ipcHSVSimilarityFunction
class ipcHSVSimilarityFunction
{
private:
  int HSVDISTANCE[16][16][3];

public:
  ipcHSVSimilarityFunction();

  void setParameters(int h_sens, int s_sens, int v_sens);
  inline bool colorSimilar(int h1, int s1, int v1, int h2, int s2, int v2);
  inline int compareColors(int hue, int val, int sat, int hue1, int sat1, int val1, 
                           int hue2, int sat2, int val2);
};


// Implementation of ipcHSVSimilarity-Function
inline bool ipcHSVSimilarityFunction::colorSimilar(int h1, int s1, int v1, int h2, int s2, int v2)
{
  int deltaHue,a,b;
  int hue_dist,vmax,vmin,smax,smin;

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
  a = vmax>>4;
  b = smin>>4;
  if ((vmax - vmin) > (HSVDISTANCE[b][a][1])) return false;
  if ((smax - smin) > (HSVDISTANCE[b][a][0]<<3)) return false;
  hue_dist = HSVDISTANCE[b][a][2];
  deltaHue=abs(h2-h1);
	if ((deltaHue>hue_dist) && (deltaHue<360-hue_dist)) return false;
	
  return true;
}


inline int ipcHSVSimilarityFunction::compareColors(int hue, int val, int sat, 
                    int hue1, int sat1, int val1, int hue2, int sat2, int val2)
{
  int delta1,delta2;

  if ((val<70) || (sat<48))
  {
    delta1=abs(val-val1);
    delta2=abs(val-val2);

    delta1+=abs(sat-sat1);
    delta2+=abs(sat-sat2);

    if (delta1>delta2) return 2;
    if (delta1<delta2) return 1;

    delta1 = abs(hue - hue1);
    delta2 = abs(hue - hue2);

    if (delta1>180) delta1=360-delta1;
    if (delta2>180) delta2=360-delta2;

    if (delta1>delta2) return 2;
    return 1;
  }

  delta1 = abs(hue - hue1);// << 3;
  delta2 = abs(hue - hue2);// << 3;

  delta1+=abs(val-val1);
  delta2+=abs(val-val2);

  delta1+=abs(sat-sat1);
  delta2+=abs(sat-sat2);

  if (delta1>delta2) return 2;

  return 1;
}

#endif
