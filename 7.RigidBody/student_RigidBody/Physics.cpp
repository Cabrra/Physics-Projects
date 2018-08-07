

#include"CommonFile.h"




Physics::Physics()
{

}

Physics::~Physics() 
{

}



void HandleCollision(RIGIDBODY& body1 ,RIGIDBODY& body2, TCOLLISION& theCollision, float dt)
{
   float e;     // average coefficient of restitution
   Vector3D J; //  impulse vector
   Vector3D impulseForce; // the impulsive force 
   Vector3D n ; // the normalized vector of the collision normal vector
   Vector3D Vr; // relative velocity in the collision normal direction
   // contact vectors
   Vector3D r1;// contact vector from body1
   Vector3D r2; // contact vector from body2
   Matrix3D I=Identity(); // identity matrix

   // compute the coefficient of restitution(=e) of the 2 colliding bodies by using the maximum value.Use c++ max function.
   e = max(body1.coefficientOfRestitution, body2.coefficientOfRestitution);
   //compute collision Normal N= C1C2=C2-C1  where  C1=ball1 center position ,C2=ball2 center position
   // so call the argument theCollision : theCollisionNormal=Body1Position-Body2Position;
   theCollision.normal = body2.position - body1.position;
   // normalize the collision normal
   theCollision.normal = theCollision.normal.Normalize();
   // assign n to the normalized collision normal computed above : n=(C2-C1)/||C2-C1||
   n = theCollision.normal;
   // compute body1 inverse Inertia tensor(=inertiaInv) :that is body.inertiaInv=body.inertia.Inverse().
   body1.inertiaInv = body1.inertia.Inverse();
   // compute body2 inverse Inertia tensor (=inertiaInv) :that is body.inertiaInv=body.inertia.Inverse().
   body2.inertiaInv = body2.inertia.Inverse();
   // calculate the collision contact point(=ContactLocation) of body1  in  world space => see formula from
   // the lab handout
     body1.contactLocation= body1.position + body1.radius*n;
   // calculate the contact vector of body1(=r1)  :  r1=BodyContactLocation - BodyCenterOfMassPosition
    r1=body1.contactLocation - body1.position ;
   // calculate the collision contact point(=ContactLocation) of body2  in  world space => see formula from
   // the lab handout 
     body2.contactLocation=body2.position - body2.radius*n;
   // calculate the contact vector of body2(=r2)  :  r2=BodyContactLocation - BodyCenterOfMassPosition
     r2= body2.contactLocation - body2.position;
   // compute the collision points relative velocity(=vr) from the two balls (see handout) 
	 Vr =(body1.velocity - body2.velocity + ((body1.angularVelocity ^ r1) - (body2.angularVelocity ^ r2)));
   //Set the Collision(=theCollision) relative Velocity equal to Vr
	 theCollision.relativeVelocity = Vr;
   // Mass matrix or collision matrix
  Matrix3D K;
  //compute the collision matrix or mass matrix K (see lecture note or lab handout)
  K = (body1.massInv + body2.massInv) * I - (Skew(r1) * body1.inertiaInv * Skew(r1) + Skew(r2) *  body2.inertiaInv * Skew(r2));
  // Compute the impulse magnitude j (see formula from handout)
  float j;
  j = (-(1 + e) * Vr * n) / (n * K * n);
  // compute now the collision impulse vector(=J)
  J = j * n;
  // compute body1 impulse(=impulse)
  body1.impulse = J;
  // compute body2 impulse(=impulse).Be careful, this one is negative.
  body2.impulse = -J;
  // compute body1 impulsive forces (=impulseForce) .remember F=J/dt  dt=time step
  body1.impulseForce = body1.impulse / dt;
  // compute body2 impulsive forces (=impulseForce) .remember F=J/dt  dt=time step
  body2.impulseForce = body2.impulse / dt;
   // compute body1 velocity(=velocity) after collision: v1=v1+ J/m1
  body1.velocity = body1.velocity + (J / body1.mass);
  // compute body2 velocity(=velocity) after collision: v2=v2 - J/m2
  body2.velocity = body2.velocity - (J / body2.mass);
     // set the total force on body1 during collision time to be equal to the impulsive Force: totalForce= impulseForce
  body1.totalForces = body1.impulseForce;
   //  set the total force on body2 during collision time to be equal to the impulsiveForce: totalForce= impulseForce
  body2.totalForces = body2.impulseForce;
  // compute body1  torque. remember torque= ContactVector X impulseForce
   // where ContactVector=ContactPointLocation - BodyCenterOfmassLocation, as defined in world space for both entities
  body1.torque = r1 ^ body1.impulseForce;
  // compute body2  torque. remember torque= ContactVector X impulseForce
   // where ContactVector = ContactPointLocation - BodyCenterOfmassLocation, as defined in world space for both entities
  body2.torque = r2 ^ body2.impulseForce;
   J=n=r1=r2=Vector3D();
   
}




void Physics::Update(float dt)
{
       D3DXMATRIX translate ; // matrix to update the rigid body center of mass location
 	   D3DXMATRIX rotation;  // matrix to update the rigid body orientation
	   // compute the linear acceleration , a=TotalForce/mass
	   acceleration = totalForces / mass;
	   // compute the new velocity using Euler : v = v + a*dt
	   velocity = velocity + acceleration * dt;
	   // compute the new position using Euler integration , r = r + v*dt
	   position = position + velocity * dt;
	   // translate the object by calling DirectX translation transform, D3DXMatrixTranslation
	   D3DXMatrixTranslation(&translate, position.x, position.y, position.z);
       //compute the new angular velocity (see handout)
	   angularVelocity = angularVelocity + inertiaInv * torque * dt;
	   float maxAngularSpeed; // maximum angular speed
		//compute maximum angular speed(=maxAngularSpeed) see Rigid Body kinematics Lecture or
		//lab handout note for formula
		maxAngularSpeed=  2.0f*velocity.Norm()/radius;
	   // Do: if the rigid body angular speed(=w)>=maxAngularSpeed,Wmax, then w=Wmax*W.normalized() (see note)
        if(angularVelocity.Norm()>=maxAngularSpeed)  angularVelocity=maxAngularSpeed*angularVelocity.Normalize();
	   // update the rigid body orientation (see formula from handout)
		orientation = orientation + Skew(angularVelocity)*orientation*dt;
	   // use Gram-schmidt to orthonormalize the orientation matrix : call Orthonormalize()
	   orientation=orientation.Orthonormalize();
	   // now update the object world inertia tensor according to its orientation in world space for
	   // possible next collision  see note for formula
	   inertia = orientation * Ibody;
	   // convert the orientation matrix to a DirectX matrix by calling ConvertToD3DXMatrix(),call the resulting matrix "rotation"
	   rotation = orientation.ConvertToD3DXMatrix();
	   // multiply the previous two transforms(translate and rotation) into WorldMatrix that is  WorldMatrix=rotation*translate
	   WorldMatrix = rotation * translate;
       // reset the torque to zero vector 
        torque=Vector3D(0.0f,0.0f,0.0f);
		// damp the angular velocity by 0.85.
        angularVelocity=0.85f*angularVelocity;
		// if the angular speed is <= 0.1 then set the angular velocity to zero vector
		if(angularVelocity.Norm()<=0.1f) angularVelocity=Vector3D(0.0F,0.0F,0.0F);
		// set the total applied forces to zero
		totalForces=Vector3D(0.0,0.0f,0.0f);
		// set the contact location  to zero
		contactLocation=Vector3D(0.0f,0.0f,0.0f);
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



 COLLISION_STATE CheckCollision(RIGIDBODY& body1,RIGIDBODY& body2,TCOLLISION& theCollision)
{
   COLLISION_STATE  HasCollided= NO_COLLISION;
   float Distance; // distance between the two balls centers
   Vector3D C1C2 ; // the vector distance between the two balls centers
    
   // Compute the vector between the centers of the ball C1C2 ,
   // where C1=center of ball1(body1) and C2=center of body2(ball2);
   C1C2 = body2.position - body1.position;
   
   // now compute their distance , ||C1C2||
   Distance=C1C2.Norm();

   if( Distance  < body1.radius + body2.radius )
	  {
        HasCollided=COLLISION;
	  }
	 
	else
	if(Distance - (body1.radius + body2.radius)<=0.001f )
	  {
         HasCollided=TOUCHING;
	  }
   
	else 
	 if( Distance > body1.radius + body2.radius)
	   {
	     HasCollided=NO_COLLISION;
	   }
       
   return(HasCollided);
}




void  ResolveOverlapping(RIGIDBODY& body1 ,RIGIDBODY& body2,TCOLLISION& theCollision, float dt)
{
COLLISION_STATE status= PENETRATING;
bool done=false;
float h=dt ; // temporary time step 

while( !done  && !IsZero(dt))
    {
	    switch(status)
			{  
			case PENETRATING:
				{ 
				
				RigidBody B1=body1;
				RigidBody B2=body2;
			    h=dt;
				// reverse velocities and impulse force of  body B1
				B1.velocity        = -B1.velocity;
				B1.angularVelocity = -B1.angularVelocity;
				B1.impulseForce    = -B1.impulseForce;
				B1.impulse         = -B1.impulse;

				// reverse velocities and impulse force of B2
                B2.velocity        = -B2.velocity;
				B2.angularVelocity = -B2.angularVelocity;
				B2.impulseForce    = -B2.impulseForce;
				B2.impulse         = -B2.impulse;

				// update the 2 bodies
				B1.Update(h);
				B2.Update(h);
                // half the emporary time step h ; h=h/2
				h=0.5f*h;

				// reverse the linear and angular velocities ,and the impulse force of B1
				B1.velocity        = -B1.velocity;
				B1.angularVelocity = -B1.angularVelocity;
				B1.impulseForce    = -B1.impulseForce;
				B1.impulse         = -B1.impulse;

				// reverse the linear and angular velocities ,and the impulse force of body2
                B2.velocity        = -B2.velocity;
				B2.angularVelocity = -B2.angularVelocity;
				B2.impulseForce    = -B2.impulseForce;
				B2.impulse         = -B2.impulse;

				// update the 2 bodies using h
				B1.Update(h);
				B2.Update(h);
				body1=B1;
				body2=B2;

				// now check the collision status by calling CheckCollision()
                 status=CheckCollision(body1 ,body2,theCollision);

				}
			    break;

			case TOUCHING :
                 HandleCollision(body1,body2,theCollision,dt);
				 done=true;
				 break;

			case NO_COLLISION:
				body1.Update(dt);
				body2.Update(dt);
				break;

			}

	}  

	/*if (h=0.0001f)
    {
        // Bounce the objects.
        HandleCollision(body1,body2,theCollision,h);
        body1.Update(h);
        body2.Update(h);
    }*/
}

Collision::Collision()
{

}

Collision::~Collision()
{

}


bool IsZero(float value)
{
 value=fabs(value); 
 return(value<0.0001);
}


