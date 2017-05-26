#pragma once

#ifndef VEC3_H
#define VEC3_H

#include "Matrix.h"

class Vec3
{
public:
  //Vec3(){}
  Vec3( const float x = 0.0f, const float y = 0.0f, const float z = 0.0f );
  Vec3( float *rhs );

  Vec3 &operator =( const Vec3 &rhs );

  //operator float *();

  Vec3 operator -() const;
  Vec3 operator +( const Vec3 &rhs ) const;
  Vec3 operator +( const float rhs ) const;
  Vec3 operator -( const Vec3 &rhs ) const;
  Vec3 &operator +=( const Vec3 &rhs );
  Vec3 &operator -=( const Vec3 &rhs );
  Vec3 &operator /=( const float rhs );
  Vec3 operator /( const float rhs ) const;
  float operator *( const Vec3 &rhs ) const;
  Vec3 operator *( const float s ) const;

  Vec3 Normalize() const;
  Matrix Skew() const;

  Vec3 cross( const Vec3& Vec3 ) const;
  float dot( const Vec3& Vec3 ) const;
  float length( void ) const;
  float lengthSquared( void ) const;

  float x, y, z;
};

Vec3 operator *( const Matrix &lhs, const Vec3 &rhs );
Vec3 MatrixMulVector( const Matrix &lhs, const Vec3 &rhs );

Vec3 CrossProduct( const Vec3 &v1, const Vec3 &v2 );

float Distance( const Vec3 &lhs, const Vec3 &rhs );
float DistanceSquared( const Vec3 &lhs, const Vec3 &rhs );

#endif
