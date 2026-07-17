#include "mat.h"
#include <corecrt_math_defines.h>
#include <cmath>
using std::cos;
using std::sin;

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator-() const {
  return Vec3(
    -x,
    -y,
    -z
  );
}

Vec3 Vec3::operator-(const Vec3 &other) const {
  return Vec3(
    x - other.x,
    y - other.y,
    z - other.z
  );
}

Vec4::Vec4() : x(0), y(0), z(0), w(1) {}

Vec4::Vec4(float x, float y, float z) : x(x), y(y), z(z), w(1) {}

Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vec4::Vec4(Vec3 &v) : x(v.x), y(v.y), z(v.z), w(1) {}

Vec4 Mat4::operator*(const Vec4 &v) {
  float x, y, z, w;
  x = this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][2] * v.z + this->m[0][3] * v.w;
  y = this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][2] * v.z + this->m[1][3] * v.w;
  z = this->m[2][0] * v.x + this->m[2][1] * v.y + this->m[2][2] * v.z + this->m[2][3] * v.w;
  w = this->m[3][0] * v.x + this->m[3][1] * v.y + this->m[3][2] * v.z + this->m[3][3] * v.w;

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
    {1, 0, 0, 0},
    {0, cos(rad), -sin(rad), 0},
    {0, sin(rad), cos(rad), 0},
    {0, 0, 0, 1}
  };

  return Mat4(m);
}

Mat4 rotationY(float deg) {
  float rad = degToRad(deg);

  float m[4][4] = {
    {cos(rad), 0, sin(rad), 0},
    {0, 1, 0, 0},
    {-sin(rad), 0, cos(rad), 0},
    {0, 0, 0, 1}
  };

  return Mat4(m);
}

Mat4 rotationZ(float deg) {
  float rad = degToRad(deg);

  float m[4][4] = {
    {cos(rad), -sin(rad), 0, 0},
    {sin(rad), cos(rad), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };

  return Mat4(m);
}

Mat4 translate(Vec3 v) {
  Mat4 m;
  m.m[0][3] = v.x;
  m.m[1][3] = v.y;
  m.m[2][3] = v.z;
  return m;
}

Mat4 translate(float x, float y, float z) {
  Mat4 m;
  m.m[0][3] = x;
  m.m[1][3] = y;
  m.m[2][3] = z;
  return m;
}

Mat4 scale(Vec3 v) {
  Mat4 m;
  m.m[0][0] = v.x;
  m.m[1][1] = v.y;
  m.m[2][2] = v.z;
  return m;
}

Mat4 scale(float x, float y, float z) {
  Mat4 m;
  m.m[0][0] = x;
  m.m[1][1] = y;
  m.m[2][2] = z;
  return m;
}


Vec3 cross(Vec3 a, Vec3 b) {
  return Vec3(
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x
  );
}

Vec3 normalize(Vec3 v) {
  float length = sqrt(
    v.x * v.x +
    v.y * v.y +
    v.z * v.z
  );

  return Vec3(
    v.x / length,
    v.y / length,
    v.z / length
  );
}

float dot(Vec3 a, Vec3 b) {
  return a.x * b.x +
         a.y * b.y +
         a.z * b.z;
}
