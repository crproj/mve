/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Lutz Priese, Volker Rehrman, Patrick Sturm

*/


#ifndef _ipcislhierarchy_h_
#define _ipcislhierarchy_h_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0
  
  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <adverror.h>
#include <iostream>

// Types
typedef int ipcNeighborTable[7][7];
typedef int ipcCommonIslTable[7][7];
typedef int ipcConnectedWithTable[7][7];

//! The structure codes the position of an island.
/*! The position of an island consists of a hierarchy level and a coordinate (x/y) */
struct ipcIsland
{
  int level,x,y;
};


//! The class represents the logical hexagonal island hierarchy.
class ipcIslandHierarchy
{
private:
  int  size,levelCount;
  int* numOfIslands;
  //int* levelWidth;
	int* evenWidth;
  int minPos[128];
  int** levelDeltaX;
  int** levelDeltaY;

  //int* correctionNum;

public:
  static int numberOfLevels(int w, int h);

  //! The constructor creates the smallest island hierarchy that covers entirely a raster with (w x h) pixels.
  ipcIslandHierarchy(int w = 0, int h = 0);

  virtual ~ipcIslandHierarchy();

  //! The function computes all subislands of an island \c I
  /*! \param island parent island \c I.
      \param subIslands Array with 7 fields. The array contains all subislands of the
             parent island \c I after execution of the method */
  void getSubIslands(const ipcIsland& island, ipcIsland* subIslands) const;

  void getSubIsland(const ipcIsland& island, int pos, ipcIsland& subIsland) const;

  void getMinCoord(const ipcIsland& island, unsigned char form, int& x, int& y, int& pos) const;

  //! The method computes a certain parent island of a given subisland depend on its relative position code.
  /*! \param island subisland for that a parent island should be computed
      \param relPos is the relative position code of the subisland within the parent island*/
  void getParentIsland(const ipcIsland& island, int relPos, ipcIsland& parentIsland) const;

  int getParentIslands(int x, int y, int subPos[2], ipcIsland parents[2]) const;

  bool gotoNeighborPixel(int dir, ipcIsland& island, int& pos) const;

  //! The function computes all subpixels of a level 0 island I
  /*! \param island parent island \c I
      \param xcoord Array with 7 fields for the x-coordinates of all subpixel of \c I.
      \param ycoord Array with 7 fields for the y-coordinates of all subpixel of \c I.*/
  void getSubPixels(const ipcIsland& island, int* xcoord, int* ycoord) const;

  const ipcCommonIslTable& getCommonIslandTable() const;
  const ipcNeighborTable& getNeighborTable() const;
  const ipcConnectedWithTable& getConnectedWithTable() const;

  //! The method returns the largest possible island key of the hierarchy.
  /*! \result The largest possible island key in this island hierarchy. 
      The result of this method is not necessarily equivalent to the result of 
      the method numberOfIslands. Therefore it is possible that there exists some
      island keys between 0 and maxIslandKey() which could not be mapped to valid island
      of the hierarchy.*/
  int maxIslandKey() const;

  //! The method computes an unique id (island key) for each island.
  /*! \param island A island \c I for which the island key should be computed.
      \result The island key of \c I*/
  inline int getIslandKey(const ipcIsland& island) const
  {
    int islX = island.x >> (island.level+1);
    int islY = island.y >> (island.level+1);
	  int oddModifier = islY & 1;

	  if (island.level+2!=levelCount)
    	return (islY>=0 && islX>=0 &&
			            islX+oddModifier<evenWidth[island.level] &&
		                    islY<evenWidth[island.level]) ? 
						                 islX+islY*evenWidth[island.level]-(islY>>1)
								                     +numOfIslands[island.level]: -1;
  	return (islY>=0 && islX>=0 &&
			            islX+1<evenWidth[island.level]+oddModifier &&
		                    islY<evenWidth[island.level]) ? 
						                 islX+islY*evenWidth[island.level]-((islY+1)>>1)
								                     +numOfIslands[island.level]: -1;
	  /*int oddModifier = island.y & 1;
	  if (island.level+2!=levelCount)
    	return (island.y>=0 && island.x>=0 &&
			            island.x+oddModifier<evenWidth[island.level] &&
		                    island.y<evenWidth[island.level]) ? 
						                 island.x+island.y*evenWidth[island.level]-(island.y>>1)
								                     +numOfIslands[island.level]: -1;
  	return (island.y>=0 && island.x>=0 &&
			            island.x+1<evenWidth[island.level]+oddModifier &&
		                    island.y<evenWidth[island.level]) ? 
						                 island.x+island.y*evenWidth[island.level]-((island.y+1)>>1)
								                     +numOfIslands[island.level]: -1;*/
  };

  /*! \result The number of islands in the given level. */
  int numberOfIslands(int level) const;

  /*! \result The number of all islands */
  int numberOfIslands() const;

  /*! \result The number of levels of this island hierarchy. */
  int numberOfLevels() const;

  //! Creates an bottom up iterator for this island hierarchy.
  class ipcBottomUpIslandIterator* createIteratorBU() const;

  //! Creates a top down iterator for this island hierarchy.
  class ipcTopDownIslandIterator* createIteratorTD() const;

  //! \result The width and height of the base raster
  int getSize() const;
  
friend class ipcBottomUpIslandIterator;
friend class ipcTopDownIslandIterator;
};


//! The class describes an interface for an abstract island iterator.
/*! An island iterator enumerates the island of an island hierarchy in a specific order.
    There should be two main iterators for one hierarchy. The first iterator class enumerates
    an island hierarchy bottom up and the second one enumerates an island hierachy top down.
*/
class ipcAbstractIslandIterator
{
public:
  //! The method initializes the island iterator.
  virtual bool begin() = 0;

  //! The iterator jumps to the next island of the current level.
  /*! The method delivers false if all islands of an level are enumerated otherwise it
      returns false.*/
  virtual bool nextIsland() = 0;

  //! The iterator jumps to the first island of the next level. 
  /*! The method returns if all levels were visited, otherwise it returns true.*/
  virtual bool nextLevel() = 0;

  /*! \return the current island. */
  virtual const ipcIsland& currentIsland() = 0;
};


//! The class describes the behavior of an bottom up island iterator.
/*! It enumerate all islands of a given island hierachy level by level. It starts
    at level 0.*/
class ipcBottomUpIslandIterator
{
private:
  const ipcIslandHierarchy* hierarchy;
  ipcIsland currIsland;
  int levelWidth,firstLine;
  int width;
  const int* levelDeltaX;
  const int* levelDeltaY;

public:
  //! This constructor sets the island iterator to the first island of the given hierarchy.
  ipcBottomUpIslandIterator(const ipcIslandHierarchy& initHierarchy);

  //! The method initializes the island iterator.
  bool begin();

  /*! The method delivers false if all islands of an level are enumerated otherwise it
      returns false.*/
  bool nextIsland();

  //! The iterator jumps to the first island of the next level. 
  /*! The method returns if all levels were visited, otherwise it returns true.*/
  bool nextLevel();

  /*! \return the current island. */
  const ipcIsland& currentIsland() const { return currIsland; };

friend class ipcIslandHierarchy;
};


//! The class describes the behavior of an top down island iterator.
/*! It enumerate all islands of a given island hierachy level by level. It starts
    at the top most level.*/
class ipcTopDownIslandIterator
{
private:
  const ipcIslandHierarchy* hierarchy;
  ipcIsland currIsland;
  int levelWidth,firstLine;
  int width;
  const int* levelDeltaX;
  const int* levelDeltaY;

public:
  //! This constructor sets the island iterator to the top most island of the given hierarchy.
  ipcTopDownIslandIterator(const ipcIslandHierarchy& initHierarchy);

  //! The method initializes the island iterator.
  bool begin();

  /*! The method delivers false if all islands of an level are enumerated otherwise it
      returns false.*/
  bool nextIsland();

  //! The iterator jumps to the first island of the next level. 
  /*! The method returns if all levels were visited, otherwise it returns true.*/
  bool nextLevel();

  /*! \return the current island. */
  const ipcIsland& currentIsland() const { return currIsland; };

friend class ipcIslandHierarchy;
};

std::ostream& operator << (std::ostream& out, const ipcIsland& island);

#endif
