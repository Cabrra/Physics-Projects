

#include"Physics.h"


/********************************************************************************************************************
Author  : Richard Bahin
Function: Physics()                                                                                    
Input   : none																									
Output  : none																											
Returns : none                                                                                                       
comment : Physics class constructor                                                                                                        
TODO    : none																											
*********************************************************************************************************************/		
Physics::Physics()
{

}

/********************************************************************************************************************
Author  : Richard Bahin
Function: ~Physics()                                                                                    
Input   : none																									
Output  : none																											
Returns : none                                                                                                       
comment : Physics class destructor                                                                                                        
TODO    : none																											
*********************************************************************************************************************/		
Physics::~Physics() 
{

}


/********************************************************************************************************************
Author  : Richard Bahin
Function: Update()                                                                                    
Input   : The time step dt 																									
Output  : none																											
Returns : void                                                                                                        
comment : this function will update each ball velocity and position .                                                                                                        
TODO    : see handouts																											
*********************************************************************************************************************/		
void Physics::Update(float dt)
{
	    // sum the forces applied to the ball   to TotalFoce= Force + Weight ( Newton's  second law) 
	totalForces = force + weight;
		// using newton second law, m*a=F calculate a=F/m   
		acceleration = totalForces / mass;
		// use Euler to compute the velocity 
	velocity = velocity + acceleration * dt;
		// use Euler to compute the particle position 
	position = position + velocity * dt;
	    // using DirectX built-in translation matrix , D3DXMAtrixTranslation(),to move the particle

	D3DXMatrixTranslation(&WorldMatrix, position.x, position.y, position.z);
}
