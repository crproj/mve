/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Patrick Sturm

*/


#ifndef _ipcmatrix_h_
#define _ipcmatrix_h_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0
  
  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <memory.h>
#include <stdlib.h>
#include <adverror.h>

/*! \class ipcMatrix
\brief This template class encapsulates a twodimensional matrix of any type (e.g. int, float, etc.).
\author Patrick Sturm
*/
template <class ElementType>
class ipcMatrix
{
private:
  ElementType* data;
  ElementType** index;
  int width,height,indexSize;
  bool ownsData;

private:
  inline void createIndex()
  {
    if (index!=NULL && height>indexSize)
    {
      delete[] index;
      index=NULL;
    }
    if (index==NULL && height>0)
    {
      indexSize=height;
      index=new ElementType*[height];
      index[0]=data;
      for (int y=1; y<height; y++)
        index[y]=index[y-1]+width;
    }
  };

public:
  //! Copy constructor
  /*! The copy constructor creates a new matrix and copies the content of m.
  \param m matrix that should be copied
  */
  ipcMatrix(const ipcMatrix& m)
  {
    width=m.width;
    height=m.height;
    data=new ElementType[width*height];
    memcpy(data,m.data,width*height*sizeof(ElementType));
    ownsData=true;
    index=NULL;
    createIndex();
  };


  /*! The constructor copies the content from newDataPtr and creates an matrix of size wxh.*/
  ipcMatrix(int w, int h, const ElementType* newDataPtr)
  {
    width=w;
    height=h;
    data=new ElementType[width*height];
    memcpy(data,newDataPtr,width*height*sizeof(ElementType));
    ownsData=true;
    index=NULL;
    createIndex();
  };


  //*! The constructor does not copy the content from newDataPtr. It just set the newDataPtr as the new content ptr.*/
  ipcMatrix(int w, int h, ElementType* newDataPtr, bool ownsDataPtr)
  {
    ownsData=ownsDataPtr;
    data=newDataPtr;
    width=w;
    height=h;
    index=NULL;
    createIndex();
  };


  //! The constructor creates a matrix with w*h fields
  /*! 
  \param w initialization width
  \param h initialization height
  */
  ipcMatrix(int w=0, int h=0)
  {
    if (w<=0 || h<=0)
    {
      width=0;
      height=0;
      data=NULL;
    }
    else
    {
      width=w;
      height=h;
      data=new ElementType[width*height];
    }
    ownsData=true;
    index=NULL;
    createIndex();
  };


  //! Destructor
  virtual ~ipcMatrix()
  {
    if (data!=NULL && ownsData) delete[] data;
    if (index!=NULL) delete[] index;
  };


  //! Changes the matrix data pointer
  void changeContent(int w, int h, ElementType* newDataPtr)
  {
    if (ownsData && data!=NULL) delete[] data;
    data=new ElementType[w*h];
    memcpy(data,newDataPtr,w*h*sizeof(ElementType));
    ownsData=true;
    width=w;
    height=h;
    createIndex();
  }


  //! Changes the matrix data pointer
  void changeContent(int w, int h, ElementType* newDataPtr, bool ownsDataPtr)
  {
    if (ownsData && data!=NULL) delete[] data;
    data=newDataPtr;
    ownsData=ownsDataPtr;
    width=w;
    height=h;
    createIndex();
  }



  //! The object releases the ownership of the content pointer, i.e. if the object is delete the content pointer stays valid.
  void release()
  {
    ownsData=false;
  }


  //! The object takes the ownership of the content pointer, i.e. if the object is deleted the content pointer will also be deleted.
  void freeze()
  {
    ownsData=true;
  }

  //! The method changes the size of the matrix to w*h
  /*!
   \warning the content of the matrix will be destroyed!
   \param w initialization width
   \param h initialization height
  */
  void resize(int w, int h)
  {
    if (ownsData)
    {
      if (w<=0 || h<=0)
      {
        width=0;
        height=0;
        if (data!=NULL) delete[] data;
        data=NULL;
        createIndex();
      }
      else if (width!=w || height!=h)
      {
        width=w;
        height=h;
        if (data!=NULL) delete[] data;
        data=new ElementType[width*height];
        createIndex();
      }
    }
  };


  //! Returns the number of fields
  inline int getNumberOfFields() const
  {
    return width*height;
  };


  //! Returns the width of the matrix
  inline int getWidth() const
  {
    return width;
  };


  //! Returns the height of the matrix
  inline int getHeight() const
  { 
    return height;
  };


  //! The Operator returns a reference on the i-th element of the matrix.
  inline ElementType& operator[] (int i)           
  {
    advAssert(data!=NULL && 0<=i && i<width*height);

    return data[i];
  };

  //! The Operator returns a reference on the i-th element of the matrix.
  inline const ElementType& operator[] (int i) const
  {
    advAssert(data!=NULL && i>=0 && i<width*height);

    return data[i];
  };


  //! The Operator returns a reference on the element at position (x,y) of the matrix.
  inline ElementType& operator() (int x, int y)
  {
    advAssert(data!=NULL && x>=0 && x<width && y>=0 && y<height);

    //return data[x+y*width];
    return index[y][x];
  };


  //! The method returns the value at index
  inline const ElementType& getField(int index) const
  {
    advAssert(data!=NULL && index>=0 && index<width*height);
    return data[index];
  };

  //! The method sets the field at position (x,y) to value val.
  inline void setField(int index, const ElementType& val)
  {
    advAssert(data!=NULL && index>=0 && index<width*height);
    data[index]=val;
  };

  //! The method returns the value at position (x,y)
  inline const ElementType& getField(int x, int y) const
  {
    //return data[x+y*width];
    return index[y][x];
  };

  //! The method sets the field at position (x,y) to value val.
  inline void setField(int x, int y, const ElementType& val)
  {
    //data[x+y*width]=val;
    index[y][x]=val;
  };

  //! The Operator returns a reference on the element at position (x,y) of the matrix.
  inline const ElementType& operator() (int x, int y) const
  {
    advAssert(data!=NULL && x>=0 && x<width && y>=0 && y<height);

    //return data[x+y*width];
    return index[y][x];
  };

  inline void getFieldRefs(int coordNum, const int xcoord[], const int ycoord[], const ElementType* values[], bool avail[]) const
  {
    for (int i=0; i<coordNum; i++)
    {
      if (xcoord[i]>=0 && ycoord[i]>=0 && xcoord[i]<width && ycoord[i]<height)
      {
        //values[i]=&(data[xcoord[i]+ycoord[i]*width]);
        values[i]=&(index[ycoord[i]][xcoord[i]]);
        avail[i]=true;
      }
      else avail[i]=false;
    }
  };

  //! \result Direct pointer to the data array of the matrix
  inline ElementType* getContentPtr()
  {
    return data;
  };

  //! \result Direct pointer to the index array of the matrix
  inline ElementType** getIndexPtr()
  {
    return index;
  };

  //! \result Direct pointer to the data array of the matrix
  inline operator ElementType* ()
  {
    return data;
  };

  //! \result Direct pointer to the data array of the matrix
  inline operator const ElementType* () const
  {
    return data;
  };

  //! \result Direct pointer to the index array of the matrix
  inline operator ElementType** ()
  {
    return index;
  };

  //! \result Direct pointer to the index array of the matrix
  inline operator const ElementType** () const
  {
    return index;
  };

  //! \result Direct pointer to the data array of the matrix
  inline const ElementType* getContentPtr() const
  {
    return data;
  };

  //! \result Direct pointer to the index array of the matrix
  inline const ElementType** getIndexPtr() const
  {
    return index;
  };
};

#endif
