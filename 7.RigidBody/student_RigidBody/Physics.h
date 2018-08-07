

#ifndef  _PHYSICS_H
#define  _PHYSICS_H

#define COLLISION_TOLERANCE 0.1

typedef enum COLLISION_STATE{ NO_COLLISION ,COLLISION, TOUCHING ,PENETRATING };

typedef class RigidBody  RIGIDBODY;

typedef class Collision  TCOLLISION;

static bool forceApplied=false;



class Physics 
{

private:
 
public:
	Physics();
	~Physics();
	float mass;
	float massInv; // inverse of mass that is 1/mass
	float speed;
	float radius;
	Vector3D angularVelocity; // angular velocity
	Vector3D angularAcceleration;
	Matrix3D inertia; // inertia Tensor in world space
	Matrix3D inertiaInv; // inverse inertia tensor  
	Matrix3D Ibody;  // inertia Tensor in body space
	Matrix3D orientation; // body orientation;
	float    coefficientOfRestitution;
	float    mu;
	Vector3D position;
	Vector3D velocity;
	Vector3D acceleration;
	Vector3D impulse;
	Vector3D impulseForce;
	Vector3D torque;
	Vector3D contactLocation;
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
   Vector3D frictionForce;
   Vector3D relativeVelocity; // relatve velocity of colliding bodies in the collision normal direction
};

 void HandleCollision(RIGIDBODY& body1 ,RIGIDBODY& body2,TCOLLISION& theCollision, float dt);

 void ResolveOverlapping(RIGIDBODY& body1 ,RIGIDBODY& body2,TCOLLISION& theCollision, float dt);

 COLLISION_STATE CheckCollision(RIGIDBODY& body1,RIGIDBODY& body2,TCOLLISION& theCollision);

 bool IsZero(float value);
 
#endif


