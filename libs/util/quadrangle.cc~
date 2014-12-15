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


  bool Quadrangle::isInside( float x, float y, float width, float height)
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
	if (((xCoords[1]*width - xCoords[0]*width) * (y - yCoords[0]*height) - (x - xCoords[0]*width) * (yCoords[1]*height - yCoords[0]*height)) <= 0) {
	if (((xCoords[2]*width - xCoords[1]*width) * (y - yCoords[1]*height) - (x - xCoords[1]*width) * (yCoords[2]*height - yCoords[1]*height)) <= 0) {
	if (((xCoords[3]*width - xCoords[2]*width) * (y - yCoords[2]*height) - (x - xCoords[2]*width) * (yCoords[3]*height - yCoords[2]*height)) <= 0) {
	if (((xCoords[0]*width - xCoords[3]*width) * (y - yCoords[3]*height) - (x - xCoords[3]*width) * (yCoords[0]*height - yCoords[3]*height)) <= 0) {
//std::cout << x << ","<< y << " liegt in " << xCoords[0]*width << "," << yCoords[0]*height << " " << xCoords[1]*width << "," << yCoords[1]*height << " " << xCoords[2]*width << "," << yCoords[2]*height << " " << xCoords[3]*width << "," << yCoords[3]*height << std::endl; 
	return true;
}
}
}
}

	if (((xCoords[1]*width - xCoords[0]*width) * (y - yCoords[0]*height) - (x - xCoords[0]*width) * (yCoords[1]*height - yCoords[0]*height)) >= 0) {
	if (((xCoords[2]*width - xCoords[1]*width) * (y - yCoords[1]*height) - (x - xCoords[1]*width) * (yCoords[2]*height - yCoords[1]*height)) >= 0) {
	if (((xCoords[3]*width - xCoords[2]*width) * (y - yCoords[2]*height) - (x - xCoords[2]*width) * (yCoords[3]*height - yCoords[2]*height)) >= 0) {
	if (((xCoords[0]*width - xCoords[3]*width) * (y - yCoords[3]*height) - (x - xCoords[3]*width) * (yCoords[0]*height - yCoords[3]*height)) >= 0) {
//std::cout << x << ","<< y << " liegt in " << xCoords[0]*width << "," << yCoords[0]*height << " " << xCoords[1]*width << "," << yCoords[1]*height << " " << xCoords[2]*width << "," << yCoords[2]*height << " " << xCoords[3]*width << "," << yCoords[3]*height << std::endl; 
	return true;
}
}
}
}
//std::cout << x << ","<< y << " liegt NICHT in " << xCoords[0]*width << "," << yCoords[0]*height << " " << xCoords[1]*width << "," << yCoords[1]*height << " " << xCoords[2]*width << "," << yCoords[2]*height << " " << xCoords[3]*width << "," << yCoords[3]*height << std::endl; 
return false;


  }
  
  void Quadrangle::addPoint( float x, float y)
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

  int Quadrangle::getID() const {
    return this->id;
  }

  


