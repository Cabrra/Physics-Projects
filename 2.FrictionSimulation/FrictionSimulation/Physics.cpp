

#include"Physics.h"
#include"commonFile.h"


Physics::Physics()
{

}

Physics::~Physics() 
{

}


void Physics::Update(float dt)
{ 

	    // compute ball speed , that is the morm of the velocity
	this->speed = linearVelocity.Norm();
	    // compute the aerodynamic drag force(see note about the formula)
	this->dragForce = -0.5f * rho * speed * dragCoefficient * area * linearVelocity;
	    // apply friction by calling ApplyFriction()
	ApplyFriction(dt);
	// compute the linear acceleration using Newton's 2nd Law
	this->linearAcceleration = totalForces / mass;
	// compute the linear velocity
	this->linearVelocity = linearVelocity + linearAcceleration * dt;
	// the position of the object
	this->position = position + linearVelocity * dt;
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
   
    // set the ground normal vector(normal) to j=(0,1,0)
	normal = Vector3D(0.0f, 1.0f, 0.0f);
	// define and set n to normal
	Vector3D n = normal;
	// compute the tangential component of the applied force(tangentForce) ; see note.
	tangentForce = force - (force * n) * n;
	// compute the tangent vector(tangent) , that is the result of normalizing the tangentForce using Normalize() 
	tangent = tangentForce.Normalize();

	if( linearVelocity.Norm()==0.0F)
	{   // we have static state
		// compute static friction , see note for formula
		staticFriction = StaticFrictionCoefficient * normalForce.Norm();
		// set linear velocity to (0,0,0)
		linearVelocity = Vector3D(0.0f, 0.0f, 0.0f);
	    // compute the total force applied to the ball; 
		// DO NOT ADD the static friction force since it should not cause motion
		totalForces = weight + normalForce;
	}

		
	if( linearVelocity.Norm()>0.0f )
	{    
	
	  // Compute Kinetic(Dynamic) friction , see note for the formula
		kineticFriction = -DynamicFrictionCoefficient * normalForce.Norm() * linearVelocity.Normalize();
		// set the frictionForce equal to the previously computed kineticFriction
		frictionForce = kineticFriction;
		// compute the total force , included friction and drag force , on the ball
		totalForces = force + weight + normalForce + frictionForce + dragForce;
	}

    if( linearVelocity.Norm()==0.0f && tangentForce.Norm()>=staticFriction)
	 {
		 float  slidingFactor; // a sliding factor to make the transition from static to dynamic friction state 
         // compute the sliding factor (=sliding speed) that is the ratio of the tangent Force norm  over static Friction force  ;
		 slidingFactor = tangentForce.Norm() / staticFriction;
		 // compute an initial velocity to break the transition from static friction to dynamic friction
		 // that is velocity= slidingFactor x direction of action (= direction of tangent force,computed as "tangent")
		 linearVelocity = slidingFactor * tangent;
		 // compute Kinetic(dynamic) friction
		 kineticFriction = -DynamicFrictionCoefficient * normalForce.Norm() * linearVelocity.Normalize();
		 // set frictionForce equal to dynamic friction computed above
		 frictionForce = kineticFriction;
		 //compute total forces involved
		 totalForces = force + weight + normalForce + frictionForce + dragForce;

	 }
        // now clamp the velocity by its components to zero by doing the followings:

        // if the X component of velocity is 0.1(close to 0) , set it to 0
	if (linearVelocity.x <= 0.1)
		linearVelocity.x = 0;
	// if the Y component of velocity is 0.1 (close to 0), set it to 0
	if (linearVelocity.y <= 0.1)
		linearVelocity.y = 0;
	// if the Z component of velocity is 0.1(close to 0) , set it to 0
	if (linearVelocity.z <= 0.1)
		linearVelocity.z = 0;
}










