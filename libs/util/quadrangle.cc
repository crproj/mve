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

return false;
}
  
void Quadrangle::addPoint( float x, float y) {
	//if(!isComplete() ) {
		xCoords.push_back(x);
      		yCoords.push_back(y);
      		numberVerts++;
    	//}
}
  
bool Quadrangle::isComplete() {
	//return complete;
	return (getSize() > 3);
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
