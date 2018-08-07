

#ifndef  _PHYSICS_H
#define  _PHYSICS_H

#include"MathLib.h"


/********************************************************************************************************************
Author     : Richard Bahin
class      : Physics                                                                                 
base class : none  																																																			
comment    : The Physics class for the  Physics simulation                                                                                                     
TODO       : None 																											
*********************************************************************************************************************/
class Physics 
{

private:
 
public:
	Physics();
	~Physics();
	float mass;
	float speed;
	Vector3D position; // object linear location
	Vector3D velocity; // object linear velocity
	Vector3D acceleration; // object linear acceleration
	Vector3D totalForces;  // sum of forces applied to object
	Vector3D weight; // gravity force w=m*g  where g=9.81m/s/s
	Vector3D force; // applied outer force
	
	void Update(float dt); // to update body physical parameters(velocity,position,force,orientation....)
	D3DXMATRIX WorldMatrix;
	
};


#endif


