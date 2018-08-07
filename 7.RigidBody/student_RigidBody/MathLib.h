
#ifndef _MATHLIB_H
#define _MATHLIB_H

#include<D3dx9math.h>
#include<assert.h>

#define ZERO 0.000001f;


class Vector3D {
    
public:
	float x;
	float y;
	float z;
	Vector3D();
	Vector3D(float a,float b, float c);
	
	Vector3D(const Vector3D& V); // COPY CONSTRUCTOR
	Vector3D& operator =(const Vector3D& V);
    Vector3D& operator +=( Vector3D V);
    Vector3D& operator -=( Vector3D V);
	Vector3D& operator *=(float k);
	Vector3D& operator /=(float k);
	Vector3D  operator -();
 	float Norm();	
    Vector3D Normalize()const;
	float  NormSquared();
	D3DXVECTOR3 ConvertToD3DXVector();
    
    
};// end class Vector3D


     Vector3D operator+( Vector3D U , Vector3D V);
	 Vector3D  operator-( Vector3D U , Vector3D V );
	 Vector3D  operator*( Vector3D V,  float k);
	 Vector3D  operator*( float k   ,  Vector3D V);
	 float     operator*( Vector3D U , Vector3D V );
	 Vector3D  operator/(Vector3D V , float k);
	 Vector3D  operator^(Vector3D U , Vector3D V );
	 float     Component( Vector3D U , Vector3D V);
	 Vector3D  Projection( Vector3D U , Vector3D V);
	 
   




////////////////////////////////////////Matrix class definition////////////////////////////////////////////////////


class Matrix3D {

public :
	    float m11,m12,m13,
			  m21,m22,m23,
			  m31,m32,m33;
		Matrix3D();
		Matrix3D(float a11,float a12,float a13,
			     float a21,float a22,float a23,
				 float a31,float a32,float a33);
		
	    Matrix3D(const Matrix3D& M);// COPY CONSTRUCTOR
        Matrix3D&  operator=(const Matrix3D& M);
		Matrix3D& operator+=(Matrix3D M);
		Matrix3D& operator-=(Matrix3D M);
		Matrix3D& operator*=(float k);
		Matrix3D& operator/=(float k);
		
		Matrix3D Transpose()const;
	    Matrix3D Orthonormalize();
		float    Trace();
	    Matrix3D Inverse();
		float Determinant();
		D3DXMATRIX ConvertToD3DXMatrix();
};

          Matrix3D operator +( Matrix3D M, Matrix3D N);
		  Matrix3D operator -( Matrix3D M, Matrix3D N);
		  Matrix3D operator *( Matrix3D M, Matrix3D N);
		  Vector3D operator *(Matrix3D M,Vector3D V);
		  Vector3D operator *(Vector3D V, Matrix3D m);
		  Matrix3D operator *(Matrix3D M,float k);
		  Matrix3D operator *(float k, Matrix3D M); 
		  Matrix3D operator /( Matrix3D M , float k); 
		  Matrix3D Skew(Vector3D M);
		  Matrix3D Identity();
		



/////////////////////////////////Quaternion class Definition////////////////////////////////////////////////////

class Quaternion {

public:
	float    w ; // real part
	Vector3D v ; // Vector3D part 
	Quaternion();
	Quaternion(float a,float b,float c,float d);
	Quaternion(float a , Vector3D vec);
	Quaternion(const Quaternion & q);
    Quaternion& operator=(const Quaternion& q);
	Quaternion& operator +=(Quaternion q);
	Quaternion& operator -=(Quaternion q);
	Quaternion& operator *=(float k);
	Quaternion& operator /=(float k);
	Quaternion operator~()const;
	float Norm();
	Quaternion Normalize();
	Quaternion Inverse()const;
    Vector3D GetVector();
	float GetScalar();

	/*to be done 
	 Vector3D   GetAxis();
	 float      GetAngle(); 
	 float      GetRotationAngle();
	 Vector3D   GetRotationAxis();
	 Quaternion QuaternionFromEuler();
	 Vector3D   EulerFromQuaternion();
	 Quaternion QuaternionRotation();

    */
    
	
};

	 Quaternion operator+(const Quaternion q1 ,const Quaternion q2);
	 Quaternion operator-(const Quaternion q1 ,const Quaternion q2);
	 Quaternion operator*(const Quaternion q1 ,const Quaternion q2);
	 Quaternion operator*(float     k         ,const Quaternion q);
	 Quaternion operator*(const Quaternion q  ,float     k       );
	 Quaternion operator/(const Quaternion q  ,float     k       );
	 float Dot(Quaternion q1 , Quaternion q2);
	 Quaternion VectorToQuaternion(Vector3D v);
	 Quaternion MatrixToQuaternion(Matrix3D M);
	 Quaternion Slerp(float t, Quaternion q0, Quaternion q1);


#endif
