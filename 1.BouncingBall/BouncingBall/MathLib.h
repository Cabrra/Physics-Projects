
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
	
	inline Vector3D(const Vector3D& V); // COPY CONSTRUCTOR
	inline Vector3D& operator =(const Vector3D& V);
	inline Vector3D& operator+=( Vector3D V);
	inline Vector3D& operator-=( Vector3D V);
	inline Vector3D& operator*=(float k);
	inline Vector3D& operator/=(float k);
    Vector3D  operator- ();
	
	operator  D3DXVECTOR3(); 
 	float Norm();	
	inline Vector3D Normalize()const;
	inline  float  NormSquared();
    
    
};// end class Vector3D


     Vector3D operator+( Vector3D U , Vector3D V);
	 Vector3D  operator-( Vector3D U , Vector3D V );
	 Vector3D  operator*( Vector3D V,  float k);
	 Vector3D  operator*( float k   ,  Vector3D V);
	 float     operator*( Vector3D U , Vector3D V );
	 bool operator==(Vector3D U , Vector3D V);

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
		inline Matrix3D& operator+=(Matrix3D M);
		inline Matrix3D& operator-=(Matrix3D M);
		inline Matrix3D& operator*=(float k);
		inline Matrix3D& operator/=(float k);
		
		inline Matrix3D Transpose()const;
		inline Matrix3D Orthonormalize();
		inline float    Trace();
		inline Matrix3D Inverse();
		inline float Determinant();
		operator D3DXMATRIX();
};

          Matrix3D operator +( Matrix3D M, Matrix3D N);
		  Matrix3D operator -( Matrix3D M, Matrix3D N);
		  Matrix3D operator *( Matrix3D M, Matrix3D N);
		  Vector3D operator *(Matrix3D M,Vector3D V);
		  Vector3D operator *(Vector3D V, Matrix3D m);
		  Matrix3D operator *(Matrix3D M,float k);
		  Matrix3D operator *(float k, Matrix3D M); 
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
	inline quaternion& operator=(const quaternion& q);
	inline quaternion& operator +=(quaternion q);
	inline quaternion& operator -=(quaternion q);
	inline quaternion& operator *=(float k);
	inline quaternion& operator /=(float k);
	inline quaternion operator~()const;
	inline float Norm();
	inline float Dot(quaternion q1 , quaternion q2);
	inline quaternion Inverse()const;
    inline Vector3D GetVector3D();
	inline float GetScalar();
	//to be done
	/*inline quaternion Vector3DToQuaternion();
	inline Vector3D   GetAxis();
	inline float      GetAngle();
	inline Matrix3D   QuaternionToMatrix();
	inline Matrix3D   MatrixToQuaternion();
	inline float      GetRotationAngle();
	inline Vector3D   GetRotationAxis();
	inline quaternion QuaternionFromEuler();
	inline Vector3D   EulerFromQuaternion();
	inline quaternion QuaternionRotation(); ?????

    
    */
	
};

	 quaternion operator+(const quaternion q1 ,const quaternion q2);
	 quaternion operator-(const quaternion q1 ,const quaternion q2);
	 quaternion operator*(const quaternion q1 ,const quaternion q2);
	 quaternion operator*(float     k         ,const quaternion q);
	 quaternion operator*(const quaternion q  ,float     k       );
	 quaternion operator/(const quaternion q  ,float     k       );


#endif
