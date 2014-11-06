/* 

This "SOFTWARE" is a free software.

You are allowed to download, use, modify and redistribute this software.
The software is provided "AS IS" without warranty of any kind.

Copyright: University of Koblenz, Patrick Sturm

*/


#ifndef _advstr_h_
#define _advstr_h_

/***********************************************
  Advanced String Functions Version 1.0
  
  Copyright 2002, Patrick Sturm
************************************************/

// Include-Files
#include <string>
#include <map>
#include <list>

// Global variables
extern const char advPathDelimiter;
extern const char advPathSeparator;

// Prototypes
extern std::string advGetExtension(const std::string& filename);
extern std::string advChangeExtension(const std::string& filename, const std::string& newExtension);
extern std::string advGetPath(const std::string& filename);
extern std::string advGetFilename(const std::string& filename);
extern std::string advEnsureExtension(const std::string& filename, const std::string& extension);
extern bool advIsExtension(const std::string& filename, const std::string& extension);
extern std::string advRemoveExtension(const std::string& filename);
extern std::string advTrimLeft(const std::string& str);
extern std::string advTrimRight(const std::string& str);
extern std::string advTrim(const std::string& str);
extern std::string advLowerString(const std::string& str);
extern bool advExtractKeyAndValue(const std::string& str, std::string& key, std::string& value);
extern void advExtractKeyAndValue(const std::string& assignments, std::map<std::string,std::string>& keyMap);
extern void advExtractKeyAndValue(int argc, const char* argv[], std::map<std::string,std::string>& keyMap);
extern void advExtractSearchPaths(const std::string& searchPathsStr, std::list<std::string>& searchPaths);
extern std::string advGetFirstSuitablePath(const std::string& filename, const std::string& searchPaths);


#endif
