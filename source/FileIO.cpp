////////////////////////////////////////////////////////////////////////////////
/*!
  @par    Project:GAM200 Game Engine
  @par    Course: GAM200
  @file   FileIO.cpp
  @author Jeremy Robert Anderson
  @par    email: janders2\@digipen.edu
  @date   October 4, 2008

  @brief
    The FileIO Class

  @brief  Copyright (C) 2008 DigiPen Institute of Technology.
*/
////////////////////////////////////////////////////////////////////////////////
#include "FileIO.h"
#include <sstream>

namespace FileIO
{

  FileConfig::FileConfig()
  {
  }

  bool FileConfig::Open( const std::string &filename )
  {
    filestr.open( filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary );
    if ( filestr.is_open() )
      return true;
    return false;
  }

  void FileConfig::GetData( std::string &Str )
  {
    char buffer[255] = {0};
    size_t Found;
    size_t Found2;

    filestr.getline( buffer, 255 );
    Str = buffer;

    while ( Str[0] == '!' || Str[0] == '\n' || Str[0] == '\r' )
    {
      filestr.getline( buffer, 255 );
      Str = buffer;
    }

    Found = Str.find_last_of( ":" ) + 1;
    Found2 = Str.find_last_of( ">" );

    Str = Str.substr( ++Found, Found2 - Found );
  }

  bool FileConfig::ToBool()
  {
    std::string Str;
    GetData( Str );

    for ( std::string::iterator it = Str.begin(), it2 = Str.end(); it != it2; ++it )
    {
      *it = tolower( *it );
    }

    if ( Str == "true" )
      return true;
    else
      return false;
  }

  int FileConfig::ToInt()
  {
    std::string Str;
    GetData( Str );
    return atoi( Str.c_str() );
  }

  float FileConfig::ToFloat()
  {
    std::string Str;
    GetData( Str );
    return atof( Str.c_str() );
  }

  std::string FileConfig::ToString()
  {
    std::string Str;
    GetData( Str );
    return Str;
  }

  Vector VectorFromString( std::string Str )
  {
    Vector temp;
    size_t Found;

    /*Found = Str.find_last_of( ":" ) + 1;
    Found2 = Str.find_last_of( ">" );*/

    Found = Str.find_first_of( ", " );

    std::string Str2 = Str.substr( 0, Found );
    temp.x = atof( Str2.c_str() );
    Str.erase( 0, Found + 2 );
    
    Found = Str.find_first_of( ", " );
    Str2 = Str.substr( 0, Found );
    temp.y = atof( Str2.c_str() );
    Str.erase( 0, Found + 2 );

    Found = Str.find_first_of( ", " );
    Str2 = Str.substr( 0, Found );
    temp.z = atof( Str2.c_str() );
    Str.erase( 0, Found + 2 );

    temp.w = atof( Str.c_str() );

    return temp;
  }

  Vector FileConfig::ToVector()
  {
    std::string Str;
    GetData( Str );
    return VectorFromString( Str );
  }

  void FileConfig::PutBool( std::string &Name, bool flag )
  {
    std::string Str;
    std::ostringstream out( std::ostringstream::out );
    out << "< bool Name = " << Name << " : " << ( flag ? "true" : "false" ) << ">";
    Str = out.str();
    PutData( Str );
  }

  void FileConfig::PutInt( std::string &Name, int value )
  {
    std::string Str;
    std::ostringstream out( std::ostringstream::out );
    out << "< int Name = " << Name << " : " << value << ">";
    Str = out.str();
    PutData( Str );
  }

  void FileConfig::PutString( std::string &Name, std::string &string )
  {
    std::string Str;
    std::ostringstream out( std::ostringstream::out );
    out << "< string Name = " << Name << " : " << string << ">";
    Str = out.str();
    PutData( Str );
  }

  void FileConfig::PutData( std::string &Str )
  {
    Str += "\r\n";
    filestr << Str;
  }

  FileConfig::~FileConfig()
  {
    if ( filestr.is_open() )
      filestr.close();
  }

}