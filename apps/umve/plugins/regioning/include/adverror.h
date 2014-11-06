/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Patrick Sturm

*/


#ifndef _adverror_h_
#define _adverror_h_

/***********************************************
  iMAge pROcessing cLAsses Version 1.0
  
  Copyright 2002, Patrick Sturm
************************************************/


// Includes
#include <string>
#include <stdio.h>
//#include <strstream>
#include <exception>


// Definition: Exception Creation Macros
#define ADV_NEW_STD_EXCEPTION(CLASSNAME,DEFAULTMSG) ADV_NEW_SUB_EXCEPTION(CLASSNAME,advException,DEFAULTMSG)
#define ADV_NEW_SUB_EXCEPTION(CLASSNAME,INHERITFROM,DEFAULTMSG) class CLASSNAME: public INHERITFROM { public: CLASSNAME(const char* msg): INHERITFROM(msg) {}; CLASSNAME(): INHERITFROM(DEFAULTMSG) {}; };



//! Base exception class
/*! This class is the base class for all marola exceptions. The class saves a message std::string
containing a error message.

\author Patrick Sturm
*/
class advException: public std::exception
{
private:
  std::string message;

public:
  //! The constructor creates a new exception with message msg
  /*!
   \param msg message text
  */
  advException(const char* msg = "") {message=msg;};

  //! Destructor
  virtual ~advException() throw() {};

  //! The method changes the message text of the exception
  /*!
  \param msg new message text
  */
  void setMessage(const char* msg) {message=msg;};


  //! The method returns the message text of the exception
  const char* getMessageStr() const { return message.c_str(); };

  virtual const char* what() { return getMessageStr(); };
};


//! Exception of this type are thrown by advAssert.
/*! advAssert(cond) throws a exception of type advAssertion if condition cond is false.
\author Patrick Sturm
*/
class advAssertion: public advException
{
public:
  advAssertion(const char* cond, const char* file, int line)
  {
    char newMessage[2000];

    sprintf(newMessage,"Assertion (Cond[%s], File[%s], Line [%i]",cond,file,line);
    setMessage(newMessage);
    /*ostrstream msgStream;

    msgStream << "Assertion (Cond[" << cond << "], File[" << file << "], Line [" << line << "])" << ends;
    setMessage(msgStream.str());
    msgStream.freeze(false);*/
  };
};


extern void _advAssert(const char * __cond, const char * __file, int __line);


#ifdef advAssert
#undef advAssert
#endif

#ifdef NDEBUG
#define advAssert(p)   ((void)0)
#else
#define advAssert(p)   ((p) ? (void)0 : _advAssert(#p, __FILE__, __LINE__))
#endif


// Standard-Error-Exceptions
ADV_NEW_STD_EXCEPTION(advEFileNotFound,"File not found...");
ADV_NEW_STD_EXCEPTION(advEOutOfMemory, "Out of memory...");


#endif
