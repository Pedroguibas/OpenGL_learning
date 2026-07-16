#pragma once

class Vec3 {
  public:
    float x;
    float y;
    float z;
    Vec3();
    Vec3(float x, float y, float z);

};

class Vec4 {
public:
  float x;
  float y;
  float z;
  float w;
  Vec4();
  Vec4(float x, float y, float z);
  Vec4(float x, float y, float z, float w);
  Vec4(Vec3 &v);

};

class Mat4 {
  public: 
    float m[4][4];
    
    Mat4(float (&m)[4][4]);
    Mat4();
    Vec4 operator*(const Vec4& v);
    Mat4 operator*(const Mat4& m);
};

Mat4 rotationX(float deg);

Mat4 rotationY(float deg);

Mat4 rotationZ(float deg);

Mat4 translate(float x, float y, float z);
Mat4 translate(Vec3 v);

Mat4 scale(float x, float y, float z);
Mat4 scale(Vec3 v);

Vec3 cross(Vec3 a, Vec3 b);

Vec3 normalize(Vec3 v);