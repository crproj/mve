/* 

  This "SOFTWARE" is a free software.
  
  You are allowed to download, use, modify and redistribute this software.
  The software is provided "AS IS" without warranty of any kind.
    
  Copyright: University of Koblenz, Lutz Priese, Volker Rehrman, Patrick Sturm
      
*/


#ifndef _ipccscengine_h_
#define _ipccscengine_h_

/***********************************************
iMAge pROcessing cLAsses Version 1.0

  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <adverror.h>
#include <ipcislhierarchy.h>
#include <ipccodebase.h>
#include <advqueue.h>
#include <list>

// Exceptions
ADV_NEW_STD_EXCEPTION(ipcCSCException,"CSC failed...")
ADV_NEW_SUB_EXCEPTION(ipcCodeelementBaseOverrun,ipcCSCException,"Codeelement overrun...")


//! Symbolic names for different splitting algorithms
enum ipcSplittingType {ipcNoSplitting, ipcDirectSplitting, ipcDeferredSplitting/*, ipcDirectSplittingRecursive*/};

//! Symbolic names for different repair alhorithms
enum ipcRepairType {ipcNoRepair, ipcFastRepair, ipcPreciseRepair};

template <class ipcFeatureType>
struct ipcUpdateFeature
{
  int level;
  ipcCodeelement<ipcFeatureType> *ce;
};


template <class ipcFeatureType>
struct ipcSplittingPair
{
  ipcCodeelement<ipcFeatureType> *root1;
  ipcCodeelement<ipcFeatureType> *root2;
  ipcCodeelement<ipcFeatureType> *ce1,*ce2;
  ipcIsland island;
  int relPos1,relPos2;
};


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
class ipcCSCEngine
{
private:
  const ipcIslandHierarchy* hierarchy;
  ipcCodeelementBase<ipcFeatureType>* ceBase;
  ipcBottomUpIslandIterator* islandIterator;
  ipcLinkControl* linkControl;
  int roiX1,roiY1,roiX2,roiY2;
  ipcSplittingType splittingType;
  advQueue<ipcSplittingPair<ipcFeatureType> > splittingQueue;
  int maxQueue,disintegratedCEs;
  ipcSubCodeelement<ipcFeatureType>* ceQueue;
  ipcRepairType repairType;
  bool updateAfterSplitting;
  ipcUpdateFeature<ipcFeatureType>* updateQueue;
  int maxUpdateQueue;

  
  void coding(int w, int h, const ipcPixelType* image);
  void level0Linking();
  void levelNLinking();
  void updateFeature(int level, ipcCodeelement<ipcFeatureType>* ce);
  void deferredSplitting();
  void directSplitting();
  bool testConnectivityIf(ipcCodeelement<ipcFeatureType>* rootCE, ipcCodeelement<ipcFeatureType>* removedCE);
  bool testLevel1ConnectivityIf(ipcCodeelement<ipcFeatureType>* rootCE, ipcCodeelement<ipcFeatureType>* removedCE);
  void repair(ipcCodeelement<ipcFeatureType>* rootCE, ipcSubCodeelement<ipcFeatureType>* subCEList, int &numOfConnected, ipcSubCodeelement<ipcFeatureType>* &connectedList, unsigned char& connectedForm, int &numOfRest, ipcSubCodeelement<ipcFeatureType>* &restList);
  void level1Repair(ipcCodeelement<ipcFeatureType>* rootCE, ipcSubCodeelement<ipcFeatureType>* subCEList, int &numOfConnected, ipcSubCodeelement<ipcFeatureType>* &connectedList, unsigned char& connectedForm, int &numOfRest, ipcSubCodeelement<ipcFeatureType>* &restList);
  int repair(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* rootCE);
  void storeSegments();
#ifdef IPC_DEBUG_DISINTEGRATION
  bool testConnectivity(ipcCodeelement<ipcFeatureType>* rootCE);
  bool testLevel1Connectivity(ipcCodeelement<ipcFeatureType>* rootCE);
  void testConnectivity();
#endif

public:
  ipcCSCEngine(ipcCodeelementBase<ipcFeatureType>& newCEBase, ipcLinkControl* newLinkControl, ipcSplittingType newSplittingType = ipcDirectSplitting, ipcRepairType newRepairType = ipcPreciseRepair);
  virtual ~ipcCSCEngine();

  void changeCEBase(ipcCodeelementBase<ipcFeatureType>& newCEBase);
  void changeRepairType(ipcRepairType newRepairType) {repairType=newRepairType;};
  void setROI(int x, int y, int w, int h);
  void startSegmentation(int w, int h, const ipcPixelType* image);
  ipcLinkControl& getLinkControl() { return (*linkControl); };
  inline int getNumOfDisintegratedCEs() const { return disintegratedCEs; };
};


// Implementation
template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::ipcCSCEngine(ipcCodeelementBase<ipcFeatureType>& newCEBase, ipcLinkControl* newLinkControl, ipcSplittingType newSplittingType, ipcRepairType newRepairType): linkControl(newLinkControl), splittingQueue(2000,2000)
{
  advAssert(linkControl!=NULL);
  islandIterator=NULL;
  changeCEBase(newCEBase);
  splittingType=newSplittingType;
  maxQueue=2000;
  ceQueue=new ipcSubCodeelement<ipcFeatureType>[maxQueue];
  disintegratedCEs=0;
  repairType=newRepairType;
  updateAfterSplitting=false;
  maxUpdateQueue=2000;
  updateQueue=new ipcUpdateFeature<ipcFeatureType>[maxUpdateQueue];
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::~ipcCSCEngine()
{
  if (islandIterator!=NULL) delete islandIterator;
  if (ceQueue!=NULL) delete[] ceQueue;
  if (updateQueue!=NULL) delete[] updateQueue;
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::changeCEBase(ipcCodeelementBase<ipcFeatureType>& newCEBase)
{
  hierarchy=&(newCEBase.getHierarchy());
  ceBase=&newCEBase;
  if (islandIterator!=NULL) delete islandIterator;
  islandIterator=hierarchy->createIteratorBU();
  setROI(0,0,hierarchy->getSize(),hierarchy->getSize());
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::setROI(int x, int y, int w, int h)
{
  roiX1=(x>=0) ? x : 0;
  roiY1=(y>=0) ? y : 0;
  roiX2=(x+w<=hierarchy->getSize()) ? x+w : hierarchy->getSize();
  roiY2=(y+h<=hierarchy->getSize()) ? y+h : hierarchy->getSize();
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::startSegmentation(int w, int h, const ipcPixelType* image)
{
  int tryAgain = 4;
  // Correct region of interest
  if (roiX2>w) roiX2=w;
  if (roiY2>h) roiY2=h;

  // Reset the codebase
  ceBase->clearContent();
  
  // Segmentation
  disintegratedCEs=0;
  do
  {
    try
    {
      coding(w,h,image);
      level0Linking();
      levelNLinking();

      // Splitting
      if (splittingType==ipcDeferredSplitting)
        deferredSplitting();

      tryAgain=0;
#ifdef IPC_DEBUG_DISINTEGRATION
      testConnectivity();
#endif
      storeSegments();
    }  
    catch (ipcCodeelementBaseOverrun&)
    {
      ceBase->reinit(2*ceBase->getAVGCapacityPerIsland());
      tryAgain--;
    }
  } while (tryAgain>0);

}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::coding(int w, int h, const ipcPixelType* image)
{
	(void)h;
  const ipcNeighborTable& neighborTable = hierarchy->getNeighborTable();
  int xcoords[7],ycoords[7],pixQueue[49],pixelCount;
  const ipcPixelType* values[7];
  bool used[7];
  int startPos,currPos,neighPos,i,inQueue,nextElem,remainingPixels;
  
  if (islandIterator->begin())
    do
    {
      const ipcIsland& currIsland = islandIterator->currentIsland(); // Island to code...
      
      ceBase->newIsland(currIsland);
      
      // Get all pixels of the current island...
      hierarchy->getSubPixels(currIsland,xcoords,ycoords);
      
      remainingPixels=0;
      if (xcoords[0]<=roiX2 || ycoords[0]<=roiY2)
        for (i=0; i<7; i++)
        {
          if (roiX1<=xcoords[i] && xcoords[i]<roiX2 && roiY1<=ycoords[i] && ycoords[i]<roiY2)
          {
            used[i]=false;
            values[i]=&(image[xcoords[i]+w*ycoords[i]]);
            remainingPixels++;
          }
          else used[i]=true;
        }
        
        for (startPos=0; (startPos<7) && (remainingPixels>=1); startPos++)
          if (!used[startPos])
          {
            ipcCodeelement<ipcFeatureType>* newCE = ceBase->getCurrentCE();
            
            if (newCE==NULL) throw ipcCodeelementBaseOverrun();
            
            newCE->subCEs=NULL;
            newCE->parents[0]=NULL;
            newCE->parents[1]=NULL;
            newCE->root=NULL;
            newCE->numOfSubCEs=0;
            newCE->flags=ipcCERoot;
            newCE->form=(1<<startPos);
#ifdef IPC_CSC_STORE_ISLAND
            newCE->island=currIsland;
#endif
#ifdef IPC_CSC_STORE_BOUNDING_BOX
            newCE->bbLeft=xcoords[startPos];
            newCE->bbTop=ycoords[startPos];
            newCE->bbRight=newCE->bbLeft+1;
            newCE->bbBottom=newCE->bbTop+1;
#endif
            pixelCount=1;
            
            linkControl->begin(0,*values[startPos]);
            
            used[startPos]=true;
            pixQueue[0]=startPos;
            inQueue=1;
            nextElem=0;
            remainingPixels--;
            
            while (nextElem<inQueue)
            {
              currPos=pixQueue[nextElem]; 
              nextElem++;  // Extract next position form queue
              for (i=0; neighborTable[currPos][i]!=-1; i++) // Extract all neighbors from queue
              {
                neighPos=neighborTable[currPos][i];
                if (!used[neighPos])
                {
                  if (linkControl->add(*values[currPos],*values[neighPos]))
                  {
                    used[neighPos]=true;
                    pixQueue[inQueue]=neighPos;
                    inQueue++;
                    newCE->form|=(1<<neighPos);
                    pixelCount++;
#ifdef IPC_CSC_STORE_BOUNDING_BOX
                    if (xcoords[neighPos]<newCE->bbLeft)
                      newCE->bbLeft=xcoords[neighPos];
                    else if (xcoords[neighPos]>=newCE->bbRight)
                      newCE->bbRight=xcoords[neighPos]+1;
                    if (ycoords[neighPos]<newCE->bbTop)
                      newCE->bbTop=ycoords[neighPos];
                    else if (ycoords[neighPos]>=newCE->bbBottom)
                      newCE->bbBottom=ycoords[neighPos]+1;
#endif
                    remainingPixels--;
                    if (remainingPixels==0) break;
                  }
                }
              }
              if (remainingPixels==0) break;
            }
            if (pixelCount>1)
            {
              linkControl->setFeature(newCE->data);
              ceBase->storeCurrentCE(false);
            }
            else remainingPixels++;
          }
    } while (islandIterator->nextIsland());
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::level0Linking()
{
  const ipcNeighborTable& neighborTable = hierarchy->getNeighborTable();
  const ipcCommonIslTable& commonIslTable = hierarchy->getCommonIslandTable(); 
  ipcSubCodeelement<ipcFeatureType> ceQueue[441]; // 7 (Islands) * 3 (Max. Codeelements per Island) = 21
  ipcIsland subIslands[7];
  ipcCodeelement<ipcFeatureType>* subCEs[7];
  ipcCodeelement<ipcFeatureType>* startCE;
  ipcCodeelement<ipcFeatureType>* temp;
  int i,inQueue,nextElem,startPos;
  int numOfCEs[7];
  int currPos,neighPos,remainingCEs;
  
  if (islandIterator->nextLevel())
    do
    {
      const ipcIsland& currIsland = islandIterator->currentIsland();
      
      ceBase->newIsland(currIsland);
      
      hierarchy->getSubIslands(currIsland,subIslands);
      ceBase->getCodeelements(subIslands,7,subCEs,numOfCEs);
      
      remainingCEs=numOfCEs[0]+numOfCEs[1]+numOfCEs[2]+numOfCEs[3]+numOfCEs[4]+numOfCEs[5]+numOfCEs[6];
      for (startPos=0; (startPos<7) && (remainingCEs>1); startPos++)
      { 
        startCE=subCEs[startPos];
        while (startCE!=NULL)
        {
          if ((startCE->flags & ipcCEUsed) == 0)
          {
            ipcCodeelement<ipcFeatureType>* newCE = ceBase->getCurrentCE();
            
            if (newCE==NULL) throw ipcCodeelementBaseOverrun();
            
            newCE->parents[0]=NULL;
            newCE->parents[1]=NULL;
            newCE->root=NULL;
            newCE->flags=ipcCERoot;
            newCE->form=(1<<startPos);
            newCE->numOfSubCEs=1;
            newCE->subCEs[0].pos=startPos;
            newCE->subCEs[0].ce=startCE;
#ifdef IPC_CSC_STORE_ISLAND
            newCE->island=currIsland;
#endif
#ifdef IPC_CSC_STORE_BOUNDING_BOX
            newCE->bbLeft=startCE->bbLeft;
            newCE->bbRight=startCE->bbRight;
            newCE->bbTop=startCE->bbTop;
            newCE->bbBottom=startCE->bbBottom;
#endif
            linkControl->begin(1,startCE);
            ceQueue[0].ce=startCE;
            ceQueue[0].pos=startPos;
            startCE->flags|=ipcCEUsed;
            remainingCEs--;
            
            inQueue=1;
            nextElem=0;
            
            while (nextElem<inQueue)
            {
              advAssert(inQueue<=441);
              ipcCodeelement<ipcFeatureType>* currCE=ceQueue[nextElem].ce;
              currPos=ceQueue[nextElem].pos;
              nextElem++;  // Extract next position form queue
              
              for (i=0; neighborTable[currPos][i]!=-1; i++) // Extract all neighbors from queue
              {
                neighPos=neighborTable[currPos][i];
                advAssert(commonIslTable[currPos][neighPos]>=0);
                ipcCodeelement<ipcFeatureType>* neighCE=subCEs[neighPos];
                while (neighCE!=NULL)
                {
                  if (((neighCE->flags & ipcCEUsed) == 0)
                    && ((currCE->form & (1<<commonIslTable[currPos][neighPos]))!=0)
                    && ((neighCE->form & (1<<commonIslTable[neighPos][currPos]))!=0))
                  {
                    if (linkControl->add(currCE,neighCE))
                    {
                      ceQueue[inQueue].ce=neighCE;
                      ceQueue[inQueue].pos=neighPos;
                      inQueue++;
                      
                      neighCE->flags|=ipcCEUsed;
                      
                      newCE->form|=(1<<neighPos);
                      newCE->subCEs[newCE->numOfSubCEs].pos=neighPos;
                      newCE->subCEs[newCE->numOfSubCEs].ce=neighCE;
                      newCE->numOfSubCEs++;
                      
                      advAssert(neighCE->parents[0]==NULL || neighCE->parents[1]==NULL);
                      if (neighCE->parents[0]==NULL) neighCE->parents[0]=newCE;
                      else neighCE->parents[1]=newCE;
                      neighCE->flags&=~ipcCERoot;
#ifdef IPC_CSC_STORE_BOUNDING_BOX
                      if (neighCE->bbLeft<newCE->bbLeft) newCE->bbLeft=neighCE->bbLeft;
                      if (neighCE->bbRight>newCE->bbRight) newCE->bbRight=neighCE->bbRight;
                      if (neighCE->bbBottom>newCE->bbBottom) newCE->bbBottom=neighCE->bbBottom;
                      if (neighCE->bbTop<newCE->bbTop) newCE->bbTop=neighCE->bbTop;
#endif
                      remainingCEs--;
                      if (remainingCEs==0) break;
                    }
                  }
                  neighCE=neighCE->next;
                }
                if (remainingCEs==0) break;
              }
              if (remainingCEs==0) break;
            }
            if (newCE->numOfSubCEs>1)
            {
              linkControl->setFeature(newCE->data);
              advAssert(startCE->parents[0]==NULL || startCE->parents[1]==NULL);
              if (startCE->parents[0]==NULL) startCE->parents[0]=newCE;
              else startCE->parents[1]=newCE;
              startCE->flags&=~(ipcCERoot);
              ceBase->storeCurrentCE(true);
            }
            else remainingCEs++;
            if (remainingCEs<=1) break;
          }
          startCE=startCE->next;
        }
      }
      for (i=0; i<7; i++)
      {
        temp=subCEs[i];
        while (temp!=NULL)
        {
          temp->flags&=~ipcCEUsed;
          temp=temp->next;
        }
      }
    } while (islandIterator->nextIsland());
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::storeSegments()
{
  ipcCodeelement<ipcFeatureType>* ce;
  int count;

  if (islandIterator->begin())
  {
    do
    {
      do
      {
        const ipcIsland& currIsland = islandIterator->currentIsland();
        ce=ceBase->getCodeelements(currIsland,count);
        while (ce!=NULL)
        { 
          if (ce->flags & ipcCERoot) ceBase->addNewSegment(currIsland,ce);          
          ce=ce->next;
        }
      } while (islandIterator->nextIsland());
    } while (islandIterator->nextLevel());
  }
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::levelNLinking()
{
  const ipcConnectedWithTable& connectedWithTable = hierarchy->getConnectedWithTable();
  //const ipcCommonIslTable& commonIslTable = hierarchy->getCommonIslandTable(); 
  int inQueue,nextElem;
  ipcIsland subIslands[7];
  ipcCodeelement<ipcFeatureType>* subCEs[7];
  ipcCodeelement<ipcFeatureType>* startCE;
  ipcCodeelement<ipcFeatureType>* temp;
  ipcSubCodeelement<ipcFeatureType>* connectCE;
  int numOfCEs[7],startPos/*,ceNr*/;
  int currPos,neighPos,connectPos,i,j;
  ipcSplittingPair<ipcFeatureType> splittingInfo;
  //int numOfLevels = hierarchy->numberOfLevels();
  
  while (islandIterator->nextLevel())
  {
    do
    {
      const ipcIsland& currIsland = islandIterator->currentIsland();
      
      ceBase->newIsland(currIsland);
      hierarchy->getSubIslands(currIsland,subIslands);
      ceBase->getCodeelements(subIslands,7,subCEs,numOfCEs);
      
      for (startPos=0; startPos<7; startPos++)
      {
        startCE=subCEs[startPos];
        while (startCE!=NULL)
        {
          if ((startCE->flags & ipcCEUsed) == 0)
          {
            ipcCodeelement<ipcFeatureType>* newCE = ceBase->getCurrentCE();
            
            if (newCE==NULL)
            {
              if (ceQueue!=NULL) delete[] ceQueue;
              throw ipcCodeelementBaseOverrun();
            }
            
            newCE->parents[0]=NULL;
            newCE->parents[1]=NULL;
            newCE->root=NULL;
            newCE->flags=ipcCERoot;
            newCE->form=(1<<startPos);
            newCE->numOfSubCEs=1;
            newCE->subCEs[0].pos=startPos;
            newCE->subCEs[0].ce=startCE;
#ifdef IPC_CSC_STORE_ISLAND
            newCE->island=currIsland;
#endif
#ifdef IPC_CSC_STORE_BOUNDING_BOX
            newCE->bbLeft=startCE->bbLeft;
            newCE->bbRight=startCE->bbRight;
            newCE->bbTop=startCE->bbTop;
            newCE->bbBottom=startCE->bbBottom;
#endif
            
            linkControl->begin(currIsland.level,startCE);
            ceQueue[0].ce=startCE;
            ceQueue[0].pos=startPos;
            ceQueue[0].ce->flags|=ipcCEUsed;
            inQueue=1;
            nextElem=0;
            
            while (nextElem<inQueue)
            {
              ipcSubCodeelement<ipcFeatureType>& currSubCE=ceQueue[nextElem];
              ipcCodeelement<ipcFeatureType>* currCE=currSubCE.ce;
              currPos=currSubCE.pos;
              nextElem++;
              
              //for (int subCENr=0; subCENr<currCE->numOfSubCEs; subCENr++)
              connectCE=currCE->subCEs;
              while (connectCE!=NULL)
              {
                connectPos = connectCE->pos;
                neighPos = connectedWithTable[currPos][connectPos];
                
                if (neighPos>=0)
                {
                  ipcCodeelement<ipcFeatureType>* neighCE;
                  
                  advAssert(connectCE->ce->parents[0]==currCE || connectCE->ce->parents[1]==currCE);
                  neighCE=(connectCE->ce->parents[0]==currCE) ? connectCE->ce->parents[1] : connectCE->ce->parents[0];
                  advAssert(neighCE!=currCE);
                  if (neighCE!=NULL && ((neighCE->flags & ipcCEUsed) == 0))
                  {
                    if (linkControl->add(currCE,neighCE))
                    { 
                      if (inQueue>=maxQueue)
                      {
                        maxQueue*=2;
                        ipcSubCodeelement<ipcFeatureType>* newQueue=new ipcSubCodeelement<ipcFeatureType>[maxQueue];
                        for (j=0; j<inQueue; j++) newQueue[j]=ceQueue[j];
                        delete[] ceQueue;
                        ceQueue=newQueue;
                      }
                      ceQueue[inQueue].ce=neighCE;
                      ceQueue[inQueue].pos=neighPos;
                      inQueue++;
                      
                      neighCE->flags|=ipcCEUsed;
                      
                      newCE->form|=(1<<neighPos);
                      newCE->subCEs[newCE->numOfSubCEs].pos=neighPos;
                      newCE->subCEs[newCE->numOfSubCEs].ce=neighCE;
                      newCE->numOfSubCEs++;
                      advAssert(neighCE->parents[0]==NULL || neighCE->parents[1]==NULL);
                      if (neighCE->parents[0]==NULL) neighCE->parents[0]=newCE;
                      else neighCE->parents[1]=newCE;
                      neighCE->flags&=~ipcCERoot;
#ifdef IPC_CSC_STORE_BOUNDING_BOX
                      if (neighCE->bbLeft<newCE->bbLeft) newCE->bbLeft=neighCE->bbLeft;
                      if (neighCE->bbRight>newCE->bbRight) newCE->bbRight=neighCE->bbRight;
                      if (neighCE->bbBottom>newCE->bbBottom) newCE->bbBottom=neighCE->bbBottom;
                      if (neighCE->bbTop<newCE->bbTop) newCE->bbTop=neighCE->bbTop;
#endif
                    }
                    else if (splittingType==ipcDirectSplitting)// || splittingType==ipcDirectSplittingRecursive)
                    {
                      splittingInfo.root1=currCE;
                      splittingInfo.root2=neighCE;
                      splittingInfo.island=currIsland;
                      splittingInfo.relPos1=currPos;
                      splittingInfo.relPos2=neighPos;
                      splittingInfo.ce1=currCE;
                      splittingInfo.ce2=neighCE;
                      splittingQueue.enqueue(splittingInfo);
                    }
                  }
                }
                connectCE=connectCE->next;
              }
            }
            if (newCE->numOfSubCEs>1)
            {
              linkControl->setFeature(newCE->data);
              advAssert(startCE->parents[0]==NULL || startCE->parents[1]==NULL);
              if (startCE->parents[0]==NULL) startCE->parents[0]=newCE;
              else startCE->parents[1]=newCE;
              startCE->flags&=~ipcCERoot;
              ceBase->storeCurrentCE(true);
            }
          }
          startCE=startCE->next;
        }
      }
      for (i=0; i<7; i++)
      {
        temp=subCEs[i];
        while (temp!=NULL)
        {
          temp->flags&=~ipcCEUsed;
          temp=temp->next;
        }
      }
    } while (islandIterator->nextIsland());
    
    if (splittingType==ipcDirectSplitting) directSplitting();
  }

}


#ifdef IPC_DEBUG_DISINTEGRATION
template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
bool ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::testConnectivity(ipcCodeelement<ipcFeatureType>* rootCE)
{
  int i,j,inQueue,neighPos;
  const ipcConnectedWithTable& connectedWithTable = hierarchy->getConnectedWithTable();
  const ipcCommonIslTable& commonIslTable = hierarchy->getCommonIslandTable(); 
  ipcSubCodeelement<ipcFeatureType> current;
  ipcSubCodeelement<ipcFeatureType>* subCE;
  ipcCodeelement<ipcFeatureType>* neighCE;
 
  i=0;
  j=0;
  if (j<rootCE->numOfSubCEs)
  {
    inQueue=1;
    ceQueue[0]=rootCE->subCEs[j];
    ceQueue[0].ce->flags|=ipcCEInQueue;
  }
  else inQueue=0;

  while (i<inQueue)
  {
    current=ceQueue[i]; i++;
    subCE=current.ce->subCEs;
    while (subCE!=NULL)
    {
      neighPos=connectedWithTable[current.pos][subCE->pos];
      if (neighPos!=-1 && subCE->ce->parents[0]!=NULL && subCE->ce->parents[1]!=NULL)
      {
        if (inQueue>=maxQueue)
        {
          maxQueue*=2;
          ipcSubCodeelement<ipcFeatureType>* newQueue=new ipcSubCodeelement<ipcFeatureType>[maxQueue];
          for (j=0; j<inQueue; j++) newQueue[j]=ceQueue[j];
          delete[] ceQueue;
          ceQueue=newQueue;
        }  
        if (subCE->ce->parents[0]==current.ce)
        {
          neighCE=subCE->ce->parents[1];
          if (((neighCE->flags & ipcCEInQueue)==0) && (neighCE->parents[0]==rootCE || neighCE->parents[1]==rootCE))
          {
            ceQueue[inQueue].pos=neighPos;
            ceQueue[inQueue].ce=neighCE;
            ceQueue[inQueue].ce->flags|=ipcCEInQueue;
            inQueue++;
          }
        }
        else 
        {
          neighCE=subCE->ce->parents[0];
          if (((neighCE->flags & ipcCEInQueue)==0) && (neighCE->parents[0]==rootCE || neighCE->parents[1]==rootCE))
          {
            ceQueue[inQueue].pos=neighPos;
            ceQueue[inQueue].ce=neighCE;
            ceQueue[inQueue].ce->flags|=ipcCEInQueue;
            inQueue++;
          }
        }
      }
      subCE=subCE->next;
    }
  }
  advAssert(inQueue<=rootCE->numOfSubCEs);
  for (i=0; i<inQueue; i++)
    ceQueue[i].ce->flags&=~ipcCEInQueue;

  return (inQueue==rootCE->numOfSubCEs);
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
bool ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::testLevel1Connectivity(ipcCodeelement<ipcFeatureType>* rootCE)
{
  int i,j,inQueue;
  const ipcConnectedWithTable& connectedWithTable = hierarchy->getConnectedWithTable();
  const ipcCommonIslTable& commonIslTable = hierarchy->getCommonIslandTable(); 
  ipcSubCodeelement<ipcFeatureType> current;
  ipcSubCodeelement<ipcFeatureType>* searchCE;
 
  i=0;
  searchCE=rootCE->subCEs;
  while (searchCE!=NULL && searchCE->ce==removedCE) searchCE=searchCE->next;
  if (searchCE!=NULL)
  {
    inQueue=1;
    ceQueue[0]=(*searchCE);
    ceQueue[0].ce->flags|=ipcCEInQueue;
  }
  else inQueue=0;

  while (i<inQueue)
  {
    current=ceQueue[i]; i++;
    searchCE=rootCE->subCEs;
    while (searchCE!=NULL)
    {
      if ((searchCE->ce->flags & ipcCEInQueue)==0 && searchCE->ce!=removedCE 
                 && ((current.ce->form & (1<<commonIslTable[current.pos][searchCE->pos]))!=0)
                 && ((searchCE->ce->form & (1<<commonIslTable[searchCE->pos][current.pos]))!=0))
      {
        if (inQueue>=maxQueue)
        {
          maxQueue*=2;
          ipcSubCodeelement<ipcFeatureType>* newQueue=new ipcSubCodeelement<ipcFeatureType>[maxQueue];
          for (j=0; j<inQueue; j++) newQueue[j]=ceQueue[j];
          delete[] ceQueue;
          ceQueue=newQueue;
        }  
        ceQueue[inQueue]=*searchCE;
        searchCE->ce->flags|=ipcCEInQueue;
        inQueue++;
      }
      searchCE=searchCE->next;
    }
  }
  advAssert(inQueue<=rootCE->numOfSubCEs);
  for (i=0; i<inQueue; i++)
    ceQueue[i].ce->flags&=~ipcCEInQueue;

  return (inQueue==rootCE->numOfSubCEs);
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::testConnectivity()
{
  ipcCodeelement<ipcFeatureType>* current;
  int /*i,*/ceCount;
  ipcTopDownIslandIterator* islIterator = hierarchy->createIteratorTD();
  
  disintegratedCEs=0;
  islIterator->begin();
  do
  {
    do
    {
      current=ceBase->getCodeelements(islIterator->currentIsland(),ceCount);
      while (current)
      {
        if (!testConnectivity(current))
        {
          current->flags|=ipcCEDisintegrated;
          disintegratedCEs++;
        }
        current=current->next;
      }
    } while (islIterator->nextIsland());
  } while (islIterator->nextLevel() && islIterator->currentIsland().level>1);
}
#endif

template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::deferredSplitting()
{
  ipcCodeelement<ipcFeatureType>* current;
  ipcCodeelement<ipcFeatureType>* root1;
  ipcCodeelement<ipcFeatureType>* root2;
  int /*i,*/ceCount;
  ipcTopDownIslandIterator* islIterator = hierarchy->createIteratorTD();
  
  islIterator->begin();
  do
  {
    do
    {
      current=ceBase->getCodeelements(islIterator->currentIsland(),ceCount);
      while (current!=NULL)
      {
        root1=(current->parents[0]!=NULL) ? current->parents[0]->root : NULL;
        root2=(current->parents[1]!=NULL) ? current->parents[1]->root : NULL;
        
        if (root1==NULL && root2!=NULL) current->root=root2;
        else if (root2==NULL && root1!=NULL) current->root=root1;
        else if (root1==NULL && root2==NULL) current->root=current;
        else if (root1==root2) current->root=root1;
        else
        {
          switch (linkControl->compareFeatures(root1->data,root2->data,current->data))
          {
          case 1: ceBase->removeSubCE(current->parents[1],current);
            current->root=current->parents[0]->root;
            break;
          case 2: ceBase->removeSubCE(current->parents[0],current);
            current->root=current->parents[1]->root;
            break;
          }
        }
        current=current->next;
      }
    } while (islIterator->nextIsland());
  } while (islIterator->nextLevel());
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
inline void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::updateFeature(int level, ipcCodeelement<ipcFeatureType>* ce)
{
  advAssert(level>0);
  if ((ce->flags & ipcCEVisited)==0)
  {
    int nextUpdate,lastUpdate;
    ipcSubCodeelement<ipcFeatureType>* subCE;

    updateQueue[0].level=0;
    updateQueue[0].ce=ce;
    ce->flags|=ipcCEVisited;
    nextUpdate=0;
    lastUpdate=1;
    while (nextUpdate<lastUpdate)
    {
      ipcUpdateFeature<ipcFeatureType>& updateFeature = updateQueue[nextUpdate];
      updateFeature.ce->flags&=~ipcCEVisited;

      subCE=updateFeature.ce->subCEs;
      advAssert(subCE!=NULL);
      if (subCE!=NULL)
      {
        linkControl->begin(level,subCE->ce);
        subCE=subCE->next;
        while (subCE!=NULL)
        {
          linkControl->add(subCE->ce);
          subCE=subCE->next;
        }
      }
      linkControl->setFeature(updateFeature.ce->data);

      if (updateFeature.ce->parents[0] && (updateFeature.ce->flags & ipcCEVisited)==0)
      {
        if (lastUpdate>=maxUpdateQueue)
        {
          maxUpdateQueue*=2;
          ipcUpdateFeature<ipcFeatureType>* newUpdateQueue=new ipcUpdateFeature<ipcFeatureType>[maxQueue];
          for (int j=0; j<lastUpdate; j++) newUpdateQueue[j]=updateQueue[j];
          delete[] updateQueue;
          updateQueue=newUpdateQueue;
        }
        updateQueue[lastUpdate].level=level+1;
        updateQueue[lastUpdate].ce=updateFeature.ce->parents[0];
        updateFeature.ce->parents[0]->flags|=ipcCEVisited;
        lastUpdate++;
      }

      if (updateFeature.ce->parents[1] && (updateFeature.ce->flags & ipcCEVisited)==0)
      {
        if (lastUpdate>=maxUpdateQueue)
        {
          maxUpdateQueue*=2;
          ipcUpdateFeature<ipcFeatureType>* newUpdateQueue=new ipcUpdateFeature<ipcFeatureType>[maxQueue];
          for (int j=0; j<lastUpdate; j++) newUpdateQueue[j]=updateQueue[j];
          delete[] updateQueue;
          updateQueue=newUpdateQueue;
        }
        updateQueue[lastUpdate].level=level+1;
        updateQueue[lastUpdate].ce=updateFeature.ce->parents[1];
        updateFeature.ce->parents[1]->flags|=ipcCEVisited;
        lastUpdate++;
      }
      nextUpdate++;
    }
  }
}            


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::directSplitting()
{
  const ipcCommonIslTable& commonIslTable = hierarchy->getCommonIslandTable();
  const ipcConnectedWithTable& connectedWithTable = hierarchy->getConnectedWithTable();
  ipcSplittingPair<ipcFeatureType> currentPair;
  ipcSplittingPair<ipcFeatureType> newPair;
  int commonPos,masterCE;
  ipcSubCodeelement<ipcFeatureType>* commonCE;
  ipcSubCodeelement<ipcFeatureType>* subCE;
  
  int number=splittingQueue.numOfElements();
  int count=number;
  while (!splittingQueue.isEmpty())
  {
    currentPair=splittingQueue.current();
    count--;
    commonCE=currentPair.ce1->subCEs;
    while (commonCE!=NULL)
    {
      if (commonCE->ce->parents[0]==currentPair.ce2 || commonCE->ce->parents[1]==currentPair.ce2)
      {
        masterCE=linkControl->compareFeatures(currentPair.root1->data,currentPair.root2->data,commonCE->ce->data);
        if (repairType==ipcFastRepair)
        {
          if (masterCE==1)
          {
            if (commonCE->ce->numOfSubCEs>0 && !testConnectivityIf(currentPair.ce2,commonCE->ce)) 
            {
              if ((currentPair.island.level>1 && testConnectivityIf(currentPair.ce1,commonCE->ce)) 
                 || (currentPair.island.level==1 && testLevel1ConnectivityIf(currentPair.ce1,commonCE->ce))) 
                masterCE=2;
              else
              {
                if ((currentPair.ce2->flags & ipcCEDisintegrated)==0)
                  currentPair.ce2->flags|=ipcCEDisintegrated;
              }
            }
          }
          else
          {
            if (commonCE->ce->numOfSubCEs>0 && !testConnectivityIf(currentPair.ce1,commonCE->ce)) 
            {
              if ((currentPair.island.level>1 && testConnectivityIf(currentPair.ce2,commonCE->ce))
                 || (currentPair.island.level==1 && testLevel1ConnectivityIf(currentPair.ce1,commonCE->ce))) 
                masterCE=1;
              else
              {
                if ((currentPair.ce1->flags & ipcCEDisintegrated)==0)
                  currentPair.ce1->flags|=ipcCEDisintegrated;
              }
            }
          }
        }

        if (masterCE==1)
        {
          ipcIsland subIsland;

          hierarchy->getSubIsland(currentPair.island,currentPair.relPos2,subIsland);
          ceBase->removeSubCE(currentPair.ce2,commonCE->ce);
          if (updateAfterSplitting) updateFeature(currentPair.island.level,currentPair.ce2);
          commonPos=commonIslTable[currentPair.relPos2][currentPair.relPos1];
          subCE=commonCE->ce->subCEs;
          while (subCE!=NULL)
          {
            if (connectedWithTable[commonPos][subCE->pos]>=0 && subCE->ce->parents[0]!=NULL && subCE->ce->parents[1]!=NULL)
            {
              newPair.root1=currentPair.root1;
              newPair.root2=currentPair.root2;
              newPair.relPos1=commonPos;
              newPair.relPos2=connectedWithTable[commonPos][subCE->pos];
              newPair.island=subIsland;
              newPair.ce1=commonCE->ce;
              if (subCE->ce->parents[0]==commonCE->ce) newPair.ce2=subCE->ce->parents[1];
              else newPair.ce2=subCE->ce->parents[0];
              splittingQueue.enqueue(newPair);
            }
            subCE=subCE->next;
          }
          if ((currentPair.ce2->flags & ipcCEDisintegrated) || repairType==ipcPreciseRepair)
          {
            currentPair.ce2->flags&=~ipcCEDisintegrated;
            repair(subIsland,currentPair.ce2);
          }
        }
        else if (masterCE==2)
        {
          ipcIsland subIsland;

          hierarchy->getSubIsland(currentPair.island,currentPair.relPos1,subIsland);
          ceBase->removeSubCE(currentPair.ce1,commonCE->ce);
  		    if (updateAfterSplitting) updateFeature(currentPair.island.level,currentPair.ce1);
          commonPos=commonIslTable[currentPair.relPos1][currentPair.relPos2];
          subCE=commonCE->ce->subCEs;
          while (subCE!=NULL)
          {
            if (connectedWithTable[commonPos][subCE->pos]>=0 && subCE->ce->parents[0]!=NULL && subCE->ce->parents[1]!=NULL)
            {
              newPair.root1=currentPair.root1;
              newPair.root2=currentPair.root2;
              newPair.relPos1=connectedWithTable[commonPos][subCE->pos];
              newPair.relPos2=commonPos;
              newPair.island=subIsland;
              if (subCE->ce->parents[0]==commonCE->ce) newPair.ce1=subCE->ce->parents[1];
              else newPair.ce1=subCE->ce->parents[0];
              newPair.ce2=commonCE->ce;
              splittingQueue.enqueue(newPair);
            }
            subCE=subCE->next;
          }
          if ((currentPair.ce1->flags & ipcCEDisintegrated) || repairType==ipcPreciseRepair)
          {
            currentPair.ce1->flags&=~ipcCEDisintegrated;
            repair(subIsland,currentPair.ce1);
          }
        }
      }
      commonCE=commonCE->next;
    }
    splittingQueue.dequeue();
  }
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
bool ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::testConnectivityIf(ipcCodeelement<ipcFeatureType>* rootCE, ipcCodeelement<ipcFeatureType>* removedCE)
{
  int i,j,inQueue,neighPos;
  const ipcConnectedWithTable& connectedWithTable = hierarchy->getConnectedWithTable();
  //const ipcCommonIslTable& commonIslTable = hierarchy->getCommonIslandTable(); 
  ipcSubCodeelement<ipcFeatureType> current;
  ipcSubCodeelement<ipcFeatureType>* subCE;
  ipcCodeelement<ipcFeatureType>* neighCE;
 
  i=0;
  subCE=rootCE->subCEs;
  while (subCE!=NULL && subCE->ce==removedCE) subCE=subCE->next;
  if (subCE!=NULL)
  {
    inQueue=1;
    ceQueue[0]=*subCE;
    subCE->ce->flags|=ipcCEInQueue;
  }
  else inQueue=0;

  while (i<inQueue)
  {
    current=ceQueue[i]; i++;
    subCE=current.ce->subCEs;
    while (subCE!=NULL)
    {
      neighPos=connectedWithTable[current.pos][subCE->pos];
      if (neighPos!=-1 && subCE->ce->parents[0]!=NULL && subCE->ce->parents[1]!=NULL && subCE->ce->parents[0]!=removedCE && subCE->ce->parents[1]!=removedCE)
      {
        if (inQueue>=maxQueue)
        {
          maxQueue*=2;
          ipcSubCodeelement<ipcFeatureType>* newQueue=new ipcSubCodeelement<ipcFeatureType>[maxQueue];
          for (j=0; j<inQueue; j++) newQueue[j]=ceQueue[j];
          delete[] ceQueue;
          ceQueue=newQueue;
        }  
        if (subCE->ce->parents[0]==current.ce)
        {
          neighCE=subCE->ce->parents[1];
          if (((neighCE->flags & ipcCEInQueue)==0) && neighCE!=removedCE && (neighCE->parents[0]==rootCE || neighCE->parents[1]==rootCE))
          {
            ceQueue[inQueue].pos=neighPos;
            ceQueue[inQueue].ce=neighCE;
            ceQueue[inQueue].ce->flags|=ipcCEInQueue;
            inQueue++;
          }
        }
        else 
        {
          neighCE=subCE->ce->parents[0];
          if (((neighCE->flags & ipcCEInQueue)==0) && neighCE!=removedCE && (neighCE->parents[0]==rootCE || neighCE->parents[1]==rootCE))
          {
            ceQueue[inQueue].pos=neighPos;
            ceQueue[inQueue].ce=neighCE;
            ceQueue[inQueue].ce->flags|=ipcCEInQueue;
            inQueue++;
          }
        }
      }
      subCE=subCE->next;
    }
  }
  advAssert(inQueue+1<=rootCE->numOfSubCEs);
  for (i=0; i<inQueue; i++)
    ceQueue[i].ce->flags&=~ipcCEInQueue;

  return (inQueue+1==rootCE->numOfSubCEs);
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
bool ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::testLevel1ConnectivityIf(ipcCodeelement<ipcFeatureType>* rootCE, ipcCodeelement<ipcFeatureType>* removedCE)
{
  int i,j,inQueue;
  //const ipcConnectedWithTable& connectedWithTable = hierarchy->getConnectedWithTable();
  const ipcCommonIslTable& commonIslTable = hierarchy->getCommonIslandTable(); 
  ipcSubCodeelement<ipcFeatureType> current;
  ipcSubCodeelement<ipcFeatureType>* searchCE;
 
  i=0;
  searchCE=rootCE->subCEs;
  while (searchCE!=NULL && searchCE->ce==removedCE) searchCE=searchCE->next;
  if (searchCE!=NULL)
  {
    inQueue=1;
    ceQueue[0]=(*searchCE);
    ceQueue[0].ce->flags|=ipcCEInQueue;
  }
  else inQueue=0;

  while (i<inQueue)
  {
    current=ceQueue[i]; i++;
    searchCE=rootCE->subCEs;
    while (searchCE!=NULL)
    {
      if ((searchCE->ce->flags & ipcCEInQueue)==0 && searchCE->ce!=removedCE 
                 && ((current.ce->form & (1<<commonIslTable[current.pos][searchCE->pos]))!=0)
                 && ((searchCE->ce->form & (1<<commonIslTable[searchCE->pos][current.pos]))!=0))
      {
        if (inQueue>=maxQueue)
        {
          maxQueue*=2;
          ipcSubCodeelement<ipcFeatureType>* newQueue=new ipcSubCodeelement<ipcFeatureType>[maxQueue];
          for (j=0; j<inQueue; j++) newQueue[j]=ceQueue[j];
          delete[] ceQueue;
          ceQueue=newQueue;
        }  
        ceQueue[inQueue]=*searchCE;
        searchCE->ce->flags|=ipcCEInQueue;
        inQueue++;
      }
      searchCE=searchCE->next;
    }
  }
  advAssert(inQueue+1<=rootCE->numOfSubCEs);
  for (i=0; i<inQueue; i++)
    ceQueue[i].ce->flags&=~ipcCEInQueue;

  return (inQueue+1==rootCE->numOfSubCEs);
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::repair(ipcCodeelement<ipcFeatureType>* rootCE, ipcSubCodeelement<ipcFeatureType>* subCEList, int &numOfConnected, ipcSubCodeelement<ipcFeatureType>* &connectedList, unsigned char &connectedForm, int &numOfRest, ipcSubCodeelement<ipcFeatureType>* &restList)  
{
  int i,j,inQueue,neighPos;
  const ipcConnectedWithTable& connectedWithTable = hierarchy->getConnectedWithTable();
  //const ipcCommonIslTable& commonIslTable = hierarchy->getCommonIslandTable(); 
  ipcSubCodeelement<ipcFeatureType> current;
  ipcSubCodeelement<ipcFeatureType>* subCE;
  ipcCodeelement<ipcFeatureType>* neighCE;
  
  i=0;
  inQueue=1;
  ceQueue[0]=rootCE->subCEs[0];
  ceQueue[0].ce->flags|=ipcCEInQueue;
  while (i<inQueue)
  {
    current=ceQueue[i]; i++;
    subCE=current.ce->subCEs;
    while (subCE!=NULL)
    {
      neighPos=connectedWithTable[current.pos][subCE->pos];
      if (neighPos!=-1 && subCE->ce->parents[0]!=NULL && subCE->ce->parents[1]!=NULL)
      {
        if (inQueue>=maxQueue)
        {
          maxQueue*=2;
          ipcSubCodeelement<ipcFeatureType>* newQueue=new ipcSubCodeelement<ipcFeatureType>[maxQueue];
          for (j=0; j<inQueue; j++) newQueue[j]=ceQueue[j];
          delete[] ceQueue;
          ceQueue=newQueue;
        }  
        if (subCE->ce->parents[0]==current.ce)
        {
          neighCE=subCE->ce->parents[1];
          if (((neighCE->flags & ipcCEInQueue)==0) && (neighCE->parents[0]==rootCE || neighCE->parents[1]==rootCE))
          {
            ceQueue[inQueue].pos=neighPos;
            ceQueue[inQueue].ce=neighCE;
            ceQueue[inQueue].ce->flags|=ipcCEInQueue;
            inQueue++;
          }
        }
        else 
        {
          neighCE=subCE->ce->parents[0];
          if (((neighCE->flags & ipcCEInQueue)==0) && (neighCE->parents[0]==rootCE || neighCE->parents[1]==rootCE))
          {
            ceQueue[inQueue].pos=neighPos;
            ceQueue[inQueue].ce=neighCE;
            ceQueue[inQueue].ce->flags|=ipcCEInQueue;
            inQueue++;
          }
        }
      }
      subCE=subCE->next;
    }
  }

  advAssert(inQueue<=rootCE->numOfSubCEs);

  numOfConnected=0;
  numOfRest=0;
  connectedList=NULL;
  restList=NULL;
  ipcSubCodeelement<ipcFeatureType>* lastOfRestList=NULL;
  ipcSubCodeelement<ipcFeatureType>* lastOfConnectedList=NULL;
  connectedForm=0;

  while (subCEList!=NULL)
  {
    if ((subCEList->ce->flags & ipcCEInQueue)!=0)
    {
      if (lastOfConnectedList==NULL) 
      {
        numOfConnected=1;
        lastOfConnectedList=connectedList=subCEList;
        connectedForm|=(1<<subCEList->pos);
      }
      else 
      {
        numOfConnected++;
        lastOfConnectedList->next=subCEList;
        lastOfConnectedList=lastOfConnectedList->next;
        connectedForm|=(1<<subCEList->pos);
      }
    }
    else
    {
      if (lastOfRestList==NULL) 
      {
        numOfRest=1;
        lastOfRestList=restList=subCEList;
      }
      else 
      {
        numOfRest++;
        lastOfRestList->next=subCEList;
        lastOfRestList=lastOfRestList->next;
      }
    }
    subCEList=subCEList->next;
  }
  if (lastOfConnectedList!=NULL) lastOfConnectedList->next=NULL;
  if (lastOfRestList!=NULL) lastOfRestList->next=NULL;

  for (i=0; i<inQueue; i++)
    ceQueue[i].ce->flags&=~ipcCEInQueue;
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::level1Repair(ipcCodeelement<ipcFeatureType>* rootCE, ipcSubCodeelement<ipcFeatureType>* subCEList, int &numOfConnected, ipcSubCodeelement<ipcFeatureType>* &connectedList, unsigned char &connectedForm, int &numOfRest, ipcSubCodeelement<ipcFeatureType>* &restList)
{
  int i,j,inQueue;
  //const ipcConnectedWithTable& connectedWithTable = hierarchy->getConnectedWithTable();
  const ipcCommonIslTable& commonIslTable = hierarchy->getCommonIslandTable(); 
  ipcSubCodeelement<ipcFeatureType> current;
  ipcSubCodeelement<ipcFeatureType>* searchCE;
  
  i=0;
  inQueue=1;
  ceQueue[0]=rootCE->subCEs[0];
  ceQueue[0].ce->flags|=ipcCEInQueue;
  while (i<inQueue)
  {
    current=ceQueue[i]; i++;
    searchCE=rootCE->subCEs;
    while (searchCE!=NULL)
    {
      if ((searchCE->ce->flags & ipcCEInQueue)==0
                 && ((current.ce->form & (1<<commonIslTable[current.pos][searchCE->pos]))!=0)
                 && ((searchCE->ce->form & (1<<commonIslTable[searchCE->pos][current.pos]))!=0))
      {
        if (inQueue>=maxQueue)
        {
          maxQueue*=2;
          ipcSubCodeelement<ipcFeatureType>* newQueue=new ipcSubCodeelement<ipcFeatureType>[maxQueue];
          for (j=0; j<inQueue; j++) newQueue[j]=ceQueue[j];
          delete[] ceQueue;
          ceQueue=newQueue;
        }  
        ceQueue[inQueue]=*searchCE;
        searchCE->ce->flags|=ipcCEInQueue;
        inQueue++;
      }
      searchCE=searchCE->next;
    }
  }

  advAssert(inQueue<=rootCE->numOfSubCEs);

  numOfConnected=0;
  numOfRest=0;
  connectedList=NULL;
  restList=NULL;
  ipcSubCodeelement<ipcFeatureType>* lastOfRestList=NULL;
  ipcSubCodeelement<ipcFeatureType>* lastOfConnectedList=NULL;
  connectedForm=0;

  while (subCEList!=NULL)
  {
    if ((subCEList->ce->flags & ipcCEInQueue)!=0)
    {
      if (lastOfConnectedList==NULL) 
      {
        numOfConnected=1;
        lastOfConnectedList=connectedList=subCEList;
        connectedForm|=(1<<subCEList->pos);
      }
      else 
      {
        numOfConnected++;
        lastOfConnectedList->next=subCEList;
        lastOfConnectedList=lastOfConnectedList->next;
        connectedForm|=(1<<subCEList->pos);
      }
    }
    else
    {
      if (lastOfRestList==NULL) 
      {
        numOfRest=1;
        lastOfRestList=restList=subCEList;
      }
      else 
      {
        numOfRest++;
        lastOfRestList->next=subCEList;
        lastOfRestList=lastOfRestList->next;
      }
    }
    subCEList=subCEList->next;
  }
  if (lastOfConnectedList!=NULL) lastOfConnectedList->next=NULL;
  if (lastOfRestList!=NULL) lastOfRestList->next=NULL;

  for (i=0; i<inQueue; i++)
    ceQueue[i].ce->flags&=~ipcCEInQueue;
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
int ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>::repair(const ipcIsland& island, ipcCodeelement<ipcFeatureType>* rootCE)
{
  ipcCodeelement<ipcFeatureType>* newCE = rootCE;
  ipcCodeelement<ipcFeatureType>* oldCE = rootCE;
  ipcCodeelement<ipcFeatureType>* parent1 = rootCE->parents[0];
  ipcCodeelement<ipcFeatureType>* parent2 = rootCE->parents[1];
  //int parent1Pos = 0;
  //int parent2Pos = 0;
  ipcSubCodeelement<ipcFeatureType>* connectedList;
  ipcSubCodeelement<ipcFeatureType>* restList;
  ipcSubCodeelement<ipcFeatureType>* subCE;
  ipcSubCodeelement<ipcFeatureType>* subCEInParent1 = NULL;
  ipcSubCodeelement<ipcFeatureType>* subCEInParent2 = NULL;
  int numOfConnected,numOfRest,degreeOfDisintegration=1;

  subCEInParent1=(parent1) ? ceBase->findSubCE(parent1,rootCE) : NULL;
  subCEInParent2=(parent2) ? ceBase->findSubCE(parent2,rootCE) : NULL;
  ceBase->reopenIsland(island);
  do
  {
    if (island.level>1)
      repair(newCE,newCE->subCEs,numOfConnected,connectedList,newCE->form,numOfRest,restList);
    else level1Repair(newCE,newCE->subCEs,numOfConnected,connectedList,newCE->form,numOfRest,restList);
    if (numOfConnected>1)
    {
      newCE->subCEs=connectedList;
      newCE->numOfSubCEs=numOfConnected;
      if (newCE!=rootCE) 
      {
        newCE->parents[0]=parent1;
        newCE->parents[1]=parent2;
        if (parent1!=NULL)
        {
          subCE=ceBase->getCurrentSubCEs();
          subCE->pos=subCEInParent1->pos;
          subCE->ce=newCE;
          subCE->next=parent1->subCEs;
          parent1->subCEs=subCE;;
          ceBase->storeCurrentSubCEs(1);
          parent1->numOfSubCEs++;
        }
        if (parent2!=NULL)
        {
          subCE=ceBase->getCurrentSubCEs();
          subCE->pos=subCEInParent2->pos;
          subCE->ce=newCE;
          subCE->next=parent2->subCEs;
          parent2->subCEs=subCE;;
          ceBase->storeCurrentSubCEs(1);
          parent2->numOfSubCEs++;
        }
        ceBase->storeCurrentCE(false);
        degreeOfDisintegration++;
      }
	    if (updateAfterSplitting) updateFeature(island.level+1,newCE);
      if (newCE->parents[0]==NULL && newCE->parents[1]==NULL)
        newCE->flags|=ipcCERoot;
      oldCE=newCE;
      newCE=ceBase->getCurrentCE();
      newCE->data=rootCE->data;
      newCE->form=rootCE->form;
      newCE->flags=rootCE->flags;
      newCE->numOfSubCEs=numOfRest;
      newCE->subCEs=restList;
      newCE->parents[0]=NULL;
      newCE->parents[1]=NULL;
      subCE=newCE->subCEs;
      while (subCE!=NULL)
      {
        advAssert(subCE->ce->parents[0]==oldCE || subCE->ce->parents[1]==oldCE);
        if (subCE->ce->parents[0]==oldCE) subCE->ce->parents[0]=newCE;
        else subCE->ce->parents[1]=newCE;
        subCE=subCE->next;
      }
    }
    else if (connectedList!=NULL)
    {
      newCE->subCEs=restList;
      newCE->numOfSubCEs=numOfRest;
      advAssert(connectedList->ce->parents[0]==newCE || connectedList->ce->parents[1]==newCE);
      if (connectedList->ce->parents[0]==newCE) connectedList->ce->parents[0]=NULL;
      else connectedList->ce->parents[1]=NULL;
      if (connectedList->ce->parents[0]==NULL && connectedList->ce->parents[1]==NULL) 
        connectedList->ce->flags|=ipcCERoot;
      degreeOfDisintegration++;
    }
  } while (restList!=NULL && newCE->subCEs==restList);
  if (rootCE->numOfSubCEs<=1)
  {
    if (parent1!=NULL) ceBase->removeSubCE(parent1,rootCE);
    if (parent2!=NULL) ceBase->removeSubCE(parent2,rootCE);
	  ceBase->removeCodeelement(island,rootCE);
  }
  if (degreeOfDisintegration>1)
  { 
    ipcIsland parentIsland;

    if (subCEInParent1!=NULL)
    {
      hierarchy->getParentIsland(island,subCEInParent1->pos,parentIsland);
      repair(parentIsland,parent1);
    }
    if (subCEInParent2!=NULL)
    {
      hierarchy->getParentIsland(island,subCEInParent2->pos,parentIsland);
      repair(parentIsland,parent2);
    }
  }
  return degreeOfDisintegration;
}

#endif
