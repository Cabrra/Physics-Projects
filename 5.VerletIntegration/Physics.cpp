

#include"Physics.h"



Physics::Physics()
{

}

Physics::~Physics() 
{

}  


void Physics::Update(float dt)
{
  // To implement verlet integration

	   
	  // sum the forces applied to the ball   to TotalFoce= Force + Weight ( Newton's  second law)
	totalForces = force + weight;
       // define a temporary vector savePosition of type Vector3D
	Vector3D savePosition;
	   // set savePosition to position
	savePosition = position;
	   // Calculate  the acceleration using Newton a=F/m
	acceleration = totalForces / mass;
	// now compute the new position using velocity verlet:  r(t+dt)=2*r(t)-r(t-dt)+a(t)*dt*dt 
	   // that is new position= 2*(current position)-(previous position)+ (current acceleration)dt*dt
	position = 2 * position - previousPosition + acceleration * dt * dt;
		// set previousPosition to savePosition
		previousPosition = savePosition;
        // now translate the position in real-time by calling D3DXMatrixTranslation()
		D3DXMatrixTranslation(&WorldMatrix, position.x, position.y, position.z);
}
