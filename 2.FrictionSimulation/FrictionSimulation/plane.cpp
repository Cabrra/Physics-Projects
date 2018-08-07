
#include "plane.h"
#include "commonFile.h"



  

 
Planes::Planes()
{
	    Floor=NULL;
	    PlaneTexture=NULL;
        v=NULL;
}


Planes::~Planes()
{
  SAFE_RELEASE(Floor);
  SAFE_RELEASE(PlaneTexture);
  SAFE_DELETE_ARRAY(v);

}

void Planes::CreatePlane(LPDIRECT3DDEVICE9 theDevice , LPCSTR textureFilename)
{
    const float  DIM=300.0f;
	theDevice->CreateVertexBuffer(6*sizeof(Vertex),0,Vertex::FVF,D3DPOOL_MANAGED,&Floor,0);
	Vertex* v=0;
	Floor->Lock(0,0,(void**)&v,0);
	v[0]=Vertex(-DIM,0.0f,-DIM,0.0f,1.0f,0.0f,0.0f,0.1f); 
	v[1]=Vertex(-DIM,0.0f, DIM,0.0f,1.0f,0.0f,0.0f,0.0f);
	v[2]=Vertex( DIM,0.0f, DIM,0.0f,1.0f,0.0f,1.0f,0.0f);
	v[3]=Vertex(-DIM,0.0f,-DIM,0.0f,1.0f,0.0f,0.0f,1.0f);
	v[4]=Vertex( DIM,0.0f, DIM,0.0f,1.0f,0.0f,1.0f,0.0f);
	v[5]=Vertex( DIM,0.0f,-DIM,0.0f,1.0f,0.0f,1.0f,1.0f);
	Floor->Unlock();
	
   // load the plane texture
	D3DXCreateTextureFromFile(theDevice,textureFilename,&PlaneTexture);
	// create the plane texture state
	theDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	theDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	theDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_POINT);

	D3DXMATRIX scale;
	D3DXMatrixTranslation(&worldMatrix,position.x,position.y,position.z);
	D3DXMatrixScaling(&scale,2,2,2);
	worldMatrix=worldMatrix*scale;
	
	
}

void Planes::Render(LPDIRECT3DDEVICE9 theDevice)
{
    
    theDevice->GetTransform(D3DTS_WORLD, &saveWorldMatrix);
	theDevice->SetTransform(D3DTS_WORLD, &worldMatrix);
	theDevice->SetMaterial(&WHITEMATERIAL);
	theDevice->SetTexture(0,PlaneTexture);
	theDevice->SetFVF(Vertex::FVF);
	theDevice->SetStreamSource(0,Floor,0,sizeof(Vertex));
	theDevice->DrawPrimitive(D3DPT_TRIANGLELIST,0,2);
    theDevice->SetTransform(D3DTS_WORLD,&saveWorldMatrix);
	
}