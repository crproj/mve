#include <iostream>
#include <string>
#include <stdlib.h>
#include "quadrangle.h"
using namespace std;


Quadrangle::Quadrangle(int id) {
	numberVerts = 0;
        this->id=id;
	this->complete = false;
}


Quadrangle::Quadrangle() {
	numberVerts = 0;
        this->id=-1;
	this->complete = false;
}


float Quadrangle::strahltest(float x, float y, float xb, float yb, float xc, float yc){
	float xtmp, ytmp;
	if(y == yb && y == yc)
		if(x >= xb && x <= xc || x >= xc && x <= xb)
			return 0;
				
		else
			return 1;
	if(yb > yc) {
		xtmp = xb;
		ytmp = yb;
		xb = xc;
		yb = yc;
		xc = xtmp;
		yc = ytmp;
	}

	if (y == yb && x == xb)
		return 0;

	if( y <= yb || y > yc)
		return 1;		



	float delta = (xb - x) * (yc - y) - (yb - y) * (xc - x);
		if(delta > 0)
			return -1;
		else if(delta < 0)
			return 1;
		else 
			return 0;
}

bool Quadrangle::isInside( float x, float y, float width, float height) {
	/*if (((xCoords[1]*width - xCoords[0]*width) * (y - yCoords[0]*height) - (x - xCoords[0]*width) * (yCoords[1]*height - yCoords[0]*height)) <= 0) {
	if (((xCoords[2]*width - xCoords[1]*width) * (y - yCoords[1]*height) - (x - xCoords[1]*width) * (yCoords[2]*height - yCoords[1]*height)) <= 0) {
	if (((xCoords[3]*width - xCoords[2]*width) * (y - yCoords[2]*height) - (x - xCoords[2]*width) * (yCoords[3]*height - yCoords[2]*height)) <= 0) {
	if (((xCoords[0]*width - xCoords[3]*width) * (y - yCoords[3]*height) - (x - xCoords[3]*width) * (yCoords[0]*height - yCoords[3]*height)) <= 0) {
	return true;}}}}

	if (((xCoords[1]*width - xCoords[0]*width) * (y - yCoords[0]*height) - (x - xCoords[0]*width) * (yCoords[1]*height - yCoords[0]*height)) >= 0) {
	if (((xCoords[2]*width - xCoords[1]*width) * (y - yCoords[1]*height) - (x - xCoords[1]*width) * (yCoords[2]*height - yCoords[1]*height)) >= 0) {
	if (((xCoords[3]*width - xCoords[2]*width) * (y - yCoords[2]*height) - (x - xCoords[2]*width) * (yCoords[3]*height - yCoords[2]*height)) >= 0) {
	if (((xCoords[0]*width - xCoords[3]*width) * (y - yCoords[3]*height) - (x - xCoords[3]*width) * (yCoords[0]*height - yCoords[3]*height)) >= 0) {
	return true;}}}}*/


	vector<float> xCopy = xCoords;
	xCopy.push_back(xCoords[0]);

	vector<float> yCopy = yCoords;
	yCopy.push_back(yCoords[0]);

	int t = -1;
	float result = 0;

	for(unsigned int i = 0; i < xCopy.size(); i++ )
	{	
		

		result = strahltest(x, y, xCopy[i] * width, yCopy[i] * height, xCopy[i+1] * width, yCopy[i+1] * height);
		t = t * result;
	}

	if(t < 0) 
		return false; 
	return true;



	/*
	bool result = true;

	for (unsigned int i = 0; i < this->getSize(); i++) {
	    if (result) {
		if (i == this->getSize()-1)
		    result = (((xCoords[0]*width - xCoords[i]*width) * (y - yCoords[i]*height) - (x - xCoords[i]*width) * (yCoords[0]*height - yCoords[i]*height)) <= 0);
		else
		    result = (((xCoords[i+1]*width - xCoords[i]*width) * (y - yCoords[i]*height) - (x - xCoords[i]*width) * (yCoords[i+1]*height - yCoords[i]*height)) <= 0);
	    }
	}

	if (result)
	    return true;

	result = true;

	for (unsigned int i = 0; i < this->getSize(); i++) {
	    if (result) {
		if (i == this->getSize()-1)
		    result = (((xCoords[0]*width - xCoords[i]*width) * (y - yCoords[i]*height) - (x - xCoords[i]*width) * (yCoords[0]*height - yCoords[i]*height)) >= 0);
		else
		    result = (((xCoords[i+1]*width - xCoords[i]*width) * (y - yCoords[i]*height) - (x - xCoords[i]*width) * (yCoords[i+1]*height - yCoords[i]*height)) >= 0);
	    }
	}

	if (result)
	    return true;

return false;*/
}
  
void Quadrangle::addPoint( float x, float y) {
	if(!isComplete() ) {
		xCoords.push_back(x);
      		yCoords.push_back(y);
      		numberVerts++;
    	}
}
  
bool Quadrangle::isComplete() {
	return complete;
}

unsigned int Quadrangle::getSize() {
	return xCoords.size();
}	

void Quadrangle::setID(int id) {
	this->id = id;
}

void Quadrangle::setComplete() {
	this->complete = true;
}

int Quadrangle::getID() {
	return this->id;
}
