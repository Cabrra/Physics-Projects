
#include"MathLib.h"




Vector3D::Vector3D()
{ 
	x=0.0f;
    y=0.0f;
	z=0.0f;
}  

 Vector3D::Vector3D(float a , float b , float c)
{
	x=a;
	y=b;
	z=c;
    
}


 Vector3D::Vector3D(const Vector3D& V)
{
	x=V.x;
	y=V.y;
	z=V.z;
}




inline Vector3D& Vector3D::operator =(const Vector3D& V)  
{
	x=V.x;
	y=V.y;
	z=V.z;
	return *this;
}


 float Vector3D::Norm() 
{   // norm=length=magnitude
	
	return sqrt(x*x + y*y + z*z);
}


inline float Vector3D::NormSquared()
{
	return(x*x + y*y + z*z);
}


inline Vector3D& Vector3D::operator *=(float k)
{
       x*=k;
	   y*=k;
	   z*=k;
	   return *this;
}

inline Vector3D& Vector3D::operator +=( Vector3D V)
{
	x += V.x;
	y += V.y;
	z += V.z;
    return *this;
}


inline Vector3D& Vector3D::operator -=( Vector3D V )
{
	x-=V.x;
	y-=V.y;
	z-=V.z;
	return *this;
}


 Vector3D Vector3D::operator -()
{
	 return Vector3D(-x,-y,-z);
}


inline Vector3D& Vector3D::operator /=(float k)
{
	assert(k!=0.0f);
	x/=k;
	y/=k;
	z/=k;
	return *this;
}


inline Vector3D Vector3D::Normalize()const
{
	float m=sqrt(x*x+y*y+z*z);
	//assert(m!=0.0f);
	return(Vector3D(x/m,y/m,z/m));
}

inline Vector3D::operator D3DXVECTOR3()
{
return D3DXVECTOR3(x,y,z);
}



 Vector3D operator *(float k, Vector3D V)
{
	
  return Vector3D(k*V.x , k*V.y , k*V.z);
}


Vector3D  operator* ( Vector3D V , float k)
{
	return Vector3D(V.x*k , V.y*k , V.z*k) ;
}


 Vector3D operator +( Vector3D U,  Vector3D V)
{
	return Vector3D( U.x + V.x ,U.y + V.y ,U.z + V.z);

}

 bool operator ==(Vector3D U , Vector3D V)
{
	bool check=false;
	if(U.x==V.x && U.y==V.y && U.z==V.z ) check=true;
	return check;
}



 Vector3D operator -( Vector3D U, Vector3D V)
{
	return Vector3D( U.x - V.x ,U.y - V.y , U.z - V.z );
}

 float  operator *( Vector3D U , Vector3D V )
{
	return (float)(U.x*V.x + U.y*V.y + U.z*V.z );
}





 Vector3D  operator/( Vector3D V , float k)
{
    assert(k!=0.0f);
	return Vector3D(V.x/k , V.y/k , V.z/k );
}

 Vector3D  operator^( Vector3D U , Vector3D V )
{
	  return Vector3D(U.y*V.z - U.z*V.y , U.z*V.x - U.x*V.z , U.x*V.y - U.y*V.x);
}


// The component of u onto v
 float Component( Vector3D U , Vector3D V)
{

	return(U*V.Normalize());
}

 Vector3D  Projection( Vector3D U , Vector3D V)
{
	return( Component(U,V)*V.Normalize());
}



////////////////////////////////////////////////////////end Vector3D implementation////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////begin Matrix3D/////////////////////////////////////////////////////////////


Matrix3D::Matrix3D()
{
	m11=m12=m13=0.0f;
	m21=m22=m23=0.0f;
	m31=m32=m33=0.0f;
}

Matrix3D::Matrix3D(float a11,float a12,float a13,
			       float a21,float a22,float a23,
				   float a31,float a32,float a33)
{
	m11=a11 ; m12=a12 ; m13=a13;
	m21=a21 ; m22=a22 ; m23=a23;
	m31=a31 ; m32=a32 ; m33=a33;
}

 Matrix3D::Matrix3D(const Matrix3D & M)
{
   m11=M.m11 ; m12=M.m12 ; m13=M.m13;
   m21=M.m21 ; m22=M.m22 ; m23=M.m23;
   m31=M.m31 ; m32=M.m32 ; m33=M.m33;
}

 Matrix3D& Matrix3D::operator =(const Matrix3D& M)
{
   m11=M.m11 ; m12=M.m12 ; m13=M.m13;
   m21=M.m21 ; m22=M.m22 ; m23=M.m23;
   m31=M.m31 ; m32=M.m32 ; m33=M.m33;
   return *this;
}

inline Matrix3D& Matrix3D::operator *=(float k)
{
	m11*=k; m12*=k; m13*=k;
	m21*=k; m22*=k; m23*=k;
	m31*=k; m32*=k; m33*=k;
	return *this;
}

inline Matrix3D& Matrix3D::operator +=(Matrix3D M)
{
	m11+=M.m11 ; m12+=M.m12 ; m13+=M.m13;
	m21+=M.m21 ; m22+=M.m22 ; m23+=M.m23;
	m31+=M.m31 ; m32+=M.m32 ; m33+=M.m33;
	return *this;
}

inline Matrix3D& Matrix3D::operator -=(Matrix3D M )
{
   m11-=M.m11 ; m12-=M.m12 ; m13-=M.m13;
   m21-=M.m21 ; m22-=M.m22 ; m23-=M.m23;
   m31-=M.m31 ; m32-=M.m32 ; m33-=M.m33;
	return *this;
}

inline Matrix3D& Matrix3D::operator /=(float k )
{
    assert(k!=0.0f);
	m11/=k; m12/=k; m13/=k;
	m21/=k; m22/=k; m23/=k;
	m31/=k; m32/=k; m33/=k;
	return *this;
}



inline Matrix3D Matrix3D::Transpose()const{
	return Matrix3D(m11,m21,m31,
		            m12,m22,m32,
					m13,m23,m33);
}

inline float Matrix3D::Determinant()
{
	return( m11*(m22*m33-m23*m32) - m12*(m21*m33-m31*m23)+ m13*(m21*m32-m31*m22));
}

inline Matrix3D Matrix3D::Inverse(){
	
	//Matrix3D Adjoint ; // adjoint matrix
	//float c11,c12,c13,c21,c22,c23,c31,c32,c33; 

	return Matrix3D() ;//Adjoint.Transpose()/Adjoint.det();
}


inline Matrix3D Matrix3D::Orthonormalize()
{
   Vector3D V,U,W;
   V=Vector3D(m11,m21,m31);
   U=Vector3D(m12,m22,m32);
   V.Normalize();
   U=V-Projection(U,V);
   U.Normalize();
   W=V^U;
   m11=V.x ; m12=U.x ; m13=W.x ;
   m21=V.y ; m22=U.y ; m23=W.y ;
   m31=V.z ; m32=U.z ; m33=W.z ;

   return *this;
}





 Matrix3D operator +( Matrix3D M , Matrix3D N)
{

	return Matrix3D(  M.m11 + N.m11 , M.m12 + N.m12 , M.m13 + N.m13 ,
		              M.m21 + N.m21 , M.m22 + N.m22 , M.m23 + N.m23 ,
					  M.m31 + N.m31 , M.m32 + N.m32 , M.m33 + N.m33);
}

		  
 Matrix3D operator -( Matrix3D M, Matrix3D N)
{
	return Matrix3D(  M.m11 - N.m11 , M.m12 - N.m12 , M.m13 - N.m13 ,
		              M.m21 - N.m21 , M.m22 - N.m22 , M.m23 - N.m23 ,
					  M.m31 - N.m31 , M.m32 - N.m32 , M.m33 - N.m33);
}

 Matrix3D operator *( Matrix3D M, Matrix3D N)
{
	return Matrix3D( M.m11*N.m11 + M.m12*N.m21 + M.m13*N.m31, 
		             M.m11*N.m12 + M.m12*N.m22 + M.m13*N.m32,
					 M.m11*N.m13 + M.m12*N.m23 + M.m13*N.m33,

					 M.m21*N.m11 + M.m22*N.m21 + M.m23*N.m31,
					 M.m21*N.m12 + M.m22*N.m22 + M.m23*N.m32,
					 M.m21*N.m13 + M.m22*N.m23 + M.m23*N.m33,

					 M.m31*N.m11 + M.m32*N.m21 + M.m33*N.m31,
					 M.m31*N.m12 + M.m32*N.m22 + M.m33*N.m32,
					 N.m31*N.m13 + M.m32*N.m23 + M.m32*N.m33);
}

  Vector3D operator *(Matrix3D M,Vector3D V)
{
	return Vector3D(M.m11*V.x+M.m12*V.y+M.m13*V.z , M.m21*V.x + M.m22*V.y + M.m23*V.z ,M.m31*V.x+M.m32*V.y+M.m33*V.z);
}


 Vector3D operator *(Vector3D V, Matrix3D M)
{
	return Vector3D(M.m11*V.x+M.m12*V.y+M.m13*V.z , M.m21*V.x + M.m22*V.y + M.m23*V.z ,M.m31*V.x+M.m32*V.y+M.m33*V.z);

}

 Matrix3D operator *( Matrix3D M,float k)
{
    return Matrix3D( M.m11*k , M.m12*k , M.m13*k ,
		             M.m21*k , M.m22*k , M.m23*k ,
					 M.m31*k , M.m32*k , M.m33*k);
}


 Matrix3D operator *(float k, Matrix3D M)
{
	return Matrix3D( M.m11*k , M.m12*k , M.m13*k ,
		             M.m21*k , M.m22*k , M.m23*k ,
					 M.m31*k , M.m32*k , M.m33*k);
}


inline float Matrix3D::Trace()
{
	return( m11 + m22 + m33 );
}

 Matrix3D Skew(Vector3D M)
{
	return Matrix3D( 0 , -M.z , M.y ,
		             M.z , 0 , -M.x ,
					-M.y , M.x , 0 );
}

Matrix3D::operator D3DXMATRIX()
{
	
	return D3DXMATRIX(  m11, m12, m13, 0,
			            m21, m22, m23, 0,
				        m31, m32, m33, 0, 
                        0  ,  0 ,  0 , 1 );
}

    
//////////////////////////////////end of Matrix3D class implementation//////////////////////////////////////////////////



///////////////////////////////////////////Begin Quaternions//////////////////////////////////////////////////////////////

 quaternion::quaternion()
{
	w=0.0;
	v.x = v.y = v.z= 0.0;
}

quaternion::quaternion(float a , float b ,float c , float d)
{
	w   =a; 
	v.x =b;
	v.y =c;
	v.z =d;
}

quaternion::quaternion(float a , Vector3D vec)
{
	w=a;
	v=vec;
}

inline quaternion::quaternion(const quaternion &q)
{
	w=q.w;
	v=q.v;
}

inline quaternion & quaternion::operator =(const quaternion& q)
{
	w=q.w;
	v=q.v;
	return *this;
}

quaternion& quaternion::operator +=(quaternion q)
{
	w+=q.w;
	v+=q.v;
	return *this;
}

inline quaternion& quaternion::operator *=(float k)
{
	w*=k;
	v*=k;
	return *this;
}
inline quaternion& quaternion::operator /=(float k)
{
    assert(k!=0.0f);   
	w/=k;
   	v/=k;
   return *this;
}


inline quaternion quaternion::operator~()const
{
	return quaternion(w,-1*v);
}

inline float quaternion::Norm()
{
	return((float)(w*w+ v.x*v.x + v.y*v.y + v.z*v.z));
}

inline float quaternion::Dot(quaternion q1 , quaternion q2)
{
	return(  q1.w*q2.w + q1.v*q2.v);
}

inline quaternion quaternion::Inverse()const
{
	float N=(w*w+ v.x*v.x + v.y*v.y + v.z*v.z);
	if (N==0.0f)    N=1.0f;
	return( quaternion( w/N ,-1*v/N ) );
}

 quaternion operator+(const quaternion q1 ,const quaternion q2)
{
	return( quaternion( q1.w + q2.w , q1.v + q2.v ) );
}

  quaternion operator-(const quaternion q1 ,const quaternion q2)
{
     return( quaternion( q1.w - q2.w , q1.v - q2.v ) );
}
	

quaternion operator*(const quaternion q1 , const quaternion q2)
{
	return (  quaternion (q1.w*q2.w - q1.v*q2.v , q1.w*q2.v + q2.w*q1.v + q1.v^q2.v) );
}

quaternion operator*(float k, const quaternion q)
{
	return quaternion(k*q.w,k*q.v);
}


 quaternion operator*(const quaternion q  ,float k )
{
   return quaternion(q.w*k,q.v*k);
}

	
 quaternion operator/(const quaternion q, float k)
{
    assert(k!=0.0f);
	return quaternion(q.w/k,q.v/k);
}

inline Vector3D quaternion::GetVector3D()
{
	return(Vector3D(v.x,v.y,v.z));
}

inline float quaternion::GetScalar()
{
	return w;
}

 



	
	
	

