

#include"Physics.h"
#include"commonFile.h"



Ground::Ground(): Planes()
{
  point=Vector3D(0.0f,0.0f,0.0f);
  normal=Vector3D(0.0f,1.0f,0.0f);
}

Physics::Physics()
{

}

Physics::~Physics() 
{

}


void Physics::Update(float dt)
{       
	
	    // compute speed
	speed = linearVelocity.Norm();
	    // compute the drag force
	dragForce = -0.5f * rho * speed * dragCoefficient * area * linearVelocity;
	    // update the ball position using Euler method
	position = position + linearVelocity * dt;
	
		if(position.y <= radius )
		{  
			//clamp it to the value of the radius
			position.y = radius;
		}
		
		// make the object move (translate) in real-time using D3DXMatrixTranslation()
		D3DXMatrixTranslation(&WorldMatrix, position.x, position.y, position.z);
}       





void Physics::ApplyFriction(float dt)
{
	float staticFriction;// static friction
	Vector3D kineticFriction;// kinetic friction
	Vector3D tangentForce; // tangential component of the applied force
	Vector3D normal; // normal vector of the ground
	Vector3D tangent; // vector in the direction of the tangential component of the applied force
	Ground   ground;
	Vector3D d;// unit vector of the applied force

	// normal to ground normal vector (0,1,0)
	normal=ground.normal;
    

	if(linearVelocity.Norm() == 0.0f  )
	{   
		///--- stable static  state ----

		// compute static friction
		staticFriction = StaticFrictionCoefficient*normalForce.Norm();
		// set linear velocity to (0,0,0)
		linearVelocity       = Vector3D(0.0f,0.0f,0.0f);
		// set linear acceleration to (0,0,0)
		linearAcceleration   = Vector3D(0.0f,0.0f,0.0f);
			
	    // compute the total force applied to the ball (we realy do not need that since a and v are zero); 
		// DO NOT ADD the static friction force since it should not cause motion
	   	totalForces= weight + normalForce ;
		
	}

		
	if(linearVelocity.Norm()>0)
	{    
	   //---- this is the dynamic state---

	  // Compute Kinetic(Dynamic) friction , see note for the formula
        kineticFriction= -DynamicFrictionCoefficient*normalForce.Norm()*linearVelocity.Normalize();
     // set the frictionForce equal to the previously computed kineticFriction
		frictionForce=kineticFriction;
	 // compute the total force , included friction and drag force , on the ball
		totalForces= force + weight + normalForce + frictionForce + dragForce; 
		// compute the linear acceleration of the ball
		linearAcceleration=totalForces/mass;
		// compute the linear velocity of the ball
		linearVelocity=linearVelocity + linearAcceleration*dt;
		
	}

    if(linearVelocity.Norm() == 0 && force.Norm() > staticFriction)
	 {
		 //--- this is the unstable static state---

		 float  slidingFactor;// a sliding factor to make the transition from static to dynamic friction state.

         // compute the sliding factor . see note 
		 slidingFactor = force.Norm() / staticFriction;
		 // compute a small initial velocity to break the transition from static friction to dynamic friction
		 // in the direction of the applied force normalized vector.
		 linearVelocity = slidingFactor * force.Normalize();
		 // now,the ball is moving with a non-zero velocity.Kinetic friction is being applied.
		 // Compute it(see note on Kinetic friction)
		 kineticFriction = -this->DynamicFrictionCoefficient * normalForce.Norm() * linearVelocity.Normalize();
		 // Set the friction force(frictionForce) equal to the kinetic friction(kineticFriction) as computed above
		 frictionForce = kineticFriction;
		 // compute the total forces on the ball : weight , drag  , friction force ,normal and applied force(force) 
		 totalForces= force + weight + normalForce + frictionForce + dragForce; 
		 // compute the linear acceleration 
		 linearAcceleration = totalForces / mass;
		 // compute the updated linear velocity
		 linearVelocity = linearVelocity + linearAcceleration * dt;
	 }
        // now clamp the velocity by its components to zero by doing the followings:

        // if the X component of velocity is 0.1(close to 0) , set it to 0
	    if( fabs(linearVelocity.x) <=0.1f) linearVelocity.x=0.0f;

		// if the Y component of velocity is 0.1 (close to 0), set it to 0
		if (fabs(linearVelocity.y) <= 0.1f) linearVelocity.y = 0.0f;
		// if the Z component of velocity is 0.1(close to 0) , set it to 0
		if (fabs(linearVelocity.z) <= 0.1f) linearVelocity.z = 0.0f;
		       

}


     


	 COLLISION_STATE  CheckSpherePlaneCollision(RigidBody& body1,Ground& ground)
     {
           COLLISION_STATE  HasCollided=NO_COLLISION;

		  float Vrn; // relative speed in the collision normal direction
		  float d;   // d of plane equation n*p+d=0 where d=-Plane_normal*point_on_plane
		  float R;// to represent radius
		  Vector3D n=ground.normal;
		  Vector3D P=ground.point;
		  Vector3D C= body1.position;
		  // compute d of the plane
		  d=-n*P;
		  // Set R to body1 radius
		  R=body1.radius;

          // compute body1 normal velocity 
		  body1.normalVelocity = (body1.linearVelocity * n) * n;
		  // compute body1 tangential velocity
		  body1.tangentialVelocity = body1.linearVelocity - body1.normalVelocity;
		  // compute the relative speed in the direction of the collision normal n that is Vrn=normalVelocity*n .
		  Vrn = body1.normalVelocity * n;
		 
		  
		  if(body1.normalVelocity.Norm() < 0.1)
		  {
			  //  then set the normal velocity to zero vector 
			  body1.normalVelocity = Vector3D(0, 0, 0);
			  //and Vrn to zero.
			  Vrn = 0;
		  }
           
	
		  if (Vrn< 0 && abs(n * C+d) <=R)
		  {
			  //set HasCollided equal to COLLISION;
			  HasCollided = COLLISION;
		  }
		  else 

		  if (Vrn ==0 && abs(n * C + d) == R)
		  {
			  //set HasCollided equal to RESTING_CONTACT;
			  HasCollided = RESTING_CONTACT;
		  }

		  else 
            
		  if (Vrn > 0 || abs(n * C + d) > R/*if Vrn>0 OR |n*C+d|>R*/)
			{
				//set HasCollided equal to NO_COLLISION;
			  HasCollided = NO_COLLISION;
			}

		   return HasCollided;
	 }


	 void HandleSpherePlaneCollision(RigidBody& body1 ,Ground& ground)
	 {
		 float e; // coefficient of Restitution 
		 // Set e to body1 coefficient Of Restitution
		 e = body1.coefficientOfRestitution;
		 // compute body1 linear velocity after contact ; see note
		 body1.linearVelocity = -e * body1.normalVelocity + body1.tangentialVelocity;

	 }


	   void HandleRestingContact(RigidBody& body1 ,Ground& ground,float dt)
	   {

		   
           if(body1.position.y == body1.radius/* if body1 position Y-component equal to its radius*/)
		   {
			 // then apply friction ( applyFriction(dt)  ) to body1.
			   body1.ApplyFriction(dt);
		   }
	   }

	 




///////////////////////////////////////////////////////////////////////////////////////

	   
LPD3DXBUFFER  D3DXMtrlBuffer=NULL;



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
		 // MessageBox(0,"   Cannot find file to load mesh..... ",0,MB_OK);
		  
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
					 // MessageBox(0,"Model Texture upload failed"," ",MB_OK);
				  }
			  }

			  else

			  {
				 //MessageBox(0,"Cannot find texture file"," ",MB_OK); 
			     meshData->meshTextures[i]=NULL;
				  
			  }
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
		  //MessageBox(0,"No file was loaded",0,MB_OK);
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

//////////////////////////////////////////////////////class ground implementation\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

 // Ground::Ground() : Planes(){   }
  Ground::~Ground() { }
