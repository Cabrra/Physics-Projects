

#ifndef  _PHYSICS_H
#define  _PHYSICS_H

 #include"MathLib.h"
#include"commonFile.h"
#include"Game.h"
//#include<math.h>
#include"Plane.h"



typedef enum COLLISION_STATE{ NO_COLLISION ,COLLISION, RESTING_CONTACT };

typedef class RigidBody  RIGIDBODY;

typedef class Collision  TCOLLISION;



class Ground : public Planes
{
public:
	Ground();
	~Ground();
	Vector3D point;
	Vector3D normal;
};

class Physics 
{

private:

	
 
public:
	Physics();
	~Physics();
	float mass;
	float speed;
	float DynamicFrictionCoefficient;
	float StaticFrictionCoefficient;
	float dragCoefficient;
	float coefficientOfRestitution;
	float radius;
	
	Vector3D position;
	Vector3D linearVelocity;
	Vector3D tangentialVelocity;
	Vector3D normalVelocity;
	Vector3D linearAcceleration;
	Vector3D force;
	Vector3D totalForces;
	Vector3D gravity;
	Vector3D frictionForce;
	Vector3D normalForce;
	Vector3D weight;
    Vector3D dragForce;


	float rho; // mass density  of the fluid through which the object is traveling( air or water)
	float area; // area of the object 
  
	Matrix3D orientation;
	D3DXMATRIX WorldMatrix;
	void Update(float dt); // to update body physical parameters(velocity,position,force,orientation....)
	void ApplyFriction(float dt);
	
		
};


class Collision
{
public:
   Collision();
  ~Collision();
   Vector3D normal;  // collision normal 
   Vector3D tangent; // collision tangent
   Vector3D contactPoint;// collision point
   Vector3D contactForce;
   Vector3D relativeVelocity ; // relatve velocity of colliding bodies
};

 COLLISION_STATE  CheckSpherePlaneCollision(RigidBody& body1,Ground& ground);
void HandleSpherePlaneCollision(RigidBody& body1 ,Ground& ground);
void HandleRestingContact(RigidBody& body1 ,Ground& ground,float dt);



/////////////////////////////////////////////////////////////////////////////////////////////////////////


class Mesh 
{

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
    
	Mesh* modelMesh;

public:
	RigidBody();
	~RigidBody();
	bool Render(LPDIRECT3DDEVICE9 theDevice);
	bool Load(std::string ModelMesh_Filename,LPDIRECT3DDEVICE9 theDevice);
};


#endif


