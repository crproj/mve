/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Patrick Sturm

*/


#ifndef _advio_h_
#define _advio_h_

/***********************************************
  Advanced Input Output Classes Version 1.0
  
  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <iostream>
#include <string>
#include <set>


const int aioStreamBufferSize = 4096;

class aioStreamBuffer
{
private:
  char buffer[aioStreamBufferSize];
  int inBuffer,usedChars,count;
  std::istream* inputStream;
  bool endOfFile;

public:
  aioStreamBuffer(std::istream* input);
  virtual ~aioStreamBuffer();

  void pushCharacterBack();
  void synchronizeStream();
  void seek(int pos);
  char nextChar();
  int  seekPos();
  bool eof();

friend class aioStreamTokenizer;
};


enum aioToken {tokWhiteSpaces,tokWord,tokNumber,tokRealNumber,tokString,tokCharacter,tokComment,tokEOL,tokEOF,tokUnknown};

typedef std::set<aioToken> aioTokenSet;
typedef std::set<char> aioCharSet;

  
class aioStreamTokenizer
{
private:
  aioStreamBuffer streamBuffer;
  aioCharSet commentChars,ordinaryChars;
  aioCharSet wordChars,whiteSpaceChars;
  aioTokenSet ignoreTokSet;
  std::string currentValue;
  char currentChar;
  bool parseNumbers,parseRealNumbers;

  void readUpTo(aioCharSet& chars);
  void readChars(aioCharSet& chars);
  aioToken readRealNumber();

public:
  aioStreamTokenizer(std::istream* input);
  virtual ~aioStreamTokenizer();

  void enableParseNumbers(bool enable);
  void enableParseRealNumbers(bool enable);
  void setSingleLineCommentChars(const std::string& newCommentChars);
  void setOrdinaryChars(const std::string& newOrdinaryChars);
  void setWhiteSpaceChars(const std::string& newWhiteSpaceChars);
  void setWordCharacters(const std::string& newWordChars);
  void ignoreTokens(const aioTokenSet& newIgnoreTokSet);
  void synchronizeStream();
  aioToken nextToken();
  std::string getValue();
  int getCharCount();
  //int getLineNumber();
};


#endif
