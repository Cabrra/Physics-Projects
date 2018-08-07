
#ifndef _MATHLIB_H
#define _MATHLIB_H

#include<D3dx9math.h>
#include<assert.h>

#define TOLERANCE 0.001f;


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
		



/////////////////////////////////Quaternion class Definition////////////////////////////////////////////////////

class quaternion {

public:
	float    w ; // real part
	Vector3D v ; // Vector3D part 
	quaternion();
	quaternion(float a,float b,float c,float d);
	quaternion(float a , Vector3D vec);
	quaternion(const quaternion & q);
    quaternion& operator=(const quaternion& q);
	quaternion& operator +=(quaternion q);
	quaternion& operator -=(quaternion q);
	quaternion& operator *=(float k);
	quaternion& operator /=(float k);
	quaternion operator~()const;
	float Norm();
	float Dot(quaternion q1 , quaternion q2);
	quaternion Inverse()const;
    Vector3D GetVector3D();
	float GetScalar();
	//to be done
	/*inline quaternion Vector3DToQuaternion();
	 Vector3D   GetAxis();
	 float      GetAngle();
	 Matrix3D   QuaternionToMatrix();
	 Matrix3D   MatrixToQuaternion();
	 float      GetRotationAngle();
	 Vector3D   GetRotationAxis();
	 quaternion QuaternionFromEuler();
	 Vector3D   EulerFromQuaternion();
	 quaternion QuaternionRotation();

    
    */
	
};

	 quaternion operator+(const quaternion q1 ,const quaternion q2);
	 quaternion operator-(const quaternion q1 ,const quaternion q2);
	 quaternion operator*(const quaternion q1 ,const quaternion q2);
	 quaternion operator*(float     k         ,const quaternion q);
	 quaternion operator*(const quaternion q  ,float     k       );
	 quaternion operator/(const quaternion q  ,float     k       );


#endif
