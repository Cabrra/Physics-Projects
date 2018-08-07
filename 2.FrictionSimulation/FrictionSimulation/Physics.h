

#ifndef  _PHYSICS_H
#define  _PHYSICS_H

#include"MathLib.h"
#include<math.h>



class Physics 
{

private:

     void ApplyFriction(float dt);
	
 
public:
	Physics();
	~Physics();
	float mass;
	float speed;
	float DynamicFrictionCoefficient;
	float StaticFrictionCoefficient;
	float radius;
	
	Vector3D position;
	Vector3D linearVelocity;
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
	float dragCoefficient; // 

	Matrix3D orientation;
	D3DXMATRIX WorldMatrix;
	void Update(float dt); // to update body physical parameters(velocity,position,force,orientation....)
		
};


#endif


