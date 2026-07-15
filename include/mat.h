#pragma once

class Vec4 {
public:
  float x;
  float y;
  float z;
  float w;
  Vec4();
  Vec4(float x, float y, float z);
  Vec4(float x, float y, float z, float w);

  
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
