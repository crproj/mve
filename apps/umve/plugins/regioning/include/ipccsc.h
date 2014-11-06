/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Lutz Priese, Volker Rehrman, Patrick Sturm

*/


#ifndef _ipccs_h_
#define _ipccs_h_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0
  
  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <adverror.h>
#include <ipcislhierarchy.h>
#include <ipccodebase.h>
#include <ipccscengine.h>
#include <ipccolor.h>
//#include <ipcstdrgblinkcontrol.h>
//#include <ipcstdhsvlinkcontrol.h>


/*! \brief The class ipcCSC is a compoment that encapsulate the csc algorithm.

It consists of the 3 subcomponents: island hierarchy, codeelement base and csc engine.
The class ipcCSC is a template class that expect three template arguments: ipcPixelType, ipcFeatureType and ipcLinkControl.

\li \c ipcPixelType describes the pixel format of the input image
\li \c ipcFeatureType describes the data format of codeelements. Normally \c ipcPixelType and \c ipcFeatureType are equivalent types.
\li \c ipcLinkControl is a module that controls how the csc should link codeelements together. Therefore
                      a link control class encapsulates a color similarity function and a averaging function. 
                      The standard link control classes are the ipcStdRGBLinkControl and the ipcStdHSVLinkControl class.
					  On can change the behaviour of the csc algorithm by implementing an own ipcLinkControlControl class.


\b Important \b restrictions:

\li The types ipcPixelType and ipcFeatureType must allow a copy operation:
\verbatim
ipcPixelType p1,p2;
ipcFeatureType f1,f2;

p1=p2; // <--- must be valid
f1=f2; // <--- must be valid
\endverbatim


\li A \c ipcLinkControl class has to satisfy the following interface:
\verbatim
  class ipcSampleLinkControl
  {
    ipcSampleLinkControl();
    inline void begin(int level, const ipcPixelType& pixel);
    inline bool add(const ipcPixelType& pixel1, const ipcPixelType& pixel2);
    inline void begin(int level, const ipcCodeelement<ipcFeatureType>* ce);
    inline bool add(const ipcCodeelement<ipcFeatureType>* ce1, const ipcCodeelement<ipcFeatureType>* ce2);
    inline void setFeature(ipcPixelType& avgColor);
    inline int compareFeatures(const ipcFeatureType& ce1, const ipcFeatureType& ce2, const ipcFeatureType& subCE);
  }
\endverbatim
*/
template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
class ipcCSC
{
private:
  ipcLinkControl* linkControl;
  ipcIslandHierarchy* hierarchy;
  ipcCodeelementBase<ipcFeatureType>* ceBase;
  ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>* cscEngine;
  double avgCEsPerIsland;
  ipcSplittingType splittingType;

  void init(int width, int height);

public:
  /*! The standard constructor tries to find the smallest island hierarchy that covers a "width x height"-raster 
      and initializes the three subcomponents (island hierarchy, codeelement base and csc engine).
      \param avgCEsPerIsland parameterized the size of the codeelement base
  */
  ipcCSC(int width = 0, int height = 0, double avgCEsPerIsland = 2.0, ipcSplittingType initSplittingType = ipcDirectSplitting);

  //! The destructor frees all subcomponents
  virtual ~ipcCSC();

  /*! \brief Applies the csc segmentation on the given image.

     \param w width of the source image
     \param h height of the source image
     \param srcImage source image. The source image has to be represented as
            an array with w*h fields of the type \c ipcPixelType.
     \param regImage pointer to an empty region image. The method writes the segmentation result into the
            region image. The region image has to be represented as an
            array with w*h fields of the type \c ipcFeatureType. Every pixel is mapped
            to the average color of the region he belongs to. 
  */
  void segmentation(int w, int h, const ipcPixelType* srcImage, ipcFeatureType* regImage = NULL, int minLevel=0, ipcRepairType repairType=ipcPreciseRepair);

  /*! \brief Applies the csc segmentation on the given source image.

     \param w width of the source image
     \param h height of the source image
     \param srcImage source image. The source image has to be represented as
            an array with w*h fields of the type \c ipcPixelType.
     \param roiX left x coordinate of region of interest.
     \param roiY upper y coordinate of region of interest.
     \param roiW width of the region of interest.
     \param roiH height of the region of interest.
     \param regImage pointer to an empty region image. The method writes the segmentation result into the
            region image. The region image has to be represented as an
            array with roiW*roiH fields of the type \c ipcFeatureType. Every pixel is mapped
            to the average color of the region he belongs to. 
  */    
  void segmentation(int w, int h, const ipcPixelType* srcImage, int roiX, int roiY, int roiW, int roiH, ipcFeatureType* regImage = NULL, int minLevel=0, ipcRepairType repairType=ipcPreciseRepair);

  /*! \brief Applies the csc segmentation on the given source image.

     \param w width of the source image
     \param h height of the source image
     \param srcImage source image. The source image has to be represented as
            an array with w*h fields of the type \c ipcPixelType.
     \param labeledImage pointer to an empty labeled image. The method writes the segmentation result into the
            labeled image. The labeled image has to be represented as an
            array with roiW*roiH fields of the type \c int. Every pixel is mapped
            to an integer label of the region he belongs to.
     \param ceMap codeelement map. The method maps an integer label to a codeelement and stores this association in the codeelement map.
  */    
  void segmentation(int w, int h, const ipcPixelType* srcImage, int* labeledImage, std::map<int,ipcCodeelementRef<ipcFeatureType> >& ceMap, int minLevel=0, ipcRepairType repairType=ipcPreciseRepair);

  /*! \brief Applies the csc segmentation on the given source image.

     \param w width of the source image
     \param h height of the source image
     \param srcImage source image. The source image has to be represented as
            an array with w*h fields of the type \c ipcPixelType.
     \param roiX left x coordinate of region of interest.
     \param roiY upper y coordinate of region of interest.
     \param roiW width of the region of interest.
     \param roiH height of the region of interest.
     \param labeledImage pointer to an empty labeled image. The method writes the segmentation result into the
            labeled image. The labeled image has to be represented as an
            array with roiW*roiH fields of the type \c int. Every pixel is mapped
            to an integer label of the region he belongs to.
     \param ceMap codeelement map. The method maps an integer label to a codeelement and stores this association in the codeelement map.
  */    
  void segmentation(int w, int h, const ipcPixelType* srcImage, int roiX, int roiY, int roiW, int roiH, int* labeledImage, std::map<int,ipcCodeelementRef<ipcFeatureType> >& ceMap, int minLevel=0, ipcRepairType repairType=ipcPreciseRepair);

  /*! \brief Applies the csc segmentation on the given source image.

     \param w width of the source image
     \param h height of the source image
     \param srcImage source image. The source image has to be represented as
            an array with w*h fields of the type \c ipcPixelType.
     \param labeledImage labeled image. The method writes the segmentation result into the
            labeled image. The labeled image has to be represented as an
            array with w*h fields of the type \c int. Every pixel is mapped
            to an integer label of the region he belongs to.
     \param featureMap feature map. The method maps an integer label to a feature vector and stores this association in the feature map.
  */    
  void segmentation(int w, int h, const ipcPixelType* srcImage, int* labeledImage, std::map<int,ipcFeatureType>& featureMap, int minLevel=0, ipcRepairType repairType=ipcPreciseRepair);

  /*! \brief Applies the csc segmentation on the given source image.

     \param w width of the source image
     \param h height of the source image
     \param srcImage source image. The source image has to be represented as
            an array with w*h fields of the type \c ipcPixelType.
     \param roiX left x coordinate of region of interest.
     \param roiY upper y coordinate of region of interest.
     \param roiW width of the region of interest.
     \param roiH height of the region of interest.
     \param labeledImage labeled image. The method writes the segmentation result into the
            labeled image. The labeled image has to be represented as an
            array with roiW*roiH fields of the type \c int. Every pixel is mapped
            to an integer label of the region he belongs to.
     \param feantureMap feature map. The method maps an integer label to a feature vector and stores this association in the feature map.
  */    
  void segmentation(int w, int h, const ipcPixelType* srcImage, int roiX, int roiY, int roiW, int roiH, int* labeledImage, std::map<int,ipcFeatureType>& featureMap, int minLevel=0, ipcRepairType repairType=ipcPreciseRepair);

  //! \returns the current island hierarchy.
  inline const ipcIslandHierarchy* getIslandHierarchy() const;

  //! \returns the current codeelement base.
  inline ipcCodeelementBase<ipcFeatureType>* getCEBase() const;

  //! \returns the current link control object
  inline ipcLinkControl* getLinkControl() const;

  inline int getNumOfDisintegratedCEs() const { return (cscEngine!=NULL) ? cscEngine->getNumOfDisintegratedCEs() : 0; };
};


// Implementation of ipcCSC
template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSC<ipcPixelType,ipcFeatureType,ipcLinkControl>::init(int width, int height)
{
  if (width<=0 || height<=0)
  {
    if (cscEngine!=NULL) delete cscEngine;
    if (ceBase!=NULL) delete ceBase;
    if (hierarchy!=NULL) delete hierarchy;
  }
  else
  {
    if (hierarchy==NULL)
    {
      hierarchy=new ipcIslandHierarchy(width,height);
      ceBase=new ipcCodeelementBase<ipcFeatureType>(*hierarchy,avgCEsPerIsland);
      cscEngine=new ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>(*ceBase,linkControl,splittingType);
    }
    else if (hierarchy->numberOfLevels()!=ipcIslandHierarchy::numberOfLevels(width,height))
    {
      if (cscEngine!=NULL) delete cscEngine;
      if (ceBase!=NULL) delete ceBase;
      if (hierarchy!=NULL) delete hierarchy;
      hierarchy=new ipcIslandHierarchy(width,height);
      ceBase=new ipcCodeelementBase<ipcFeatureType>(*hierarchy,avgCEsPerIsland);
      cscEngine=new ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>(*ceBase,linkControl,splittingType);
    }
  }
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
ipcCSC<ipcPixelType,ipcFeatureType,ipcLinkControl>::ipcCSC(int width, int height, double avgCEsPerIsland, ipcSplittingType initSplittingType)
{
  splittingType=initSplittingType;
  linkControl=new ipcLinkControl();
  hierarchy=NULL;
  ceBase=NULL;
  cscEngine=NULL;
  this->avgCEsPerIsland=avgCEsPerIsland;
  init(width,height);
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
ipcCSC<ipcPixelType,ipcFeatureType,ipcLinkControl>::~ipcCSC()
{
  if (cscEngine!=NULL) delete cscEngine;
  if (linkControl!=NULL) delete linkControl;
  if (ceBase!=NULL) delete ceBase;
  if (hierarchy!=NULL) delete hierarchy;
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSC<ipcPixelType,ipcFeatureType,ipcLinkControl>::segmentation(int w, int h, const ipcPixelType* srcImage, int roiX, int roiY, int roiW, int roiH, ipcFeatureType* regImage, int minLevel, ipcRepairType repairType)
{
  bool repeat;

  do
  { 
    repeat = false;
    try
    {
      init(w,h);
      advAssert(cscEngine!=NULL);
      cscEngine->setROI(roiX,roiY,roiW,roiH);
      cscEngine->changeRepairType(repairType);
      cscEngine->startSegmentation(w,h,srcImage);
      if (regImage) ceBase->drawRegionImage(roiX,roiY,roiW,roiH,regImage,minLevel);
    } 
    catch (ipcCodeelementBaseOverrun& /*exc*/)
    {
      avgCEsPerIsland*=2.0;
      if (ceBase!=NULL) delete ceBase;
      if (cscEngine!=NULL) delete cscEngine;
      ceBase=new ipcCodeelementBase<ipcFeatureType>(*hierarchy,avgCEsPerIsland);
      cscEngine=new ipcCSCEngine<ipcPixelType,ipcFeatureType,ipcLinkControl>(*ceBase,linkControl,splittingType);
      repeat=true;
    }
  } while (repeat);
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSC<ipcPixelType,ipcFeatureType,ipcLinkControl>::segmentation(int w, int h, const ipcPixelType* srcImage, ipcFeatureType* regImage, int minLevel, ipcRepairType repairType)
{
  segmentation(w,h,srcImage,0,0,w,h,NULL,0,repairType);
  if (regImage) ceBase->drawRegionImage(0,0,w,h,regImage,minLevel);
}
  
template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSC<ipcPixelType,ipcFeatureType,ipcLinkControl>::segmentation(int w, int h, const ipcPixelType* srcImage, int* labeledImage, std::map<int,ipcCodeelementRef<ipcFeatureType> >& ceMap, int minLevel, ipcRepairType repairType)
{
  segmentation(w,h,srcImage,0,0,w,h,NULL,0,repairType);
  if (labeledImage) ceBase->drawLabelImage(0,0,w,h,labeledImage,ceMap,minLevel);
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSC<ipcPixelType,ipcFeatureType,ipcLinkControl>::segmentation(int w, int h, const ipcPixelType* srcImage, int roiX, int roiY, int roiW, int roiH, int* labeledImage, std::map<int,ipcCodeelementRef<ipcFeatureType> >& ceMap, int minLevel, ipcRepairType repairType)
{
  segmentation(w,h,srcImage,0,0,w,h,NULL,0,repairType);
  if (labeledImage) ceBase->drawLabelImage(roiX,roiY,roiW,roiH,labeledImage,ceMap,minLevel);
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSC<ipcPixelType,ipcFeatureType,ipcLinkControl>::segmentation(int w, int h, const ipcPixelType* srcImage, int* labeledImage, std::map<int,ipcFeatureType>& featureMap, int minLevel, ipcRepairType repairType)
{
  segmentation(w,h,srcImage,0,0,w,h,NULL,0,repairType);
  if (labeledImage) ceBase->drawLabelImage(0,0,w,h,labeledImage,featureMap,minLevel);
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
void ipcCSC<ipcPixelType,ipcFeatureType,ipcLinkControl>::segmentation(int w, int h, const ipcPixelType* srcImage, int roiX, int roiY, int roiW, int roiH, int* labeledImage, std::map<int,ipcFeatureType>& featureMap, int minLevel, ipcRepairType repairType)
{
  segmentation(w,h,srcImage,0,0,w,h,NULL,0,repairType);
  if (labeledImage) ceBase->drawLabelImage(roiX,roiY,roiW,roiH,labeledImage,featureMap,minLevel);
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
inline const ipcIslandHierarchy* ipcCSC<ipcPixelType,ipcFeatureType,ipcLinkControl>::getIslandHierarchy() const
{
  return hierarchy;
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
inline ipcCodeelementBase<ipcFeatureType>* ipcCSC<ipcPixelType,ipcFeatureType,ipcLinkControl>::getCEBase() const
{
  return ceBase;
}


template <class ipcPixelType, class ipcFeatureType, class ipcLinkControl>
inline ipcLinkControl* ipcCSC<ipcPixelType,ipcFeatureType,ipcLinkControl>::getLinkControl() const
{
  /*if (cscEngine!=NULL)
    return &(cscEngine->getLinkControl());
  return NULL;*/
  return linkControl;
}

#endif
