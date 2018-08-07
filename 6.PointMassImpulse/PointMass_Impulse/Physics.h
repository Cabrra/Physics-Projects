

#ifndef  _PHYSICS_H
#define  _PHYSICS_H



typedef enum COLLISION_STATE{ NO_COLLISION ,COLLISION, TOUCHING ,PENETRATING };

typedef class RigidBody  RIGIDBODY;

typedef class Collision  TCOLLISION;

static bool forceApplied=false;



//#include"MathLib.h"



#define COLLISION_TOLERANCE 0.01


class Physics 
{

private:
 
public:
	Physics();
	~Physics();
	float mass;
	float speed;
	float radius;
	float coefficientOfRestitution;
	Vector3D position;
	Vector3D velocity;
	Vector3D acceleration;
	Vector3D impulse;
	Vector3D impulsiveForce;
	Vector3D force; // single initial outer force applied on the body
	Vector3D totalForces;//total force applied to the body 
	void Update(float dt); // to update body physical parameters(velocity,position,force,orientation....)
	D3DXMATRIX WorldMatrix;
	
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
   Vector3D relativeVelocity; // relatve velocity of colliding bodies
};

 void              HandleCollision(RIGIDBODY& body1 ,RIGIDBODY& body2,TCOLLISION& theCollision, float dt);
 COLLISION_STATE   CheckCollision(RIGIDBODY& body1,RIGIDBODY& body2 );
 bool IsZero(float value);
#endif


