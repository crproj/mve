#include <iostream>
#include <string>
#include <stdlib.h>
#include "quadrangle.h"
using namespace std;


Quadrangle::Quadrangle(int id) {
	maxNumberVerts = 4;
	numberVerts = 0;
        this->id=id;
}


Quadrangle::Quadrangle() {
	maxNumberVerts = 4;
	numberVerts = 0;
        this->id=-1;
}


bool Quadrangle::isInside( float x, float y, float width, float height) {
	if (((xCoords[1]*width - xCoords[0]*width) * (y - yCoords[0]*height) - (x - xCoords[0]*width) * (yCoords[1]*height - yCoords[0]*height)) <= 0) {
	if (((xCoords[2]*width - xCoords[1]*width) * (y - yCoords[1]*height) - (x - xCoords[1]*width) * (yCoords[2]*height - yCoords[1]*height)) <= 0) {
	if (((xCoords[3]*width - xCoords[2]*width) * (y - yCoords[2]*height) - (x - xCoords[2]*width) * (yCoords[3]*height - yCoords[2]*height)) <= 0) {
	if (((xCoords[0]*width - xCoords[3]*width) * (y - yCoords[3]*height) - (x - xCoords[3]*width) * (yCoords[0]*height - yCoords[3]*height)) <= 0) {
	return true;}}}}

	if (((xCoords[1]*width - xCoords[0]*width) * (y - yCoords[0]*height) - (x - xCoords[0]*width) * (yCoords[1]*height - yCoords[0]*height)) >= 0) {
	if (((xCoords[2]*width - xCoords[1]*width) * (y - yCoords[1]*height) - (x - xCoords[1]*width) * (yCoords[2]*height - yCoords[1]*height)) >= 0) {
	if (((xCoords[3]*width - xCoords[2]*width) * (y - yCoords[2]*height) - (x - xCoords[2]*width) * (yCoords[3]*height - yCoords[2]*height)) >= 0) {
	if (((xCoords[0]*width - xCoords[3]*width) * (y - yCoords[3]*height) - (x - xCoords[3]*width) * (yCoords[0]*height - yCoords[3]*height)) >= 0) {
	return true;}}}}

return false;
}
  
void Quadrangle::addPoint( float x, float y) {
	if(!isComplete() ) {
		xCoords.push_back(x);
      		yCoords.push_back(y);
      		numberVerts++;
    	}
}
  
bool Quadrangle::isComplete() {
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
