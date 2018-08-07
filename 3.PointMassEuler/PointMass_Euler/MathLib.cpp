
#include"MathLib.h"



/********************************************************************************************************************
Author  : Richard Bahin
Function: Vector3D()                                                                                    
Input   : none 																									
Output  : none																											
Returns : none                                                                                                        
comment : Vector3D class constructor                                                                                                        
TODO    : none																							
*********************************************************************************************************************/																													
Vector3D::Vector3D()
{ 
	x=0.0f;
    y=0.0f;
	z=0.0f;
}  

/********************************************************************************************************************
Author  : Richard Bahin
Function: Vector3D(float,float,float)                                                                                    
Input   : first ,second and third component of the vector																									
Output  : none																											
Returns : none                                                                                                        
comment : Vector3D class constructor with 3 arguments                                                                                                        
TODO    : none																							
*********************************************************************************************************************/			
 Vector3D::Vector3D(float a , float b , float c)
{
	x=a;
	y=b;
	z=c;
    
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: Vector3D                                                                                    
Input   : argument of type vector 																									
Output  : none																											
Returns : none                                                                                                        
comment : Vector3D class copy constructor                                                                                                        
TODO    : none																							
*********************************************************************************************************************/			
 Vector3D::Vector3D(const Vector3D& V)
{
	x=V.x;
	y=V.y;
	z=V.z;
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: operator =                                                                                    
Input   : none 																									
Output  : none																											
Returns : a vector of type Vector3D                                                                                                       
comment : overloaded assignment operator                                                                                                       
TODO    : none																							
*********************************************************************************************************************/			

 Vector3D& Vector3D::operator =(const Vector3D& V)  
{
	x=V.x;
	y=V.y;
	z=V.z;
	return *this;
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: Norm()                                                                                    
Input   : none 																									
Output  : none																											
Returns : argument of type float                                                                                                      
comment : This function will calculate the norm or magnitude of a vector                                                                                                      
TODO    : TBA																							
*********************************************************************************************************************/			
 float Vector3D::Norm() 
{   // norm=length=magnitude all the same
	
	return sqrt(x*x + y*y + z*z);
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: NormSquared()                                                                                    
Input   : none 																									
Output  : none																											
Returns : argument of type float                                                                                                      
comment : This function will calculate the square of the norm(magnitude) of a vector                                                                                                       
TODO    : TBA																							
*********************************************************************************************************************/		
float Vector3D::NormSquared()
{
	return(x*x + y*y + z*z);
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: operator *=                                                                                    
Input   : argument of type float 																									
Output  : none																											
Returns : argument of type Vector3D                                                                                                      
comment : This function will a vector by a scalar k and return a vector , V=K*V1                                                                                                     
TODO    : TBA																							
*********************************************************************************************************************/		
 Vector3D& Vector3D::operator *=(float k)
{
       x*=k;
	   y*=k;
	   z*=k;
	   return *this;
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: operator +=                                                                                    
Input   : argument of type Vector3D 																									
Output  : none																											
Returns : argument of type Vector3D                                                                                                      
comment : This function will add two vectors and return a vector , V = V1 + V2                                                                                                      
TODO    : TBA																							
*********************************************************************************************************************/		
 Vector3D& Vector3D::operator +=( Vector3D V)
{
	x += V.x;
	y += V.y;
	z += V.z;
    return *this;
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: operator -=                                                                                    
Input   : argument of type Vector3D 																									
Output  : none																											
Returns : argument of type Vector3D                                                                                                      
comment : This function will subtract two vectors and return a vector , V = V1 - V2                                                                                                      
TODO    : TBA																							
*********************************************************************************************************************/	
 Vector3D& Vector3D::operator -=( Vector3D V )
{
	x-=V.x;
	y-=V.y;
	z-=V.z;
	return *this;
}
/********************************************************************************************************************
Author  : Richard Bahin
Function: operator -()                                                                                    
Input   : none 																									
Output  : none																											
Returns : argument of type Vector3D                                                                                                      
comment : This function will reverse a vector , V = -V1                                                                                                     
TODO    : TBA																							
*********************************************************************************************************************/	

 Vector3D Vector3D::operator -()
{
	 return Vector3D(-1*x,-1*y,-1*z);
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: operator /=                                                                                    
Input   : argument of type float 																									
Output  : none																											
Returns : argument of type Vector3D                                                                                                      
comment : This function will divide a vector by a scalar and return a vector , V = V1/k                                                                                                      
TODO    : TBA																							
*********************************************************************************************************************/	
 Vector3D& Vector3D::operator /=(float k)
{
	assert(k!=0.0f);
	x/=k;
	y/=k;
	z/=k;
	return *this;
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: operator Normalize()                                                                                   
Input   : none 																									
Output  : none																											
Returns : argument of type Vector3D                                                                                                      
comment : This function will normalize a vector and return a normalized vector , V = V1/||v1||                                                                                                      
TODO    : TBA																							
*********************************************************************************************************************/	
Vector3D Vector3D::Normalize()const
{
	Vector3D V;
    float m=sqrtf(x*x+y*y+z*z);
	if(m!=ZERO)  V=Vector3D(x/m,y/m,z/m);
	return V;
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: ConvertToD3DXVector()                                                                                 
Input   : none																									
Output  : none																											
Returns : a vector of type D3DXVECTOR3                                                                                                      
comment : This function will convert our custom Vector3D into the Microsoft Direct3D vector type : D3DXVECTOR3                                                                                                       
TODO    : TBA																							
*********************************************************************************************************************/	
D3DXVECTOR3 Vector3D::ConvertToD3DXVector()
{
  return D3DXVECTOR3(x,y,z);
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: overloaded operator *()                                                                                 
Input   : a scalar and a vector																								
Output  : none																											
Returns : a vector of type Vector3D                                                                                                      
comment : This function will multiply a vector by a saclar                                                                                                        
TODO    : TBA																							
*********************************************************************************************************************/	
 Vector3D operator *(float k, Vector3D V)
{
	
  return Vector3D(k*V.x , k*V.y , k*V.z);
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: overloaded operator *()                                                                                 
Input   : a scalar and a vector																								
Output  : none																											
Returns : a vector of type Vector3D                                                                                                      
comment : This function will multiply on the right a vector by a scalar                                                                                                       
TODO    : TBA																							
*********************************************************************************************************************/	

Vector3D  operator* ( Vector3D V , float k)
{
	return Vector3D(V.x*k , V.y*k , V.z*k) ;
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: overloaded operator +()                                                                                 
Input   : Two vectors																								
Output  : none																											
Returns : a vector of type Vector3D                                                                                                      
comment : This function will add 2 vectors                                                                                                       
TODO    : TBA																							
*********************************************************************************************************************/	
 Vector3D operator +( Vector3D U,  Vector3D V)
{
	return Vector3D( U.x + V.x ,U.y + V.y ,U.z + V.z);

}



/********************************************************************************************************************
Author  : Richard Bahin
Function: overloaded operator -()                                                                                 
Input   :Two vectors																								
Output  : none																											
Returns : a vector of type Vector3D                                                                                                      
comment : This function will subtract two vectors                                                                                                        
TODO    : TBA																							
*********************************************************************************************************************/	
 Vector3D operator -( Vector3D U, Vector3D V)
{
	return Vector3D( U.x - V.x ,U.y - V.y , U.z - V.z );
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: overloaded operator *()                                                                                 
Input   :Two vectors																								
Output  : none																											
Returns : a scalar(float)                                                                                                      
comment : This function will dot multiply two vectors                                                                                                        
TODO    : TBA																							
*********************************************************************************************************************/	
 float  operator *( Vector3D U , Vector3D V )
{
	return (float)(U.x*V.x + U.y*V.y + U.z*V.z );
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: overloaded operator /()                                                                                 
Input   : A vectors and a scalar																								
Output  : none																											
Returns : a vector of type Vector3D                                                                                                      
comment : This function will divide a vector by a scalar                                                                                                        
TODO    : TBA																							
*********************************************************************************************************************/	
 Vector3D  operator/( Vector3D V , float k)
{
    assert(k!=0.0f);
	return Vector3D(V.x/k , V.y/k , V.z/k );
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: overloaded operator ^()                                                                                 
Input   :Two vectors																								
Output  : none																											
Returns : a vector of type Vector3D                                                                                                     
comment : This function will cross multiply ( cross product)  two vectors                                                                                                        
TODO    : TBA																							
*********************************************************************************************************************/	

 Vector3D  operator^( Vector3D U , Vector3D V )
{
	  return Vector3D(U.y*V.z - U.z*V.y , U.z*V.x - U.x*V.z , U.x*V.y - U.y*V.x);
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: Component(U,V)                                                                                 
Input   :Two vectors																								
Output  : none																											
Returns : a scalar (float)                                                                                                      
comment : This function will compute the component of a vector U onto a vector V                                                                                                        
TODO    : TBA																							
*********************************************************************************************************************/	
// The component of u onto v
 float Component( Vector3D U , Vector3D V)
{

	return(U*V.Normalize());
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: Projection(U,V)                                                                                 
Input   :Two vectors																								
Output  : none																											
Returns : a Vector of type Vector3D                                                                                                      
comment : This function will compute the component of a vector U onto a vector V                                                                                                        
TODO    : TBA																							
*********************************************************************************************************************/
 Vector3D  Projection( Vector3D U , Vector3D V)
{
	return( Component(U,V)*V.Normalize());
}





// ---------------------------------------------------Matrix class implementation------------------------------------




/********************************************************************************************************************
Author  : Richard Bahin
Function: Matrix3D()                                                                                    
Input   : none 																									
Output  : none																											
Returns : none                                                                                                        
comment : MatrixD class constructor                                                                                                        
TODO    : none																							
*********************************************************************************************************************/		
Matrix3D::Matrix3D()
{
	m11=m12=m13=0.0f;
	m21=m22=m23=0.0f;
	m31=m32=m33=0.0f;
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: Matrix3D(...)                                                                                    
Input   : The matrix entries values																									
Output  : none																											
Returns : none                                                                                                        
comment : MatrixD class constructor with argument values                                                                                                        
TODO    : none																							
*********************************************************************************************************************/		

Matrix3D::Matrix3D(float a11,float a12,float a13,
			       float a21,float a22,float a23,
				   float a31,float a32,float a33)
{
	m11=a11 ; m12=a12 ; m13=a13;
	m21=a21 ; m22=a22 ; m23=a23;
	m31=a31 ; m32=a32 ; m33=a33;
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: Matrix3D()                                                                                    
Input   : argument of type reference matrix 																									
Output  : none																											
Returns : none                                                                                                        
comment : MatrixD copy constructor                                                                                                        
TODO    : none																							
*********************************************************************************************************************/		
 Matrix3D::Matrix3D(const Matrix3D & M)
{
   m11=M.m11 ; m12=M.m12 ; m13=M.m13;
   m21=M.m21 ; m22=M.m22 ; m23=M.m23;
   m31=M.m31 ; m32=M.m32 ; m33=M.m33;
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: Overloaded operator=()                                                                                    
Input   : An argument of type reference Matrix3D 																									
Output  : none																											
Returns : none                                                                                                        
comment : MatrixD class constructor                                                                                                        
TODO    : none																							
*********************************************************************************************************************/
 Matrix3D& Matrix3D::operator =(const Matrix3D& M)
{
   m11=M.m11 ; m12=M.m12 ; m13=M.m13;
   m21=M.m21 ; m22=M.m22 ; m23=M.m23;
   m31=M.m31 ; m32=M.m32 ; m33=M.m33;
   return *this;
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: Overloaded operator*=()                                                                                    
Input   : An argument of type float 																									
Output  : none																											
Returns : A matrix (reference Matrix3D)                                                                                                        
comment : this function multiplies a matrix by a scalar                                                                                                        
TODO    : TBA																							
*********************************************************************************************************************/
Matrix3D& Matrix3D::operator *=(float k)
{
	m11*=k; m12*=k; m13*=k;
	m21*=k; m22*=k; m23*=k;
	m31*=k; m32*=k; m33*=k;
	return *this;
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: Overloaded operator+=()                                                                                    
Input   : An argument of type Matrix3D 																									
Output  : none																											
Returns : A matrix (reference Matrix3D)                                                                                                        
comment : this function will add two matrices                                                                                                        
TODO    : TBA																							
*********************************************************************************************************************/
Matrix3D& Matrix3D::operator +=(Matrix3D M)
{
	m11+=M.m11 ; m12+=M.m12 ; m13+=M.m13;
	m21+=M.m21 ; m22+=M.m22 ; m23+=M.m23;
	m31+=M.m31 ; m32+=M.m32 ; m33+=M.m33;
	return *this;
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: Overloaded operator-=()                                                                                    
Input   : An argument of type Matrix3D 																									
Output  : none																											
Returns : A matrix (reference Matrix3D)                                                                                                        
comment : this function will subtract two matrices                                                                                                        
TODO    : TBA																							
*********************************************************************************************************************/
Matrix3D& Matrix3D::operator -=(Matrix3D M )
{
   m11-=M.m11 ; m12-=M.m12 ; m13-=M.m13;
   m21-=M.m21 ; m22-=M.m22 ; m23-=M.m23;
   m31-=M.m31 ; m32-=M.m32 ; m33-=M.m33;
	return *this;
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: Overloaded operator/=()                                                                                    
Input   : An argument of type float (a scalar)
Output  : none																											
Returns : A matrix (reference Matrix3D)                                                                                                        
comment : this function will a matrix by a scalar                                                                                                        
TODO    : TBA																							
*********************************************************************************************************************/

Matrix3D& Matrix3D::operator /=(float k )
{
    //assert(k!=0.0f);
	m11/=k; m12/=k; m13/=k;
	m21/=k; m22/=k; m23/=k;
	m31/=k; m32/=k; m33/=k;
	return *this;
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: Transpose()                                                                                    
Input   : none 																									
Output  : none																											
Returns : A matrix  (Matrix3D)                                                                                                        
comment : this function will compute the transpose of a  matrix                                                                                                       
TODO    : TBA																							
*********************************************************************************************************************/
Matrix3D Matrix3D::Transpose()const{
	return Matrix3D(m11,m21,m31,
		            m12,m22,m32,
					m13,m23,m33);
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: Determinant()                                                                                    
Input   : none 																									
Output  : none																											
Returns : A scalar (float)                                                                                                        
comment : this function will compute the determinant of a  matrix                                                                                                       
TODO    : TBA																							
*********************************************************************************************************************/

float Matrix3D::Determinant()
{
	return( m11*(m22*m33-m23*m32) - m12*(m21*m33-m31*m23)+ m13*(m21*m32-m31*m22));
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: Inverse()                                                                                    
Input   : none 																									
Output  : none																											
Returns : A matrix  (Matrix3D)                                                                                                        
comment : this function will compute the inverse of a  matrix                                                                                                       
TODO    : TBA																							
*********************************************************************************************************************/
 Matrix3D Matrix3D::Inverse()
{
    Matrix3D adjointMatrix;
	Matrix3D cofactorMatrix;
	Matrix3D inverseMatrix;
	float c11,c12,c13,c21,c22,c23,c31,c32,c33;  // cofactors 
	c11=  m11*(m22*m33-m31*m23);
	c12= -m12*(m21*m33-m31*m23);
	c13=  m13*(m21*m32-m31*m22);
	c21= -m21*(m12*m33-m32*m13);
	c22=  m22*(m11*m33-m31*m13);
	c23= -m23*(m11*m32-m31*m12);
	c31=  m31*(m12*m23-m22*m13);
	c32= -m32*(m11*m23-m21*m13);
	c33=  m33*(m11*m22-m21*m12);
    // compute the cofactor matrix
	cofactorMatrix=Matrix3D(c11,c12,c13,
		                    c21,c22,c23,
							c31,c32,c33);
	// compute the adjoint matrix by transposing the cofactor matrix
	adjointMatrix=cofactorMatrix.Transpose();
	float det=Determinant();
	if(det!=ZERO)  inverseMatrix=adjointMatrix/Determinant();
	
	return inverseMatrix;	
}

/********************************************************************************************************************
Author  : Richard Bahin
Function: Orthonormalize()                                                                                    
Input   : none 																									
Output  : none																											
Returns : A matrix  (Matrix3D)                                                                                                        
comment : this function will orthonormalize a matrix using Gram-Schmidt Orthonormalization Algorithm                                                                                                       
TODO    : TBA																							
*********************************************************************************************************************/
Matrix3D Matrix3D::Orthonormalize()
{
   Vector3D U,V,W;
   U=Vector3D(m11,m21,m31);
   V=Vector3D(m12,m22,m32);
   W=Vector3D(m13,m23,m33);
   U=U.Normalize();
   V=V-Projection(V,U);
   V=V.Normalize();
   W=U^V;
   m11=U.x ; m12=V.x ; m13=W.x ;
   m21=U.y ; m22=V.y; m23=W.y ;
   m31=U.z ; m32=V.z ; m33=W.z ;
   
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
					 N.m31*N.m13 + M.m32*N.m23 + M.m33*N.m33);
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


Matrix3D operator /( Matrix3D M , float k)
{
  
   assert(k>ZERO);

   return Matrix3D(  M.m11/k , M.m12/k , M.m13/k ,
		             M.m21/k , M.m22/k , M.m23/k ,
					 M.m31/k , M.m32/k , M.m33/k  );
}


 float Matrix3D::Trace()
{
	return( m11 + m22 + m33 );
}

 Matrix3D Skew(Vector3D V)
{
	return Matrix3D( 0 , -V.z , V.y ,
		             V.z , 0 , -V.x ,
					-V.y , V.x , 0 );
}

	
D3DXMATRIX Matrix3D::ConvertToD3DXMatrix()
{
  return D3DXMATRIX(    m11, m12, m13, 0,
			            m21, m22, m23, 0,
				        m31, m32, m33, 0, 
                        0  ,  0 ,  0 , 1 ); 
}
    
//////////////////////////////////end of Matrix3D class implementation//////////////////////////////////////////////////



///////////////////////////////////////////Begin Quaternions//////////////////////////////////////////////////////////////

 Quaternion::Quaternion()
{
	w=0.0;
	v.x = v.y = v.z= 0.0;
}

Quaternion::Quaternion(float a , float b ,float c , float d)
{
	w   =a; 
	v.x =b;
	v.y =c;
	v.z =d;
}

Quaternion::Quaternion(float a , Vector3D vec)
{
	w=a;
	v=vec;
}

Quaternion::Quaternion(const Quaternion &q)
{
	w=q.w;
	v=q.v;
}

Quaternion & Quaternion::operator =(const Quaternion& q)
{
	w=q.w;
	v=q.v;
	return *this;
}

Quaternion& Quaternion::operator +=(Quaternion q)
{
	w+=q.w;
	v+=q.v;
	return *this;
}

Quaternion& Quaternion::operator *=(float k)
{
	w*=k;
	v*=k;
	return *this;
}
Quaternion& Quaternion::operator /=(float k)
{
    assert(k!=0.0f);   
	w/=k;
   	v/=k;
   return *this;
}


Quaternion Quaternion::operator~()const
{
	return Quaternion(w,-1*v);
}

float Quaternion::Norm()
{
	return((float)(w*w+ v.x*v.x + v.y*v.y + v.z*v.z));
}

float Quaternion::Dot(Quaternion q1 , Quaternion q2)
{
	return(  q1.w*q2.w + q1.v*q2.v);
}

Quaternion Quaternion::Inverse()const
{
	float N=(w*w+ v.x*v.x + v.y*v.y + v.z*v.z);
	if (N==0.0f)    N=1.0f;
	return( Quaternion( w/N ,-1*v/N ) );
}

 Quaternion operator+(const Quaternion q1 ,const Quaternion q2)
{
	return( Quaternion( q1.w + q2.w , q1.v + q2.v ) );
}

  Quaternion operator-(const Quaternion q1 ,const Quaternion q2)
{
     return( Quaternion( q1.w - q2.w , q1.v - q2.v ) );
}
	

Quaternion operator*(const Quaternion q1 , const Quaternion q2)
{
	return (  Quaternion (q1.w*q2.w - q1.v*q2.v , q1.w*q2.v + q2.w*q1.v + q1.v^q2.v) );
}

Quaternion operator*(float k, const Quaternion q)
{
	return Quaternion(k*q.w,k*q.v);
}


 Quaternion operator*(const Quaternion q  ,float k )
{
   return Quaternion(q.w*k,q.v*k);
}

	
 Quaternion operator/(const Quaternion q, float k)
{
    assert(k!=0.0f);
	return Quaternion(q.w/k,q.v/k);
}

Vector3D Quaternion::GetVector3D()
{
	return(Vector3D(v.x,v.y,v.z));
}

float Quaternion::GetScalar()
{
	return w;
}

 



	
	
	

