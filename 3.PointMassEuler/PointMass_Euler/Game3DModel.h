

#ifndef _GAME3DMODEL_H
#define _GAME3DMODEL_H

#include"Game.h"
#include"Physics.h"
#pragma once 



class Mesh {

private:

    
	struct MeshData {

		               LPD3DXMESH mesh; // the  model mesh
					   D3DMATERIAL9 *meshMaterials; // mesh materials
					   LPDIRECT3DTEXTURE9* meshTextures; // mesh textures
					   D3DXMATERIAL* d3dxMaterials;  // the point to the material buffer
					   int numberOfMaterials;// number of materials in the mesh
					   int referenceCount;
					   MeshData();
					   ~MeshData();
	              
                   };


    MeshData*  meshData;


public:


	Mesh();
	~Mesh();
	Mesh(Mesh &sourceMesh);
	Mesh &operator=(Mesh& sourceMesh);
	bool LoadMesh(std::string FileName,LPDIRECT3DDEVICE9 thedevice);
	bool RenderMesh(LPDIRECT3DDEVICE9 theDevice);
	
	};




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class RigidBody: public Physics  {

private:
    //D3DXMATRIX WorldMatrix;
	Mesh* modelMesh;

public:
	RigidBody();
	~RigidBody();
	bool Render(LPDIRECT3DDEVICE9 theDevice);
	bool Load(std::string ModelMesh_Filename,LPDIRECT3DDEVICE9 theDevice);
};






#endif
