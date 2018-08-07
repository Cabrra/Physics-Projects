
#include"CommonFile.h"
//#include"Game3DModel.h"


LPD3DXBUFFER  D3DXMtrlBuffer=NULL;
//D3DXMATERIAL* meshMaterials    =NULL;


Mesh::MeshData::MeshData()
{
	meshTextures=NULL;
	meshMaterials=NULL;
	numberOfMaterials=0;
	d3dxMaterials=NULL;
	mesh=NULL;
	referenceCount=0;
}

Mesh::MeshData::~MeshData()
{
	if(meshMaterials!=NULL)
	{
		delete [] meshMaterials ; 
	}

	
	if(meshTextures!=NULL)
	{

		for (int i=0; i<numberOfMaterials;i++)
		{
			if(meshTextures[i]!=NULL)
			{
				meshTextures[i]->Release();
			}
		}
		delete [] meshTextures;
	}
}






Mesh::Mesh()
{
	meshData=new MeshData();
}



Mesh::~Mesh()
{
	meshData->referenceCount--;
	if(meshData->referenceCount==0)
	{
		meshData->mesh->Release();
		delete meshData;
	}
    
}



  Mesh &Mesh::operator =(Mesh& sourceMesh)
  {

	  if(meshData!=sourceMesh.meshData)
	  {
		  meshData->referenceCount--;
		  
		  if(meshData->referenceCount==0)
		  {
			  delete meshData;
		  }
		  meshData=sourceMesh.meshData;
		  sourceMesh.meshData->referenceCount++;
	  }
	  return *this;
  }




  bool Mesh::LoadMesh(std::string FileName,LPDIRECT3DDEVICE9 theDevice)
  { 
     LPD3DXBUFFER D3DXMtrlBuffer;
	  HRESULT       hr= NULL;
	  bool IsLoaded=false;

	  hr=D3DXLoadMeshFromX(FileName.c_str(),
		                   D3DXMESH_SYSTEMMEM,
						   theDevice,
						   NULL,
						   &D3DXMtrlBuffer,
						   NULL,
						   (DWORD*)&meshData->numberOfMaterials,
						   &meshData->mesh);


	  if(hr==D3D_OK)
	  {
	      meshData->d3dxMaterials=(D3DXMATERIAL*)D3DXMtrlBuffer->GetBufferPointer();
		  IsLoaded=true;
	  }
	  else
	  {
		  MessageBox(0,"   Cannot find file to load mesh..... ",0,MB_OK);
		  
	  }

	  
	  if(IsLoaded==true)
	  {
		  // load the mesh material

		  meshData->meshMaterials=new D3DMATERIAL9[meshData->numberOfMaterials];

		  if(meshData->meshMaterials==NULL)
		  {
		      
			  IsLoaded=false;
		  }
	  }


	  if( IsLoaded==true)
	  {
		  // load mesh texture
		  meshData->meshTextures=new LPDIRECT3DTEXTURE9 [meshData->numberOfMaterials];

		  if(meshData->meshTextures==NULL)
		  {
			  delete [] meshData->meshMaterials;
			  IsLoaded=false;
		  }
	  }


	  if(IsLoaded==true)
	  {

		  for(int i=0;i<meshData->numberOfMaterials;i++)
		  {
			  

		      meshData->meshMaterials[i]=meshData->d3dxMaterials[i].MatD3D; 
		      meshData->meshMaterials[i].Ambient=meshData->meshMaterials[i].Diffuse;


			  if( meshData->d3dxMaterials[i].pTextureFilename!=NULL && (lstrlen(meshData->d3dxMaterials[i].pTextureFilename)>0))
			  {
				  if(FAILED(D3DXCreateTextureFromFile(theDevice,meshData->d3dxMaterials[i].pTextureFilename,&meshData->meshTextures[i])))
				  {
					  IsLoaded=false;
					  MessageBox(0,"Model Texture upload failed"," ",MB_OK);
				  }
			  }

			  else

			  {
				 //MessageBox(0,"Cannot find texture file"," ",MB_OK); 
			     meshData->meshTextures[i]=NULL;
				  
			  }
		    meshData->referenceCount++;
		  }
	      
		  D3DXMtrlBuffer->Release();
	  }
  
     return IsLoaded;
	  
  }




  bool Mesh::RenderMesh(LPDIRECT3DDEVICE9 theDevice)
  {

	  bool IsRendered=true;

    /* Meshes are divided into subsets, one for each material. Each 
    mesh subset needs to be renderes individually. */
	  
    for(DWORD i=0;i<(DWORD)meshData->numberOfMaterials;i++ )
    {

        // Set the material for this subset
        if ( FAILED(theDevice->SetMaterial(&meshData->meshMaterials[i])))
        {
		    MessageBox(0,"SetMaterial()-Failed"," ",MB_OK);
            IsRendered=false;
        }

        // Set the texture for this subset
        if (FAILED(theDevice->SetTexture(0,meshData->meshTextures[i])))
        {
		    MessageBox(0,"SetTexture()-Failed"," ",MB_OK);
            IsRendered=false;

        }
    
        // Draw the mesh subset
           meshData->mesh->DrawSubset(i);
    }

    return (IsRendered);
  }


  //////////////////////////////////////////////// class RigidBody implementation/////////////////////////////////////////////////


  RigidBody::RigidBody() :Physics()
  {
    modelMesh=new Mesh(); 
  }



  RigidBody::~RigidBody()
  {
    delete modelMesh;
  }



  bool RigidBody::Load(std::string ModelMesh_Filename,LPDIRECT3DDEVICE9 theDevice)
  {
	  
	  bool IsLoaded=true;

	  if(ModelMesh_Filename.length()>0)
	  {
		  modelMesh->LoadMesh(ModelMesh_Filename,theDevice);
	  }
	  else
	  {
		  IsLoaded=false;
		  MessageBox(0,"No file was loaded",0,MB_OK);
	  }

	  return IsLoaded;
  }



  bool RigidBody::Render(LPDIRECT3DDEVICE9 theDevice)
  {
	  D3DXMATRIX ModelLocalMatrix;

	  theDevice->GetTransform(D3DTS_WORLD,&ModelLocalMatrix);
	  theDevice->SetTransform(D3DTS_WORLD,&WorldMatrix);
	  modelMesh->RenderMesh(theDevice);
	  theDevice->SetTransform(D3DTS_WORLD,&ModelLocalMatrix);

	  return true;
  }





