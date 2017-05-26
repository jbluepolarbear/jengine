////////////////////////////////////////////////////////////////////////////////
/*!
  @par    Project:GAM300 Game Engine
  @par    Course: GAM300
  @file   FileIO.h
  @author Jeremy Robert Anderson
  @par    email: janders2\@digipen.edu
  @date   October 4, 2009

  @brief
    The FileIO Class

  @brief  Copyright (C) 2009 DigiPen Institute of Technology.
*/
////////////////////////////////////////////////////////////////////////////////
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