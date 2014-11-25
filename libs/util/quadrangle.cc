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


Quadrangle::Quadrangle()
{
	maxNumberVerts = 4;
	numberVerts = 0;
        this->id=-1;
}


  bool Quadrangle::isInside( int x, int y)
  {
    // Check weather the quadrangle has four corners.
    /*if( isComplete() )
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
    return false;*/

	if (((xCoords[1] - xCoords[0]) * (y - yCoords[0]) - (x - xCoords[0]) * (yCoords[1] - yCoords[0])) <= 0) {
	if (((xCoords[2] - xCoords[1]) * (y - yCoords[1]) - (x - xCoords[1]) * (yCoords[2] - yCoords[1])) <= 0) {
	if (((xCoords[3] - xCoords[2]) * (y - yCoords[2]) - (x - xCoords[2]) * (yCoords[3] - yCoords[2])) <= 0) {
	if (((xCoords[0] - xCoords[3]) * (y - yCoords[3]) - (x - xCoords[3]) * (yCoords[0] - yCoords[3])) <= 0) {
	return true;
}
}
}
}

	if (((xCoords[1] - xCoords[0]) * (y - yCoords[0]) - (x - xCoords[0]) * (yCoords[1] - yCoords[0])) >= 0) {
	if (((xCoords[2] - xCoords[1]) * (y - yCoords[1]) - (x - xCoords[1]) * (yCoords[2] - yCoords[1])) >= 0) {
	if (((xCoords[3] - xCoords[2]) * (y - yCoords[2]) - (x - xCoords[2]) * (yCoords[3] - yCoords[2])) >= 0) {
	if (((xCoords[0] - xCoords[3]) * (y - yCoords[3]) - (x - xCoords[3]) * (yCoords[0] - yCoords[3])) >= 0) {
	return true;
}
}
}
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

  void Quadrangle::setID(int id) {
    this->id = id;
  }

  int Quadrangle::getID() {
    return this->id;
  }

  


