#include <iostream>
#include <string>
#include <stdlib.h>
#include "quadrangle.h"
using namespace std;


Quadrangle::Quadrangle(int id)
{
	maxNumberVerts = 4;
	numberVerts = 0;
        this->id=id;
}


  bool Quadrangle::isInside( int x, int y)
  {
    // Check weather the quadrangle has four corners.
    if( isComplete() )
    {
      unsigned int i, j; 
      bool c = false;
      for(i = 0, j = maxNumberVerts-1; i < maxNumberVerts; j = i++ )
      {
	if( ((yCoords[i] > y) != (yCoords[j]>y) ) && (x < (xCoords[j]-xCoords[i]) * (y - yCoords[i]) / (yCoords[j] - yCoords[i]) + xCoords[i]) )
	  c = !c;
      }
      return c;
    }
    return false;
  }
  
  void Quadrangle::addPoint( int x, int y)
  {
    if(!isComplete() )
    {
      xCoords.push_back(x);
      yCoords.push_back(y);
      numberVerts++;
    }
  }
  
  bool Quadrangle::isComplete()
  {
    return (xCoords.size() >= maxNumberVerts );

  }

  int Quadrangle::getSize() {
  return xCoords.size();
  }		

  


