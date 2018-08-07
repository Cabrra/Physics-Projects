#ifndef _PLANE_H
#define _PLANE_H

#include<d3dx9.h>
#include<string>


class Vertex
{  
public:
	float x,y,z;
	float nx,ny,nz;
	float u,v;
	Vertex();
	Vertex(float _x,float _y,float _z,float _nx,float _ny,float _nz,float _u,float _v )
	{
		x =_x;
		y=_y;
		z=_z;
		nx=_nx;
		ny=_ny;
		nz=_nz;
		u=_u;
		v=_v;
	};

	static const DWORD FVF= D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

};


class Planes
{
private:
	 LPDIRECT3DVERTEXBUFFER9 Floor;
	 LPDIRECT3DTEXTURE9     PlaneTexture;
     Vertex*                 v;
	 D3DXVECTOR3            point ; // point on plane
	 D3DXVECTOR3            normal ; // plane normal vector
      
public:
	 Planes();
	~Planes();
	void CreatePlane(LPDIRECT3DDEVICE9 theDevice,LPCSTR textureFilename);
	void Render(LPDIRECT3DDEVICE9 theDevice);
	D3DXMATRIX worldMatrix;    //world matrix 
	D3DXMATRIX saveWorldMatrix; // matrix to save content of world matrix
	D3DXVECTOR3 getPoint();
	D3DXVECTOR3 getNormal();
	D3DXVECTOR3 position;
	
};



  


#endif
