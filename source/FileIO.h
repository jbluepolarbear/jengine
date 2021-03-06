#pragma once

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <fstream>
#include <string>
#include "Vec4.h"

namespace FileIO
{
  class FileConfig
  {
    public:
      FileConfig();
      virtual ~FileConfig();
      bool Open( const std::string &filename );
      bool ToBool();
      int  ToInt();
      float ToFloat();
      Vector ToVector();
      std::string ToString();
      void PutBool( std::string &Name, bool flag );
      void PutInt( std::string &Name, int value );
      void PutString( std::string &Name, std::string &string );
    private:
      void GetData( std::string &Str );
      void PutData( std::string &Str );
      std::fstream filestr;
  };
}