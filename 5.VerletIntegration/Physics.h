

#ifndef  _PHYSICS_H
#define  _PHYSICS_H

#include"MathLib.h"

class Physics 
{

private:
 
public:
	Physics();
	~Physics();
	float mass;
	float speed;
	Vector3D weight;
	Vector3D position; // location of center of mass(particle)
	Vector3D previousPosition;
	Vector3D velocity;
	Vector3D acceleration;
	Vector3D totalForces;
	Vector3D force;
	void Update(float dt); // to update body physical parameters(velocity,position,force,orientation....)
	D3DXMATRIX WorldMatrix;
	
};


#endif


