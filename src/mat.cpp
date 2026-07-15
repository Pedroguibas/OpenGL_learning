#include "mat.h"
#include <corecrt_math_defines.h>
#include <cmath>
using std::cos;
using std::sin;

Vec4::Vec4() {
  this->x = 0;
  this->y = 0;
  this->z = 0;
  this->w = 1;
}
Vec4::Vec4(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = 1;
}
Vec4::Vec4(float x, float y, float z, float w) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

Vec4 Mat4::operator*(const Vec4 &v) {
  float x, y, z, w;
  x = this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][2] * v.z + this->m[0][3] * v.w;
  y = this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][2] * v.z + this->m[1][3] * v.w;
  z = this->m[2][0] * v.x + this->m[2][1] * v.y + this->m[2][2] * v.z + this->m[2][3] * v.w;

  return Vec4(x, y, z, w);
}


Mat4 Mat4::operator*(const Mat4& m) {
  Mat4 result;
  for (int i=0; i<4; i++) {
    for (int j=0; j<4; j++) {
      result.m[i][j] = 0;
      for (int k=0; k<4; k++) {
        result.m[i][j] += this->m[i][k] * m.m[k][j]; 
      }
    }
  }

  return result;
}

Mat4::Mat4(float (&m)[4][4]) {
  for (int i=0; i<4; i++) {
    for (int j=0; j<4; j++) {
      this->m[i][j] = m[i][j];
    }
  }
}
Mat4::Mat4() {
  for (int i=0; i<4; i++) {
    for (int j=0; j<4; j++) {
      if (i == j) {
        this->m[i][j] = 1;
      } else {  
        this->m[i][j] = 0;
      }
    }
  }
}

float degToRad(float deg) {
  return deg * M_PI / 180;
}

Mat4 rotationX(float deg) {
  float rad = degToRad(deg);

  float m[4][4] = {
    {1, 0, 0},
    {0, cos(rad), -sin(rad)},
    {0, sin(rad), cos(rad)}
  };

  return Mat4(m);
}

Mat4 rotationY(float deg) {
  float rad = degToRad(deg);

  float m[4][4] = {
    {cos(rad), 0, sin(rad)},
    {0, 1, 0},
    {-sin(rad), 0, cos(rad)}
  };

  return Mat4(m);
}

Mat4 rotationZ(float deg) {
  float rad = degToRad(deg);

  float m[4][4] = {
    {cos(rad), -sin(rad), 0},
    {sin(rad), cos(rad), 0},
    {0, 0, 1}
  };

  return Mat4(m);
}