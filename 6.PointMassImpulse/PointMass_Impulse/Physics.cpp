
#include"CommonFile.h"
//#include"Physics.h"
//#include"Game3DModel.h"
// 




Physics::Physics()
{

}

Physics::~Physics() 
{

}


void Physics::Update(float dt)
{      
     // using newton second law, m*a=F calculate the acceleraton that is a=F/m 
	acceleration = totalForces / mass;
	 // use Euler to compute the velocity   v(t+dt) = v(t) + a(t)*dt
	velocity = velocity + acceleration * dt;
     // use Euler to compute the particle position  : r(t+dt)=r(t) + v(t)*dt
	position = position + velocity *dt;
	// using DirectX built-in translation matrix ,  D3DXMatrixTranslation , to move the particle
	D3DXMatrixTranslation(&WorldMatrix, position.x, position.y, position.z);

}



void HandleCollision(RIGIDBODY& body1 ,RIGIDBODY& body2, TCOLLISION& theCollision, float dt)
{
	float e;     // average coefficient of restitution
	Vector3D J; //  impulse vector 
	Vector3D n ; // the normalized vector of the collision normal vector
	Vector3D Vr; // relative velocity of the ball 
   // compute the average coefficient of restitution (e) of the 2 colliding bodies
	e = (body1.coefficientOfRestitution + body2.coefficientOfRestitution) / 2;
   //compute collision Normal n= C1-C2   C1=ball1 center position ,C2=ball2 center position
	n = body1.position - body2.position;
   // normalize n 
	n=n.Normalize();
   // set the Collision normal(theCollision.norma) to n
	theCollision.normal = n;
   // compute the relative velocity of the two balls  Vr=v1-v2  where v1=body1 velocity and v2=body2 velocity
	Vr = body1.velocity - body2.velocity;
   // set theCollision relative velocity to Vr 
	theCollision.relativeVelocity = Vr;
   //compute the magnitutde of impulse  j= -(1+e)*m1*m2*(v1-v2)*n/(m1+m2) , v1-v2=relative velocity=Vr
   float j; 
   j = -(1 + e) *body1.mass*body2.mass*Vr*n / (body1.mass + body2.mass);
	   // compute now the impulse vector J in the direction of the collision normal vector n, J= j*n
	J = j * n;
   // compute the impulsive force (impulsiveForce) of ball1 .remember F=J/deltaT
	body1.impulsiveForce = J / dt;
   // compute the impulsive force (impulsiveForce) of ball2 .remember F=-J/deltaT
	body2.impulsiveForce = -J / dt;
   // compute the velocities of body1 after collision:v1=v1+ J/m1
	body1.velocity += J / body1.mass;
   // compute the velocities of body2 after collision:v2=v2-J/m2
	body2.velocity -= J / body2.mass;
	// compute the total force on body1 during collision : body1 totalForce= body1 impulsiveForce 
	body1.totalForces = body1.impulsiveForce;
	// compute the total force on body2 during collision : body2 totalForce= body2 impulsiveForce 
	body2.totalForces = body2.impulsiveForce;
	// calculate the collision contact point C=C1 + ball1Radius*n  from ball1    
	theCollision.contactPoint = body1.position + body1.radius * n;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



 COLLISION_STATE CheckCollision(RIGIDBODY& body1,RIGIDBODY& body2 )
{
   COLLISION_STATE  HasCollided= NO_COLLISION;
   float distance=0.0f; // distance between the  2 bodies center set temporary to 0
   Vector3D C1C2 ; // the 2 bodies center vector 
   
   
   // Compute the vector between the centers of  ball1 and ball2 : C1C2 ,
   // where C1=center of ball1(body1) and C2=center of body2(ball2);
   C1C2 = body1.position - body2.position;
   // now compute their distance , distance=||C1C2|| , by calling Norm()
   distance = C1C2.Norm();
   //if(  ||C1C2|| < body1 radius + body2 radius) then HasCollided is COLLISION
   if (distance < (body1.radius + body2.radius))
	  {
		HasCollided = COLLISION;
	  }


	/* ELSE IF ( ||C1C2|| == body1 radius + body2 radius) THEN TOUCHING
   We will use the inequality (<= ) where the equality (==) is being used
     as it is already done  for you below*/
   //else if (distance == (body1.radius + body2.radius))
   //{
	  // HasCollided = TOUCHING;
   //}

	if(  fabs(distance - (body1.radius + body2.radius))<=COLLISION_TOLERANCE  )
	  {
		HasCollided = TOUCHING;
	}
   
//	else   // ELSE IF(  ||C1C2|| > body1 radius + body2 radius )  THEN HasCollided is NO_COLLISION

	if (distance > (body1.radius + body2.radius))
	   {
		HasCollided = NO_COLLISION;
	   }

   return(HasCollided);
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
 return(value<0.01);
}


