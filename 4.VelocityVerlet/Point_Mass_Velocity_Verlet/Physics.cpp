

#include"Physics.h"



Physics::Physics()
{

}

Physics::~Physics() 
{

}


void Physics::Update(float dt)
{        
	    // sum the forces applied to the ball   to TotalFoce= Force + Weight ( Newton's  second law) 
	totalForces = force + weight;
        // create a temporary velocity of type Vector3D; call it tempVelocity
	Vector3D tempVelocity;
		 // create another position holder vector of type Vector3D ; call it savePosition. It will save the current position
	Vector3D savePosition;
		 // create the next acceleration vector of type Vector3D ; call it nextAcceleration.
	Vector3D nextAcceleration;
         // set savePosition to the actual position
	savePosition = position;
        // using newton second law, m*a=F to calculate current acceleration that is a=F/m  
	acceleration = totalForces / mass;
		// use Velocity Verlet Position equation to compute the future position: r(t0+dt)=r(t0)+ v(t0)*dt +1/2*a(t0)dt*dt 
	position = position + velocity * dt + 0.5 * acceleration * dt * dt;
		// compute the temporary velocity using the computed position and savePosition that is  temporary velocity =(new position - saved position)/dt
	tempVelocity = (position - savePosition) / dt;
		 // compute the next acceleration , a(t+dt),  using the computed temporary velocity(tempVelocity) and the initial velocity 
		 // that is: next acceleration= (temporary velocity- initial velocity)/dt
	nextAcceleration = (tempVelocity - velocity) / dt;
	// use Velocity Verlet velocity equation to compute the future velocity: v(t+dt)=v(t)+ ( a(t) + a(t+dt))/2
         // that is : new velocity = old velocity + 0.5*(current acceleration + next acceleration)*deltaTime
	velocity = velocity + 0.5 * (acceleration + nextAcceleration) * dt;
	    // using DirectX built-in translation matrix,  D3DXMatrixTranslation(), to move the particle.The referenced matrix name will be WorldMatrix.
	D3DXMatrixTranslation(&WorldMatrix, position.x, position.y, position.z);
}
