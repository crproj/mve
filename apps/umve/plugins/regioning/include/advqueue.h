#ifndef _advqueue_h_
#define _advqueue_h_

/***********************************************
  Advanced Container Classes Version 1.0
  
  Copyright 2002, Patrick Sturm
************************************************/


// Include-Files
#include <adverror.h>


// Exceptions
ADV_NEW_STD_EXCEPTION(advEEmptyQueue, "Queue is empty...");
ADV_NEW_STD_EXCEPTION(advESizeTooSmall, "Size is too small...");


template <class advElementType>
class advQueue
{
protected:
  advElementType* data;
  int size,delta;
  int first,last,count;
public:
  advQueue(int initSize=0, int initDelta = -1);
  virtual ~advQueue();

  inline void init(int initSize, int initDelta = -1);
  inline void resize(int initSize);
  inline void enqueue(const advElementType& element);
  inline void dequeue();
  inline const advElementType& current() const;
  inline int numOfElements() const;
  inline void clear() const;
  inline bool isEmpty() const;
};


// Implementation of advVector
template <class advElementType>
inline advQueue<advElementType>::advQueue(int initSize, int initDelta)
{
  data=new advElementType[initSize];
  size=initSize;
  if (initDelta>=0) delta=initDelta;
  else delta=initSize;
  first=0;
  last=0;
  count=0;
}


template <class advElementType>
advQueue<advElementType>::~advQueue()
{
  if (data!=NULL) delete[] data;
}


template <class advElementType>
inline void advQueue<advElementType>::init(int initSize, int initDelta)
{
  if (data!=NULL) delete[] data;
  data=new advElementType[initSize];
  size=initSize;
  delta=initDelta;
  first=0;
  last=0;
  count=0;
}


template <class advElementType>
inline void advQueue<advElementType>::resize(int initSize)
{
  if (initSize>=count)
  {
    advElementType* newData = new advElementType[initSize];

    if (newData==NULL) throw advEOutOfMemory();
    if (first<last)
      memcpy(newData,&(data[first]),count*sizeof(advElementType));
    else if (count>0)
    {
      memcpy(newData,&(data[first]),(size-first)*sizeof(advElementType));
      memcpy(&(newData[size-first]),data,last*sizeof(advElementType));
    }
    first=0;
    last=count;
    size=initSize;
    delete[] data;
    data=newData;
  }
  else throw advESizeTooSmall();
}


template <class advElementType>
inline void advQueue<advElementType>::enqueue(const advElementType& element)
{
  if (count>=size) resize(size+delta);
  data[last]=element;
  count++;
  last++;
  if (last>=size) last=0;
}


template <class advElementType>
inline void advQueue<advElementType>::dequeue()
{
  if (count==0) throw advEEmptyQueue();
  count--;
  first++;
  if (first>=size)
  {
    first=0;
    last=first+count;
  }
}


template <class advElementType>
inline const advElementType& advQueue<advElementType>::current() const
{
  if (count==0) throw advEEmptyQueue();
    
  return data[first];
}


template <class advElementType>
inline int advQueue<advElementType>::numOfElements() const
{
  return count;
}


template <class advElementType>
inline void advQueue<advElementType>::clear() const
{
  first=0;
  last=0;
  count=0;
}


template <class advElementType>
inline bool advQueue<advElementType>::isEmpty() const
{
  return (count==0);
}


#endif
