/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Lutz Priese, Volker Rehrman, Patrick Sturm

*/


#ifndef _ipccodebase_h_
#define _ipccodebase_h_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0

  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <adverror.h>
#include <ipcislhierarchy.h>
#include <math.h>
#include <memory.h>
#include <map>
#include <list>
#include <iostream>

// Codeelement-Flags
enum ipcCEFlags
{
  ipcCEUsed          =   1,
  ipcCEUsed2         =   2,
  ipcCERoot          =   4,
  ipcCEVisited       =   8,
  ipcCEInQueue       =  16,
  ipcCEDisintegrated =  32,
  ipcCEUser1         =  64,
  ipcCEUser2         = 128
};


// Forward-Declarations
template <class ipcFeatureType> struct ipcCodeelement;

//! A subcodeelement contains a codeelement and a its relativ position.
template <class ipcFeatureType>
struct ipcSubCodeelement
{
  int pos;
  //short freeFields;
  ipcCodeelement<ipcFeatureType>* ce;
  ipcSubCodeelement<ipcFeatureType>* next;
};

template <class ipcFeatureType>
struct ipcCodeelementRef
{
  ipcIsland island;
  ipcCodeelement<ipcFeatureType>* ce;
};


/*! A codeelement... (TODO: better documentation) */
template <class ipcFeatureType>
struct ipcCodeelement
{
  unsigned char form,numOfSubCEs,flags;
  ipcFeatureType data;
#ifdef IPC_CSC_STORE_ISLAND
  ipcIsland island;
#endif
#ifdef IPC_CSC_STORE_RUNNING_NUMBER
  int runningNumber;
#endif
#ifdef IPC_CSC_STORE_BOUNDING_BOX
  short bbLeft,bbRight,bbTop,bbBottom;
#endif
  ipcCodeelement<ipcFeatureType>* root;
  ipcCodeelement<ipcFeatureType>* parents[2];
  ipcSubCodeelement<ipcFeatureType>* subCEs;
  ipcCodeelement<ipcFeatureType>* next;
};


/*! \brief A index entry stores a number of codeelements belonging to a comman island I.*/
template <class ipcFeatureType>
struct ipcIndexEntry
{
  //! Stores the number of codeelements of a the island I
  int numOfCEs;

  //! Points to the first codeelement of the island I.
  ipcCodeelement<ipcFeatureType>* firstCE;
  ipcCodeelement<ipcFeatureType>* lastCE;
};


// Forward-Declaration

/*! \brief The codeelement base stores the segmentation result of the color structure code. 

The class has several methods to access comfortably the codeelement graph. Further one can 
simply transform the codeelement graph into another representation, for example, a region
image. Everytime a programmer wants to access the codeelements directly he has to use the codeelement
base. 

\b Warning: Codeelements should not directly insert by the programmer.

The class \c ipcCodeelementBase is a template class that expect one template argument: \c ipcFeatureType.
\c ipcFeatureType describes the structure of the data that a codeelement is able to store. \c ipcFeatureType
can be every type that allows a copy operation:
\verbatim
ipcFeatureType a,b;
a=b; // <--- Copy operation
\endverbatim
@author Patrick Sturm
*/

template <class ipcFeatureType>
struct ipcCSCSegment
{
  ipcIsland island;
  ipcCodeelement<ipcFeatureType>* ce;
  ipcCSCSegment* next;
};


template <class ipcFeatureType>
class ipcCodeelementBase
{
private:
  const ipcIslandHierarchy* hierarchy;
  ipcIndexEntry<ipcFeatureType>* islandToCEs;
  ipcCodeelement<ipcFeatureType>* ces;
  ipcSubCodeelement<ipcFeatureType>* subCEs;
  int numOfCEs,numOfSubCEs,currentIsland;
  int maxNumOfCEs,maxNumOfSubCEs;
  double avgCEs;
  ipcCSCSegment<ipcFeatureType>* firstSegment;

  void drawRegionRecursive(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* ce, const ipcFeatureType& feature, int x, int y, int w, int h, ipcFeatureType* image);
  void drawLabelRecursive(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* ce, int label, int x, int y, int w, int h, int* image);

public:
  ipcCodeelementBase(const ipcIslandHierarchy& islandHierarchy, double avgCEsPerIsland = 2.0/*, double overheadPerCE = 4.0*/);
  virtual ~ipcCodeelementBase();

  inline double getAVGCapacityPerIsland() {return avgCEs; };

  inline void addNewSegment(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* ce);
  inline void removeSegment(ipcCodeelement<ipcFeatureType>* ce);
  inline ipcCSCSegment<ipcFeatureType>* getFirstSegment() const { return firstSegment; };
  void clearState(ipcCodeelement<ipcFeatureType>* ce);
  void reinit(double avgCEsPerIsland);
  void clearContent();
  inline void newIsland(const ipcIsland& island);
  inline void reopenIsland(const ipcIsland& island);
  inline void removeCodeelement(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* ce);
  inline ipcCodeelement<ipcFeatureType>* getCurrentCE() const;
  inline ipcSubCodeelement<ipcFeatureType>* getCurrentSubCEs() const;
  inline void storeCurrentCE(bool storeSubCEs = true);
  inline void storeCurrentSubCEs(int n);
  inline void removeSubCE(ipcCodeelement<ipcFeatureType>* ce, ipcCodeelement<ipcFeatureType>* subCE);
  inline ipcSubCodeelement<ipcFeatureType>* findSubCE(ipcCodeelement<ipcFeatureType>* parent, ipcCodeelement<ipcFeatureType>* subCE);
  inline ipcCodeelement<ipcFeatureType>* findRootCE(int x, int y, ipcIsland& rootIsland);

  ipcCodeelement<ipcFeatureType>* getCodeelements(const ipcIsland& island, int& count) const;
  void getCodeelements(const ipcIsland* islands, int numOfIslands, ipcCodeelement<ipcFeatureType>** ces, int* ceCounts) const;

  const ipcIslandHierarchy& getHierarchy() const;

  void drawRegionImage(int x, int y, int w, int h, ipcFeatureType* image, int minLevel=0/*, bool topDown = true*/);
  void drawRegion(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* ce, int x, int y, int w, int h, ipcFeatureType* image);
  void drawLabelImage(int x, int y, int w, int h, int* image, std::map<int,ipcCodeelementRef<ipcFeatureType> >& ceMap, int minLevel=0);
  void drawLabelImage(int x, int y, int w, int h, int* image, std::map<int,ipcFeatureType>& featureMap, int minLevel=0);
#ifdef IPC_DEBUG_DISINTEGRATION
  void drawDisintegratedRegions(int x, int y, int w, int h, int* image, int label, int minLevel);
#endif
  void drawRegion(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* ce, int label, int x, int y, int w, int h, int* image);
};


// Implementation of ipcCodeelementBase
template <class ipcFeatureType>
ipcCodeelementBase<ipcFeatureType>::ipcCodeelementBase(const ipcIslandHierarchy &islandHierarchy, double avgCEsPerIsland/*, double overheadPerCE*/)
{
  advAssert(avgCEsPerIsland>=1.0);

  firstSegment=NULL;
  hierarchy=&islandHierarchy;
  avgCEs=avgCEsPerIsland;
  maxNumOfCEs=(int)(avgCEsPerIsland*hierarchy->numberOfIslands());
  maxNumOfSubCEs=2*maxNumOfCEs;
  numOfCEs=0;
  numOfSubCEs=0;
  currentIsland=0;
  islandToCEs=new ipcIndexEntry<ipcFeatureType>[hierarchy->maxIslandKey()+1];
  ces=new ipcCodeelement<ipcFeatureType>[maxNumOfCEs];
  subCEs=new ipcSubCodeelement<ipcFeatureType>[maxNumOfSubCEs];
  advAssert(islandToCEs!=NULL && ces!=NULL && subCEs!=NULL);
}



template <class ipcFeatureType>
ipcCodeelementBase<ipcFeatureType>::~ipcCodeelementBase()
{
  clearContent();
  if (subCEs!=NULL) delete[] subCEs;
  if (ces!=NULL) delete[] ces;
  if (islandToCEs!=NULL) delete[] islandToCEs;
}


template <class ipcFeatureType>
void ipcCodeelementBase<ipcFeatureType>::reinit(double avgCEsPerIsland)
{
  advAssert(avgCEsPerIsland>=1.0);
  avgCEs=avgCEsPerIsland;
  maxNumOfCEs=(int)(avgCEsPerIsland*hierarchy->numberOfIslands());
  maxNumOfSubCEs=2*maxNumOfCEs;
  numOfCEs=0;
  numOfSubCEs=0;
  currentIsland=0;
  if (subCEs!=NULL) delete[] subCEs;
  if (ces!=NULL) delete[] ces;
  ces=new ipcCodeelement<ipcFeatureType>[maxNumOfCEs];
  subCEs=new ipcSubCodeelement<ipcFeatureType>[maxNumOfSubCEs];
  advAssert(ces!=NULL && subCEs!=NULL);

  ipcCSCSegment<ipcFeatureType>* delSeg;
  while (firstSegment!=NULL)
  {
    delSeg=firstSegment;
    firstSegment=firstSegment->next;
    delete delSeg;
  }
}


template <class ipcFeatureType>
void ipcCodeelementBase<ipcFeatureType>::clearContent()
{
  numOfCEs=0;
  numOfSubCEs=0;
  currentIsland=0;
  
  ipcCSCSegment<ipcFeatureType>* delSeg;
  while (firstSegment!=NULL)
  {
    delSeg=firstSegment;
    firstSegment=firstSegment->next;
    delete delSeg;
  }
}


template <class ipcFeatureType>
inline void ipcCodeelementBase<ipcFeatureType>::addNewSegment(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* ce)
{
  ipcCSCSegment<ipcFeatureType>* newSegment = new ipcCSCSegment<ipcFeatureType>;
  
  newSegment->island=island;
  newSegment->ce=ce;
  if (firstSegment==NULL)
  {
    firstSegment=newSegment;
    firstSegment->next=NULL;
  }
  else
  {
    if (island.level>=firstSegment->island.level)
    {
      newSegment->next=firstSegment;
      firstSegment=newSegment;
    }
    else
    { 
      ipcCSCSegment<ipcFeatureType>* tmp = firstSegment;
      while (tmp->next!=NULL && tmp->next->island.level>island.level)
        tmp=tmp->next;  
      newSegment->next=tmp->next;
      tmp->next=newSegment;
    }
  }
}


template <class ipcFeatureType>
inline void ipcCodeelementBase<ipcFeatureType>::removeSegment(ipcCodeelement<ipcFeatureType>* ce)
{
  ipcCSCSegment<ipcFeatureType>* delSeg;

  if (firstSegment!=NULL)
  {
    if (firstSegment->ce==ce) 
    {
      delSeg=firstSegment;
      firstSegment=firstSegment->next;
      delete delSeg;
    }
    else
    {
      ipcCSCSegment<ipcFeatureType>* tmp = firstSegment;
      while (tmp->next!=NULL && tmp->next->ce!=ce)
        tmp=tmp->next;
      if (tmp->next!=NULL) 
      {
        ipcCSCSegment<ipcFeatureType>* delSeg = tmp->next;
        tmp->next=tmp->next->next;
        delete delSeg;
      }
    }
  }
}


template <class ipcFeatureType>
inline void ipcCodeelementBase<ipcFeatureType>::newIsland(const ipcIsland& island)
{
  currentIsland=hierarchy->getIslandKey(island);
  islandToCEs[currentIsland].numOfCEs=0;
  islandToCEs[currentIsland].firstCE=NULL;
  islandToCEs[currentIsland].lastCE=NULL;
}


template <class ipcFeatureType>
inline ipcCodeelement<ipcFeatureType>* ipcCodeelementBase<ipcFeatureType>::getCurrentCE() const
{
  if (numOfCEs<maxNumOfCEs && numOfSubCEs<maxNumOfSubCEs)
  {
    ipcCodeelement<ipcFeatureType>* nextCE = &(ces[numOfCEs]);
    nextCE->numOfSubCEs=(maxNumOfSubCEs-numOfSubCEs>255) ? 255 : maxNumOfSubCEs-numOfSubCEs;
    nextCE->subCEs=&(subCEs[numOfSubCEs]);
    nextCE->next=NULL;

    return nextCE;
  }
  return NULL;
}


template <class ipcFeatureType>
inline void ipcCodeelementBase<ipcFeatureType>::reopenIsland(const ipcIsland& island)
{
  currentIsland=hierarchy->getIslandKey(island);
}


template <class ipcFeatureType>
inline void ipcCodeelementBase<ipcFeatureType>::storeCurrentCE(bool storeSubCEs)
{
  ipcCodeelement<ipcFeatureType>* currentCE = &(ces[numOfCEs]);

  advAssert(currentIsland>=0);
  advAssert(numOfCEs<maxNumOfCEs);
  if (islandToCEs[currentIsland].firstCE==NULL)
  {
    islandToCEs[currentIsland].firstCE=currentCE;
    islandToCEs[currentIsland].lastCE=currentCE;
  }
  else
  {
    islandToCEs[currentIsland].lastCE->next=currentCE;
    islandToCEs[currentIsland].lastCE=currentCE;
  }
  currentCE->next=NULL;
#ifdef IPC_CSC_STORE_RUNNING_NUMBER
  currentCE->runningNumber=numOfCEs;
#endif
  islandToCEs[currentIsland].numOfCEs++;
  numOfCEs++;

  if (storeSubCEs)
  {
    int n=currentCE->numOfSubCEs;
    advAssert(numOfSubCEs+n<=maxNumOfSubCEs);
    for (int i=1; i<n; i++)
      currentCE->subCEs[i-1].next=&(currentCE->subCEs[i]);
    currentCE->subCEs[n-1].next=NULL;
    numOfSubCEs+=n;
  }
}


template <class ipcFeatureType>
inline ipcSubCodeelement<ipcFeatureType>* ipcCodeelementBase<ipcFeatureType>::getCurrentSubCEs() const
{
  return &(subCEs[numOfSubCEs]);
}


template <class ipcFeatureType>
inline void ipcCodeelementBase<ipcFeatureType>::storeCurrentSubCEs(int n)
{
  advAssert(numOfSubCEs+n<=maxNumOfSubCEs);
  numOfSubCEs+=n;
}

template <class ipcFeatureType>
inline void ipcCodeelementBase<ipcFeatureType>::removeSubCE(ipcCodeelement<ipcFeatureType>* ce, ipcCodeelement<ipcFeatureType>* subCE)
{
  ipcSubCodeelement<ipcFeatureType>* current = ce->subCEs;

  if (current->ce==subCE)
  {
    ce->subCEs=ce->subCEs->next;
    ce->numOfSubCEs--;
    if (subCE->parents[0]==ce) subCE->parents[0]=NULL;
    else if (subCE->parents[1]==ce) subCE->parents[1]=NULL;
  }
  else 
  {
    while (current->next!=NULL && current->next->ce!=subCE)
      current=current->next;
    if (current->next!=NULL) 
    {
      current->next=current->next->next;
      ce->numOfSubCEs--;
      if (subCE->parents[0]==ce) subCE->parents[0]=NULL;
      else if (subCE->parents[1]==ce) subCE->parents[1]=NULL;
    }
  }
}


template <class ipcFeatureType>
inline void ipcCodeelementBase<ipcFeatureType>::removeCodeelement(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* ce)
{
  int islandKey = hierarchy->getIslandKey(island);
  ipcCodeelement<ipcFeatureType>* searchCE = islandToCEs[islandKey].firstCE;

  if (ce==searchCE)
  {
    islandToCEs[islandKey].firstCE=searchCE->next;
	if (islandToCEs[islandKey].firstCE==NULL) 
	  islandToCEs[islandKey].lastCE=NULL;
	islandToCEs[islandKey].numOfCEs--;
  }
  else
  {
    while (searchCE->next!=ce)
    {
	    searchCE=searchCE->next;
	    advAssert(searchCE!=NULL);
    }
	searchCE->next=ce->next;
	ce->next=NULL;
	if (ce==islandToCEs[islandKey].lastCE) 
	  islandToCEs[islandKey].lastCE=searchCE;
	islandToCEs[islandKey].numOfCEs--;
  }
}


template <class ipcFeatureType>
inline ipcSubCodeelement<ipcFeatureType>* ipcCodeelementBase<ipcFeatureType>::findSubCE(ipcCodeelement<ipcFeatureType>* parent, ipcCodeelement<ipcFeatureType>* subCE)
{
  ipcSubCodeelement<ipcFeatureType>* current = parent->subCEs;

  while (current!=NULL)
  {
    if (current->ce==subCE) return current;
    current=current->next;
  }
  return NULL;
}


template <class ipcFeatureType>
inline ipcCodeelement<ipcFeatureType>* ipcCodeelementBase<ipcFeatureType>::findRootCE(int x, int y, ipcIsland& rootIsland)
{
  ipcIsland parentIslands[2];
  int subPos[2];
  int numOfParents = hierarchy->getParentIslands(x,y,subPos,parentIslands);
  ipcCodeelement<ipcFeatureType>* ce;
  int count,pos;
  
  for (int i=0; i<numOfParents; i++)
  {
    ce=getCodeelements(parentIslands[i],count);
    pos=1<<subPos[i];
    while (ce!=NULL)
    {
      if (ce->form & pos)
      {
        rootIsland=parentIslands[i];
        while (ce->parents[0] || ce->parents[1])
        {
          ipcSubCodeelement<ipcFeatureType>* subCE;
          
          if (ce->parents[0])
          {
            subCE=findSubCE(ce->parents[0],ce);
            advAssert(subCE!=NULL);
            hierarchy->getParentIsland(rootIsland,subCE->pos,rootIsland);
            ce=ce->parents[0];
          }
          else
          {
            subCE=findSubCE(ce->parents[1],ce);
            advAssert(subCE!=NULL);
            hierarchy->getParentIsland(rootIsland,subCE->pos,rootIsland);
            ce=ce->parents[1];
          }
        }
        return ce;
      }
      ce=ce->next;
    }
  }
  return NULL;
}


template <class ipcFeatureType>
void ipcCodeelementBase<ipcFeatureType>::getCodeelements(const ipcIsland* islands, int numOfIslands, ipcCodeelement<ipcFeatureType>** ces, int* ceCounts) const
{
  for (int i=0; i<numOfIslands; i++)
  {
    int islandKey = hierarchy->getIslandKey(islands[i]);

    if (islandKey>=0)
    {
      ceCounts[i]=islandToCEs[islandKey].numOfCEs;
      ces[i]=islandToCEs[islandKey].firstCE;
    }
    else
    {
      ceCounts[i]=0;
      ces[i]=NULL;
    }
  }
}


template <class ipcFeatureType>
ipcCodeelement<ipcFeatureType>* ipcCodeelementBase<ipcFeatureType>::getCodeelements(const ipcIsland& island, int& count) const
{
  int islandKey = hierarchy->getIslandKey(island);

  if (islandKey>=0)
  {
    count=islandToCEs[islandKey].numOfCEs;
    return islandToCEs[islandKey].firstCE;
  }
  count=0;
  return NULL;
}


template <class ipcFeatureType>
const ipcIslandHierarchy& ipcCodeelementBase<ipcFeatureType>::getHierarchy() const
{
  return *hierarchy;
}


template <class ipcFeatureType>
void ipcCodeelementBase<ipcFeatureType>::clearState(ipcCodeelement<ipcFeatureType>* ce)
{
  if (ce->flags & ipcCEVisited)
  {
    ce->flags&=~ipcCEVisited;
    ipcSubCodeelement<ipcFeatureType>* subCE = ce->subCEs;
    while (subCE!=NULL)
    {
      clearState(subCE->ce);
      subCE=subCE->next;
    }
  }
}


template <class ipcFeatureType>
void ipcCodeelementBase<ipcFeatureType>::drawRegionRecursive(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* ce, const ipcFeatureType& feature, int x, int y, int w, int h, ipcFeatureType* image)
{
  ce->flags|=ipcCEVisited;

  if (island.level>0)
  {
    ipcIsland subIslands[7];
    ipcSubCodeelement<ipcFeatureType>* subCE;

    hierarchy->getSubIslands(island,subIslands);
    subCE=ce->subCEs;
    while (subCE!=NULL)
    {
      if ((subCE->ce->flags & ipcCEVisited)==0)
        drawRegionRecursive(subIslands[subCE->pos],subCE->ce,feature,x,y,w,h,image);
      subCE=subCE->next;
    }
  }
  else
  {
    int xcoord[7],ycoord[7];

    hierarchy->getSubPixels(island,xcoord,ycoord);
    for (int i=0; i<7; i++)
      if ((ce->form & (1<<i)) &&
               xcoord[i]>=x && xcoord[i]<x+w &&
               ycoord[i]>=y && ycoord[i]<y+h)
        image[xcoord[i]+w*ycoord[i]]=feature;
  }
}


template <class ipcFeatureType>
void ipcCodeelementBase<ipcFeatureType>::drawLabelRecursive(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* ce, int label, int x, int y, int w, int h, int* image)
{
  ce->flags|=ipcCEVisited;

  if (island.level>0)
  {
    ipcIsland subIslands[7];
    ipcSubCodeelement<ipcFeatureType>* subCE;

    hierarchy->getSubIslands(island,subIslands);
    subCE=ce->subCEs;
    while (subCE!=NULL)
    {
      if ((subCE->ce->flags & ipcCEVisited)==0)
        drawLabelRecursive(subIslands[subCE->pos],subCE->ce,label,x,y,w,h,image);
      subCE=subCE->next;
    }
  }
  else
  {
    int xcoord[7],ycoord[7];

    hierarchy->getSubPixels(island,xcoord,ycoord);
    for (int i=0; i<7; i++)
      if ((ce->form & (1<<i)) &&
               xcoord[i]>=x && xcoord[i]<x+w &&
               ycoord[i]>=y && ycoord[i]<y+h)
        image[xcoord[i]+w*ycoord[i]]=label;
  }
}


template <class ipcFeatureType>
void ipcCodeelementBase<ipcFeatureType>::drawRegionImage(int x, int y, int w, int h, ipcFeatureType* image, int minLevel/*, bool topDown*/)
{
  if (image!=NULL)
  {
    ipcCSCSegment<ipcFeatureType>* currSegment = firstSegment;

    //memset(image,0,sizeof(int)*w*h);
    int maxLevel=hierarchy->numberOfLevels();

    while (currSegment!=NULL)
    {
      if (minLevel<=currSegment->island.level && currSegment->island.level<=maxLevel)
      {
        if (currSegment->ce->flags & ipcCERoot)
        {
          drawRegionRecursive(currSegment->island,currSegment->ce,currSegment->ce->data,x,y,w,h,image);
          clearState(currSegment->ce);
        }
        else
          currSegment=currSegment;
      }
      currSegment=currSegment->next;
    }
  }
/*
  if (image!=NULL)
  {
    ipcCodeelement<ipcFeatureType>* current;
    int count;
    int maxLevel=hierarchy->numberOfLevels();
    
    ipcTopDownIslandIterator* islIterator = hierarchy->createIteratorTD();
    memset(image,0,sizeof(ipcFeatureType)*w*h);
    if (islIterator->begin())
    {
      int currentLevel = islIterator->currentIsland().level;
      do
      {
        if (currentLevel<=maxLevel)
          do
          { 
            const ipcIsland& currentIsland = islIterator->currentIsland();
            current=getCodeelements(currentIsland,count);
            while (current!=NULL)
            {
              if (current->flags & ipcCERoot)
              {
                drawRegionRecursive(currentIsland,current,current->data,x,y,w,h,image);
                clearState(current);
              }
              current=current->next;
            }
          } while (islIterator->nextIsland());
          currentLevel = islIterator->currentIsland().level;
      } while (islIterator->nextLevel() && currentLevel>=minLevel);
    }
    delete islIterator;
  }*/
}


template <class ipcFeatureType>
void ipcCodeelementBase<ipcFeatureType>::drawRegion(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* ce, int x, int y, int w, int h, ipcFeatureType* image)
{
  if (image!=NULL && ce!=NULL)
  {
    drawRegionRecursive(island,ce,ce->data,x,y,w,h,image);
    clearState(ce);
  }
}

template <class ipcFeatureType>
void ipcCodeelementBase<ipcFeatureType>::drawRegion(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* ce, int label, int x, int y, int w, int h, int* image)
{
  if (image!=NULL && ce!=NULL)
  {
    drawLabelRecursive(island,ce,label,x,y,w,h,image);
    clearState(ce);
  }
}


#ifdef IPC_DEBUG_DISINTEGRATION
template <class ipcFeatureType>
void ipcCodeelementBase<ipcFeatureType>::drawDisintegratedRegions(int x, int y, int w, int h, int* image, int label, int minLevel)
{
  if (image!=NULL)
  {
    ipcCSCSegment<ipcFeatureType>* currSegment = firstSegment;

    //memset(image,0,sizeof(int)*w*h);
    int maxLevel=hierarchy->numberOfLevels();

    while (currSegment!=NULL)
    {
      if (minLevel<=currSegment->island.level && currSegment->island.level<=maxLevel)
      {
        if (currSegment->ce->flags & ipcCEDisintegrated)
        {
          drawLabelRecursive(currSegment->ce,currSegment->island,label,x,y,w,h,image);
          clearState(currSegment->ce);
        }
      }
      currSegment=currSegment->next;
    }
  }
  
  /*  if (image!=NULL)
  {
    ipcTopDownIslandIterator* islIterator = hierarchy->createIteratorTD();
    ipcCodeelement<ipcFeatureType>* current;
    int count;

    //memset(image,0,sizeof(int)*w*h);
    int maxLevel=hierarchy->numberOfLevels();
    if (islIterator->begin())
    {
      int currentLevel = islIterator->currentIsland().level;
      do
      {
        if (currentLevel<=maxLevel)
          do
          {
            const ipcIsland& currentIsland = islIterator->currentIsland();
            current=getCodeelements(currentIsland,count);
            while (current!=NULL)
            {
              if (current->flags & ipcCEDisintegrated)
              {
                drawLabelRecursive(currentIsland,current,label,x,y,w,h,image);
                clearState(current);
              }
              current=current->next;
            }
          } while (islIterator->nextIsland());
        currentLevel = islIterator->currentIsland().level;
      } while (islIterator->nextLevel() && currentLevel>=minLevel);
    }
    delete islIterator;
  }*/
}
#endif


template <class ipcFeatureType>
void ipcCodeelementBase<ipcFeatureType>::drawLabelImage(int x, int y, int w, int h, int* image, std::map<int,ipcCodeelementRef<ipcFeatureType> >& ceMap, int minLevel)
{
  if (image!=NULL)
  {
    ipcCSCSegment<ipcFeatureType>* currSegment;
    int nextLabel=1;
    ipcCodeelementRef<ipcFeatureType> ceRef;

    memset(image,0,sizeof(int)*w*h);
    ceMap.clear();
    int maxLevel=hierarchy->numberOfLevels();

    currSegment=firstSegment;
    while (currSegment!=NULL)
    {
      if (minLevel<=currSegment->island.level && currSegment->island.level<=maxLevel && (currSegment->ce->flags & ipcCERoot))
      {
        drawLabelRecursive(currSegment->island,currSegment->ce,nextLabel,x,y,w,h,image);
        ceRef.island=currSegment->island;
        ceRef.ce=currSegment->ce;
        ceMap[nextLabel]=ceRef;
        nextLabel++;
        clearState(currSegment->ce);
      }
      currSegment=currSegment->next;
    }
  }
/*  if (image!=NULL)
  {
    ipcTopDownIslandIterator* islIterator = hierarchy->createIteratorTD();
    ipcCodeelement<ipcFeatureType>* current;
    int count;
    int nextLabel=1;
    ipcCodeelementRef<ipcFeatureType> ceRef;

    memset(image,0,sizeof(int)*w*h);
    ceMap.clear();
    int maxLevel=hierarchy->numberOfLevels();
    if (islIterator->begin())
    {
      int currentLevel = islIterator->currentIsland().level;
      do
      {
        if (currentLevel<=maxLevel)
          do
          {
            const ipcIsland& currentIsland = islIterator->currentIsland();
            current=getCodeelements(currentIsland,count);
            while (current!=NULL)
            {
              if (current->flags & ipcCERoot)
              {
                drawLabelRecursive(currentIsland,current,nextLabel,x,y,w,h,image);
                ceRef.island=currentIsland;
                ceRef.ce=current;
                ceMap[nextLabel]=ceRef;
                nextLabel++;
                clearState(current);
              }
              current=current->next;
            }
          } while (islIterator->nextIsland());
        currentLevel = islIterator->currentIsland().level;
      } while (islIterator->nextLevel() && currentLevel>=minLevel);
    }
    delete islIterator;
  }*/
}


template <class ipcFeatureType>
void ipcCodeelementBase<ipcFeatureType>::drawLabelImage(int x, int y, int w, int h, int* image, std::map<int,ipcFeatureType>& featureMap, int minLevel)
{
  std::map<int,ipcCodeelementRef<ipcFeatureType> > ceMap;

  featureMap.clear();
  drawLabelImage(x,y,w,h,image,ceMap,minLevel);
  typename std::map<int,ipcCodeelementRef<ipcFeatureType> >::iterator end = ceMap.end();

  for (typename std::map<int,ipcCodeelementRef<ipcFeatureType> >::iterator current = ceMap.begin(); current!=end; current++)
    featureMap[(*current).first]=(*current).second.ce->data;
}


#ifdef IPC_CODEBASE_OUTPUT
template <class ipcFeatureType>
std::ostream& operator << (std::ostream& out, const ipcCodeelement<ipcFeatureType>& ce)
{
#ifdef IPC_CSC_STORE_RUNNING_NUMBER
  out << "[NR:" << hex << (int)ce.runningNumber << ",Form:" << (int)ce.form << dec << ",Data:" << ce.data << ",#SubCEs:" << (int)ce.numOfSubCEs << "]";
#else
  out << "[Form:" << hex << (int)ce.form << dec << ",Data:" << ce.data << ",#SubCEs:" << (int)ce.numOfSubCEs << "]";
#endif
  return out;
}


template <class ipcFeatureType>
std::ostream& operator << (std::ostream& out, ipcCodeelementBase<ipcFeatureType>& ceBase)
{
  ipcBottomUpIslandIterator islIterator(ceBase.getHierarchy());

  if (islIterator.begin())
    do
    {
      do
      {
        ipcCodeelement<ipcFeatureType>* ce;
        int count;

        out << "Island = " << islIterator.currentIsland() << endl;
        ce=ceBase.getCodeelements(islIterator.currentIsland(),count);
        while (ce!=NULL)
        {
          out << "    CE = " << (*ce) << endl;
          ce=ce->next;
        }
      } while (islIterator.nextIsland());
    } while (islIterator.nextLevel());
  return out;
}
#endif

#endif
